#include "info.h"
#include "ui_info.h"
#include "settings_file.h"
#include "my_string.h"
#include "borrow.h"
#include "history.h"
#include "global.h"
#include "library.h"
#include "admin.h"
#include "card.h"
#include "pbl2.h"
#include "info_book.h"
#include "exception.h"
#include <QImageReader>
#include <QPainter>
#include <QPainterPath>
#include <QHeaderView>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>


BST_Borrow thong_tin_muon_tra;
BST_History lich_su_hoat_dong;
BST_Book danh_sach_yeu_thich;
//history his;

info::info(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::info)
{
    ui->setupUi(this);
    // connect(ui-> pushButton_8 , &QPushButton::clicked, [=](){
    //     ui->stackedWidget->setCurrentIndex(0);
    // });

    // connect(ui->pushButton_9, &QPushButton::clicked, [=](){
    //     ui->stackedWidget->setCurrentIndex(1);
    // });

    // connect(ui->pushButton_10, &QPushButton::clicked, [=](){
    //     ui->stackedWidget->setCurrentIndex(2);
    // });
    set_anh_dai_dien();
    resize_bang();
    ui->dat_button->installEventFilter(this);
    ui->muon_button->installEventFilter(this);
    ui->tra_button->installEventFilter(this);
    ui->yeu_thich_button->installEventFilter(this);

    ui->dat_button->setProperty("ID_Status", 1);
    ui->muon_button->setProperty("ID_Status", 2);
    ui->tra_button->setProperty("ID_Status", 3);
    ui->yeu_thich_button->setProperty("ID_Status", 4);
    on_tu_sach_cua_toi_clicked();
    ui->Ho_va_ten_top->setText(QString::fromStdString(lib.get_acc_sign_in().get_ten_tai_khoan()));
    string chuc_vu;
    if (lib.get_acc_sign_in().get_level() == "Admin"){
        chuc_vu = "Quản trị viên";
        ui->quyen_quan_tri->setVisible(true);
    }
    else if (lib.get_acc_sign_in().get_level() == "Librarian"){
        chuc_vu = "Thủ thư";
        ui->quyen_quan_tri->setVisible(true);
    }
    else{
        chuc_vu = "Độc giả";
        ui->quyen_quan_tri->setVisible(false);
    }
    ui->diem_chuc_vu_top->setText(QString::fromStdString(chuc_vu));
}

info::~info()
{
    delete ui;
}



bool info::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        
        // Ép kiểu đối tượng bị click về QWidget
        QWidget *widget = qobject_cast<QWidget *>(watched);
        
        // Kiểm tra xem widget này có chứa property "bookID" không?
        // isValid() trả về true nếu property đó tồn tại và có giá trị
        if (widget && widget->property("ID_Status").isValid()) {
            
            // Lấy ID ra xử lý
            int id = widget->property("ID_Status").toInt();
            
            qDebug() << "Đã bấm vào widget có ID sách là:" << id;
            switch (id)
            {
            case 1://xem đặt sách
                on_tu_sach_cua_toi_clicked();
                break;
            case 2://xem mượn sách
                set_muon_sach_clicked();
                break;
            case 3://xem trả sách
                set_tra_sach_clicked();
                break;
            case 4://xem yêu thích
                set_yeu_thich_clicked();
                break;
            default:
                break;
            } 
            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void info::on_quyen_quan_tri_clicked()
{
    auto win = new admin(this);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
    this->hide();
    // Khi cửa sổ đăng ký đóng, hiển thị lại Pbl2
    /*connect(win, &dang_ky_dialog::registered, this, [this, win](const Account& user) {
        acc_sign_in = user;
        //ui->info->setCurrentIndex(1);
        //ui->user_name_layout->setText(
        //    QString::fromStdString("Xin chào " + giai_ma_str_(acc_sign_in.getAccount_Name()) + ","));
        //ui->score_layout->setText("Admin");
        this->show();
        this->raise();
        this->activateWindow();
        win->deleteLater();
    });
    connect(win, &dang_ky_dialog::returned, this, [this,win](){
        this->show();
        this->raise();
        this->activateWindow();
    });*/
}
void info::closeEvent(QCloseEvent *event)
{
    QWidget *parentWin = this->parentWidget();
    if (parentWin) {
        parentWin->show();
    }
    this->deleteLater();
    event->accept();
}



void info::on_tu_sach_cua_toi_clicked()
{
    ui->vung_hien_thi->setCurrentWidget(ui->page_2);
    ui->tu_sach_cua_toi_layout->setCurrentWidget(ui->dat_sach_layout);
    ui->label_tu_sach_cua_toi->setText(QString::fromStdString("Tủ sách của " + lib.get_acc_sign_in().get_ten_tai_khoan()));
    lib.get_borrow_data().info_user(lib.get_acc_sign_in().get_ID(), thong_tin_muon_tra);
    lich_su_hoat_dong.load_from_file(lib.get_acc_sign_in().get_ten_dang_nhap(), lich_su_hoat_dong);
    int tong_sach_dang_muon = 0;
    int tong_sanh_dang_dat = 0;
    int tong_sach_da_tra = 0;
    int tong_sach_yeu_thich = 0;
    thong_tin_muon_tra.traverse_ascending([&](borrow &a){
        if (a.get_status() == StatusType::TRA_DUNG_HAN || a.get_status() == StatusType::TRA_QUA_HAN){
            tong_sach_da_tra++;
        }
        else if (a.get_status() == StatusType::DANG_MUON || a.get_status() == StatusType::QUA_HAN_MUON){
            tong_sach_dang_muon++;
        }
        else if (a.get_status() == StatusType::XU_LY || a.get_status() == StatusType::SAN_SANG || a.get_status() == StatusType::QUA_HAN_DAT){
            tong_sanh_dang_dat++;
        }
    });
    lib.get_yeu_thich_data().traverse_ascending([&](yeu_thich &a){
        if (a.get_user_id() == lib.get_acc_sign_in().get_ID()){
            tong_sach_yeu_thich++;
        }
    });
    ui->tong_sach_label->setText(QString::number(tong_sanh_dang_dat));
    ui->dang_muon_label->setText(QString::number(tong_sach_dang_muon));
    ui->da_tra_label->setText(QString::number(tong_sach_da_tra));
    ui->yeu_thich_label->setText(QString::number(tong_sach_yeu_thich));
    set_bang_dat_sach();
}

inline QPixmap loadScaled(const QString& path, const QSize& toSize, int radius)
{
    QPixmap pm(path);
    if (pm.isNull()) {
        // placeholder nếu không tìm thấy ảnh
        QPixmap ph(toSize);
        ph.fill(Qt::lightGray);
        return ph;
    }
    if (radius <= 0)
    return pm.scaled(toSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap output(toSize);
    output.fill(Qt::transparent);
    QPainter painter(&output);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPainterPath path_;
    path_.addRoundedRect(0, 0, toSize.width(), toSize.height(), radius, radius);
    painter.setClipPath(path_);
    QPixmap scaled = pm.scaled(toSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    int x = (toSize.width() - scaled.width()) / 2;
    int y = (toSize.height() - scaled.height()) / 2;
    painter.drawPixmap(x, y, scaled);
    return output;
}

QPixmap info::load_image_pro(const QString &path, const QSize &targetSize, int radius, bool cropToFill) {
    // 1. Kiểm tra file tồn tại
    if (!QFile::exists(path)) {
        // Trả về ảnh rỗng hoặc ảnh placeholder xám nếu muốn
        QPixmap placeholder(targetSize);
        placeholder.fill(Qt::lightGray);
        return placeholder;
    }

    // 2. Dùng QImageReader để tự động xoay ảnh (Fix lỗi xoay ngang)
        QImageReader reader(path);
        reader.setAutoTransform(true); // <--- QUAN TRỌNG NHẤT
        QImage img = reader.read();

    if (img.isNull()) return QPixmap();

    // 3. Xử lý Scale (Phóng to/Thu nhỏ)
    if (cropToFill) {
        // Mode: FILL (Lấp đầy khung, cắt phần thừa) - Đẹp cho UI
        img = img.scaled(targetSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        
        // Cắt lấy phần giữa (Center Crop)
        int x = (img.width() - targetSize.width()) / 2;
        int y = (img.height() - targetSize.height()) / 2;
        img = img.copy(x, y, targetSize.width(), targetSize.height());
    } else {
        // Mode: FIT (Vừa khít khung, giữ nguyên ảnh) - Xem full ảnh
        img = img.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    // 4. Xử lý Bo góc (Radius) và Vẽ lên QPixmap
    // Tạo Pixmap trong suốt với kích thước mong muốn (nếu mode FIT thì lấy kích thước thật của ảnh sau scale)
    QSize finalSize = cropToFill ? targetSize : img.size();
    QPixmap finalPix(finalSize);
    finalPix.fill(Qt::transparent);

    QPainter painter(&finalPix);
    painter.setRenderHint(QPainter::Antialiasing);      
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Tạo khung bo tròn
    QPainterPath pathPath;
    // Nếu radius > 0 thì bo, không thì để vuông
    if (radius > 0) {
        pathPath.addRoundedRect(0, 0, finalSize.width(), finalSize.height(), radius, radius);
        painter.setClipPath(pathPath);
    }

    // Vẽ ảnh lên
    painter.drawImage(0, 0, img);
    painter.end();

    return finalPix;
}

void info::set_anh_dai_dien(){
    QString id_path = QString::fromUtf8("../../anh_dai_dien/%1.png").arg(lib.get_acc_sign_in().get_ID());
    QString default_path = QString::fromUtf8("../../anh_dai_dien/anh_dai_dien.png");
    QString png_path = QFile::exists(id_path) ? id_path : default_path;
    
    // Tính size thật (nhân với PixelRatio để nét trên màn hình 2K/4K)
    QSize realSize = ui->anh_dai_dien->size() * ui->anh_dai_dien->devicePixelRatio();
    QSize realSize2 = ui->anh_dai_dien_2->size() * ui->anh_dai_dien_2->devicePixelRatio();
    
    // GỌI HÀM MỚI cho anh_dai_dien
    QPixmap pix = load_image_pro(png_path, realSize, 15, true); 
    pix.setDevicePixelRatio(ui->anh_dai_dien->devicePixelRatio());
    ui->anh_dai_dien->setPixmap(pix);
    
    // GỌI HÀM MỚI cho anh_dai_dien_2
    QPixmap pix2 = load_image_pro(png_path, realSize2, 15, true);
    pix2.setDevicePixelRatio(ui->anh_dai_dien_2->devicePixelRatio());
    ui->anh_dai_dien_2->setPixmap(pix2);
}

void info::tim_sach_yeu_thich(BST_Book &b){
    lich_su_hoat_dong.load_from_file(lib.get_acc_sign_in().get_ten_dang_nhap(), lich_su_hoat_dong);
    danh_sach_yeu_thich.clear();
    lib.get_yeu_thich_data().traverse_ascending([&](yeu_thich &a){
        if (a.get_user_id() == lib.get_acc_sign_in().get_ID()){
            book book_info;
            if (lib.get_book_data().find(a.get_book_id(), book_info)){
                danh_sach_yeu_thich.insert(book_info);
            }
        }
    });
}

void info::remove_table(QTableWidget *table){
    while (table->rowCount() > 0){
        table->removeRow(0);
    }
}

void info::resize_bang(){
    // Cấu hình lại bảng đặt sách
        ui->bang_dat_sach->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->bang_dat_sach->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->bang_dat_sach->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *header = ui->bang_dat_sach->horizontalHeader();
    header->setStretchLastSection(false);

    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents);

    header->setSectionResizeMode(1, QHeaderView::Stretch);
    // Cấu hình lại bảng mượn sách
    ui->muon_sach_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->muon_sach_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->muon_sach_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *header_muon = ui->muon_sach_table->horizontalHeader();
    header_muon->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header_muon->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header_muon->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header_muon->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    header_muon->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    header_muon->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    header_muon->setSectionResizeMode(7, QHeaderView::ResizeToContents);
    header_muon->setStretchLastSection(false);
    header_muon->setSectionResizeMode(1, QHeaderView::Stretch);
    // Cấu hình lại bảng trả sách
    ui->tra_sach_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tra_sach_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tra_sach_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *header_tra = ui->tra_sach_table->horizontalHeader();
    header_tra->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header_tra->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header_tra->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header_tra->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    header_tra->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    header_tra->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    header_tra->setSectionResizeMode(7, QHeaderView::ResizeToContents);
    header_tra->setStretchLastSection(false);
    header_tra->setSectionResizeMode(1, QHeaderView::Stretch);
    // Cấu hình lại lich sử hoạt động
    ui->lich_su_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lich_su_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->lich_su_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView *header_lich_su = ui->lich_su_table->horizontalHeader();
    header_lich_su->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header_lich_su->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    header_lich_su->setSectionResizeMode(2, QHeaderView::Stretch);
    header_lich_su->setStretchLastSection(false);   
}
void info::set_bang_dat_sach(){
    remove_table(ui->bang_dat_sach);
    lib.get_borrow_data().info_user(lib.get_acc_sign_in().get_ID(), thong_tin_muon_tra);
    int STT = 1;
    thong_tin_muon_tra.traverse_ascending([this,&STT](borrow &br){
        if (br.get_status() == StatusType::XU_LY || br.get_status() == StatusType::SAN_SANG || br.get_status() == StatusType::QUA_HAN_DAT){
            int row = ui->bang_dat_sach->rowCount();
            ui->bang_dat_sach->insertRow(row);

            auto setText = [&](int col, const QString &text, bool center = false) {
                QTableWidgetItem *item = new QTableWidgetItem(text);
                if (center)
                    item->setTextAlignment(Qt::AlignCenter);
                ui->bang_dat_sach->setItem(row, col, item);
            };
            book book_info;
            lib.get_book_data().find(br.get_book_id(), book_info);
            setText(0, QString::number(STT++), true);
            ui->bang_dat_sach->setCellWidget(row, 1, createTenSachWidget(book_info.get_ID(), book_info.get_Name(), book_info.get_Author()));
            setText(2, QString::fromStdString(br.get_ngay_dat().get_date()), true);
            setText(3, QString::fromStdString((br.get_ngay_dat() + settings_file::getInstance()->get_so_ngay_dat_sach()).get_date()), true);
            ui->bang_dat_sach->setCellWidget(row, 4, createTinhTrangWidget(br.get_status(),((my_time::now() - (br.get_ngay_dat() + settings_file::getInstance()->get_so_ngay_dat_sach())).get_day())));
            ui->bang_dat_sach->setCellWidget(row, 5, createNutXoaWidget(book_info.get_ID(), br.get_id()));

        }
    });
}

QWidget* info::createTenSachWidget(const long long &id,const string &ten_sach, const string &tac_gia){
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(10);

    // Tạo QLabel cho tên sách
    QLabel *tenSachLabel = new QLabel(QString::fromStdString(to_stringll_(id) + " - " + ten_sach));
    tenSachLabel->setStyleSheet("font-weight: bold; font-size: 14px;color: #333333;");

    // Tạo QLabel cho tác giả
    QLabel *tacGiaLabel = new QLabel(QString::fromStdString(tac_gia));
    tacGiaLabel->setStyleSheet("font-size: 12px; color: gray;");

    // Tạo layout dọc để chứa cả hai QLabel
    QVBoxLayout *textLayout = new QVBoxLayout();
    textLayout->addWidget(tenSachLabel);
    textLayout->addWidget(tacGiaLabel);
    textLayout->setSpacing(2);
    layout->addLayout(textLayout);
    layout->addStretch(); // Đẩy các widget về bên trái

    return widget;
}

QWidget* info::createTinhTrangWidget(StatusType trang_thai, int days)
{
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);
    QLabel *lblStatus = new QLabel();
    lblStatus->setAlignment(Qt::AlignCenter);
    switch (trang_thai)
    {
    case StatusType::XU_LY:
        lblStatus->setText("Đang xử lý");
        lblStatus->setStyleSheet(
            "color: blue; font-weight: bold; font-size: 11px; text-align: center;");
        break;
    case StatusType::SAN_SANG:
        lblStatus->setText("Sẵn sàng");
        lblStatus->setStyleSheet(
            "color: #28a745; font-weight: bold; font-size: 11px; text-align: center;");
        break;
    case StatusType::QUA_HAN_DAT:
        lblStatus->setText("Quá hạn đặt");
        lblStatus->setStyleSheet(
            "color: red; font-weight: bold; font-size: 11px; text-align: center;");
        break;
    case StatusType::DANG_MUON:
        lblStatus->setText("Đang mượn");
        lblStatus->setProperty("status", 4);
        lblStatus->setStyleSheet(
            "color: blue; font-weight: bold; font-size: 11px; text-align: center;");
        break;
    case StatusType::QUA_HAN_MUON:
        lblStatus->setText("Quá hạn" + QString::number(days) + " ngày");
        lblStatus->setProperty("status", 5);
        lblStatus->setStyleSheet(
            "color: red; font-weight: bold; font-size: 11px; text-align: center;");
        break;
    case StatusType::TRA_DUNG_HAN:
        lblStatus->setText("Đúng hạn");
        lblStatus->setProperty("status", 6);
        lblStatus->setStyleSheet(
            "color: #28a745; font-weight: bold; font-size: 11px; text-align: center;");
        break;
    case StatusType::TRA_QUA_HAN:
        lblStatus->setText(QString::number(days) + " ngày");
        lblStatus->setProperty("status", 7);
        lblStatus->setStyleSheet(
            "color: red; font-weight: bold; font-size: 11px; text-align: center;");
        break;
    default:
        break;
        
    }
    layout->addWidget(lblStatus);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(1);

    return container;
}

QWidget* info::createNutXoaWidget(long long id_book, long long id_borrow)
{
    QWidget *container = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(container);
    QPushButton *lblNut = new QPushButton();
    QPushButton *Xoa = new QPushButton();
    Xoa->setText("Xóa");
    Xoa->setProperty("ID_Borrow", QString::number(id_borrow));
    Xoa->setProperty("ID", QString::number(id_book));
    Xoa->setStyleSheet( "color: red; font-weight: bold; font-size: 12px; text-align: center;background-color:  #f7fbff;border: 2px solid red;padding: 2px 8px;border-radius: 5px;");
    Xoa->setCursor(Qt::PointingHandCursor);
    connect(Xoa, &QPushButton::clicked, this, &info::onXoaDatSachClicked);
    layout->addWidget(Xoa);
    layout->setContentsMargins(5,5,5,5);
    layout->setSpacing(5);
    return container;
}

void info::onXoaDatSachClicked()
{
QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    long long id_borrow = button->property("ID_Borrow").toLongLong();

    QMessageBox::StandardButton reply =
        QMessageBox::question(
            this,
            "Xác nhận hủy đặt sách",
            "Bạn có chắc chắn muốn hủy yêu cầu đặt sách này?",
            QMessageBox::Yes | QMessageBox::No
        );

    if (reply != QMessageBox::Yes)
        return;

    try {
        lib.huy_dat_sach(id_borrow);

        QMessageBox::information(
            this,
            "Thành công",
            "Đã hủy đặt sách thành công."
        );

        // reload lại dữ liệu
        lib.get_borrow_data().info_user(
            lib.get_acc_sign_in().get_ID(),
            thong_tin_muon_tra
        );
        set_bang_dat_sach();
    }
    catch (AppException &e) {
        QMessageBox::warning(
            this,
            QString::fromStdString(e.getTitle()),
            QString::fromStdString(e.what())
        );
    }
    catch (...) {
        QMessageBox::critical(
            this,
            "Lỗi hệ thống",
            "Đã xảy ra lỗi không xác định."
        );
    }
}

void info::set_muon_sach_clicked(){
    ui->tu_sach_cua_toi_layout->setCurrentWidget(ui->muon_sach_layout);
    reload_muon_sach_table();
}

void info::reload_muon_sach_table(){
    remove_table(ui->muon_sach_table);
    int STT = 1;
    thong_tin_muon_tra.traverse_ascending([this,&STT](borrow &br){
        if (br.get_status() == StatusType::DANG_MUON || br.get_status() == StatusType::QUA_HAN_MUON){
            int row = ui->muon_sach_table->rowCount();
            ui->muon_sach_table->insertRow(row);

            auto setText = [&](int col, const QString &text, bool center = false) {
                QTableWidgetItem *item = new QTableWidgetItem(text);
                if (center)
                    item->setTextAlignment(Qt::AlignCenter);
                ui->muon_sach_table->setItem(row, col, item);
            };
            book book_info;
            lib.get_book_data().find(br.get_book_id(), book_info);
            setText(0, QString::number(STT++), true);
            ui->muon_sach_table->setCellWidget(row, 1, createTenSachWidget(book_info.get_ID(), book_info.get_Name(), book_info.get_Author()));
            setText(2, QString::fromStdString("BS-" + to_stringll_(br.get_book_copy_id())), true);
            setText(3, QString::fromStdString(br.get_ngay_muon().get_date()), true);
            setText(4, QString::fromStdString(br.get_ngay_phai_tra().get_date()), true);
            string gia_han = to_stringll_(br.get_lan_gia_han()) + "/" + to_stringll_(settings_file::getInstance()->get_so_lan_gia_han());
            setText(5, QString::fromStdString(gia_han), true);
            ui->muon_sach_table->setCellWidget(row, 6, createTinhTrangWidget(br.get_status(),((my_time::now() - br.get_ngay_phai_tra()).get_day())));
            ui->muon_sach_table->setCellWidget(row, 7, createNutGiaHanWidget(book_info.get_ID(), br.get_id()));
        }
    });

}

QWidget* info::createNutGiaHanWidget(long long id_book, long long id_borrow)
{
    QWidget *container = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(container);
    QPushButton *lblNut = new QPushButton();
    QPushButton *GiaHan = new QPushButton();
    GiaHan->setText("Gia hạn");
    GiaHan->setProperty("ID_Borrow", QString::number(id_borrow));
    GiaHan->setProperty("ID", QString::number(id_book));
    GiaHan->setStyleSheet( "color: green; font-weight: bold; font-size: 12px; text-align: center;background-color:  #f7fbff;border: 2px solid green;padding: 2px 8px;border-radius: 5px;");
    GiaHan->setCursor(Qt::PointingHandCursor);
    connect(GiaHan, &QPushButton::clicked, this, &info::onGiaHanMuonSachClicked);
    layout->addWidget(GiaHan);
    layout->setContentsMargins(5,5,5,5);
    layout->setSpacing(5);
    return container;
}

void info::onGiaHanMuonSachClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    long long id_borrow =
        button->property("ID_Borrow").toLongLong();

    try {
        lib.gia_han_muon_sach_(id_borrow);

        QMessageBox::information(
            this,
            "Thành công",
            "Gia hạn mượn sách thành công."
        );

        // reload dữ liệu
        lib.get_borrow_data().info_user(
            lib.get_acc_sign_in().get_ID(),
            thong_tin_muon_tra
        );
        reload_muon_sach_table();
    }
    catch (AppException &e) {
        QMessageBox::warning(
            this,
            QString::fromStdString(e.getTitle()),
            QString::fromStdString(e.what())
        );
    }
    catch (...) {
        QMessageBox::critical(
            this,
            "Lỗi hệ thống",
            "Đã xảy ra lỗi không xác định."
        );
    }
}

void info::set_tra_sach_clicked(){
    ui->tu_sach_cua_toi_layout->setCurrentWidget(ui->tra_sach_layout);
    reload_tra_sach_table();
}
void info::reload_tra_sach_table(){
    remove_table(ui->tra_sach_table);
    
    int STT = 1;
    thong_tin_muon_tra.traverse_ascending([this,&STT](borrow &br){
        if (br.get_status() == StatusType::TRA_DUNG_HAN || br.get_status() == StatusType::TRA_QUA_HAN){
            int row = ui->tra_sach_table->rowCount();
            ui->tra_sach_table->insertRow(row);
            book book_info;
            lib.get_book_data().find(br.get_book_id(), book_info);
            auto setText = [&](int col, const QString &text, bool center = false) {
                QTableWidgetItem *item = new QTableWidgetItem(text);
                if (center)
                    item->setTextAlignment(Qt::AlignCenter);
                ui->tra_sach_table->setItem(row, col, item);
            };
            setText(0, QString::number(STT++), true);
            ui->tra_sach_table->setCellWidget(row, 1, createTenSachWidget(book_info.get_ID(), book_info.get_Name(), book_info.get_Author()));
            setText(2, QString::fromStdString("BS-" + to_stringll_(br.get_book_copy_id())), true);
            setText(3, QString::fromStdString(br.get_ngay_muon().get_date()), true);
            setText(4, QString::fromStdString(br.get_ngay_phai_tra().get_date()), true);
            setText(5, QString::fromStdString(br.get_ngay_tra().get_date()), true);
            ui->tra_sach_table->setCellWidget(row, 6, createTinhTrangWidget(br.get_status(),((my_time::now() - br.get_ngay_phai_tra()).get_day())));
            ui->tra_sach_table->setCellWidget(row, 7, createTinhTrangTraSachWidget(br.get_tinh_trang_sach(), br.get_book_id()));
            setText(8, QString::fromStdString(tien_te_vnd(br.get_tien_phat()) + " VND"), true);
        }
    });
}

QWidget* info::createTinhTrangTraSachWidget(TinhTrangsach tinh_trang, long long id)
{
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);
    QLabel *lblStatus = new QLabel();
    lblStatus->setAlignment(Qt::AlignCenter);

    QString baseStyle = "QLabel { "
                        "   border-radius: 6px; "
                        "   padding: 4px 10px; "
                        "   font-weight: bold; "
                        "   font-size: 11px; "
                        "}";

    switch (tinh_trang)
    {
    case TinhTrangsach::TOT:
        lblStatus->setText("Tốt");
        lblStatus->setProperty("status", 0);
        lblStatus->setStyleSheet(baseStyle + 
            "QLabel { background-color: #28a745; color: white; }");
        break;

    case TinhTrangsach::BINH_THUONG:
        lblStatus->setText("Bình thường");
        lblStatus->setProperty("status", 1);
        lblStatus->setStyleSheet(baseStyle + 
            "QLabel { background-color: #b9f6ca; color: #1b5e20; }");
        break;

    case TinhTrangsach::HONG:
        lblStatus->setText("Hư hỏng");
        lblStatus->setProperty("status", 2);
        lblStatus->setStyleSheet(baseStyle + 
            "QLabel { background-color: #ff9800; color: white; }");
        break;

    case TinhTrangsach::MAT:
        lblStatus->setText("Mất");
        lblStatus->setProperty("status", 3);
        lblStatus->setStyleSheet(baseStyle + 
            "QLabel { background-color: #212121; color: white; }");
        break;

    default:
        lblStatus->setText("N/A");
        break;
    }

    layout->addWidget(lblStatus);
    layout->setAlignment(Qt::AlignCenter); 
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    return container;
}

void info::set_yeu_thich_clicked(){
    ui->tu_sach_cua_toi_layout->setCurrentWidget(ui->yeu_thich_layout);
    lay_sach_yeu_thich();
    reload_yeu_thich_table();
}

void info::lay_sach_yeu_thich(){
    danh_sach_yeu_thich.clear();
    lib.get_yeu_thich_data().traverse_ascending([&](yeu_thich &a){
        if (a.get_user_id() == lib.get_acc_sign_in().get_ID()){
            book book_info;
            if (lib.get_book_data().find(a.get_book_id(), book_info)){
                danh_sach_yeu_thich.insert(book_info);
            }
        }
    });
}

void info::reload_yeu_thich_table(){
    QLayout *layout = ui->layout_yeu_thich->layout();
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
    }
    auto path_link = ui->layout_yeu_thich;
    int i = 0;
    const int MAX_COL = 7;
    danh_sach_yeu_thich.traverse_ascending([this, path_link, &i, MAX_COL](book &a){
        auto card = new ProductCard(a);
        int row = i / MAX_COL;
        int col = i % MAX_COL;
        path_link->addWidget(card, row, col, Qt::AlignTop | Qt::AlignLeft);

        connect(card, &ProductCard::clicked, this, [this](book bk){
            hien_thi_sach(bk);
            // page_previous = 2;
            // if (is_sign_in) his.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::VIEW_BOOK, bk.get_ID(), "");
            // show_info_sach(bk);
        });

        i++;
    });

}

void info::hien_thi_sach(book b){
    auto win = new info_book(b, this);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
}

void info::on_lich_su_hoat_dong_clicked()
{
    ui->vung_hien_thi->setCurrentIndex(1);
    reload_lich_su_hoat_dong_table();
}

void info::reload_lich_su_hoat_dong_table(){
    remove_table(ui->lich_su_table);
    int STT = 0;
    lich_su_hoat_dong.traverse_descending([this, &STT](history_record &hr){
        STT++;
        if (STT > 100) return;
        int row = ui->lich_su_table->rowCount();
        ui->lich_su_table->insertRow(row);

        auto setText = [&](int col, const QString &text, bool center = false) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            if (center)
                item->setTextAlignment(Qt::AlignCenter);
            QFont font = item->font();
            font.setPointSize(10);
            item->setFont(font);
            item->setFont(font);
            font.setBold(true);
            item->setFont(font);
            ui->lich_su_table->setItem(row, col, item);
        };
        book book_info;
        QString textHienThi;
        textHienThi = QString::fromStdString(hr.get_ghi_chu());

        // if (lib.get_book_data().find(hr.get_book_id(), book_info)) {
        //     // Trường hợp 1: Tìm thấy sách -> Hiển thị "ID - Tên Sách"
        //     textHienThi = QString::fromStdString(to_stringll_(book_info.get_ID()) + " - " + book_info.get_Name());
        // } 
        // else {
        //     // Trường hợp 2: Không tìm thấy sách
        //     if (hr.get_book_id() == 0) {
        //         textHienThi = ""; 
        //     } else {
        //         // ID != 0 mà tìm không ra -> Sách đã bị xóa
        //         textHienThi = "Sách đã bị xóa hoặc không tồn tại";
        //     }
        // }

        // Cột 0: Thời gian
        setText(0, QString::fromStdString("   " + hr.get_date_action().get_datetime() + "   "), true);
        
        // Cột 1: Hành động (Widget)
        ui->lich_su_table->setCellWidget(row, 1, createActionLichSuWidget(hr.get_action_type()));
        
        // Cột 2: Tên sách (Đã xử lý ở trên)
        setText(2, textHienThi, false);
    });
}
QWidget* info::createActionLichSuWidget(ActionType action_type){
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);
    QLabel *lblAction = new QLabel();
    lblAction->setAlignment(Qt::AlignCenter);

    const QString baseStyle =
        "QLabel { border-radius: 6px; padding: 4px 10px; "
        "font-weight: bold; font-size: 11px; margin: 0 5px; }";

    auto setStyle = [&](const QString &text, int code, const QString &color) {
        lblAction->setText(text);
        lblAction->setProperty("action", code);
        lblAction->setStyleSheet(baseStyle + "QLabel { background-color: " + color + "; color: white; }");
    };

    switch (action_type)
    {
    case LOGIN:             setStyle("Đăng nhập",          0, "#2e8b57"); break;
    case REGISTER:          setStyle("Đăng ký",            1, "#1976d2"); break;
    case RESET_PASSWORD:    setStyle("Đặt lại mật khẩu",   2, "#ef6c00"); break;
    case VIEW_BOOK:         setStyle("Xem thông tin sách", 3, "#5e35b1"); break;
    case DOWNLOAD_BOOK:     setStyle("Tải sách",           4, "#00acc1"); break;
    case READ_ONLINE:       setStyle("Đọc online",         5, "#00897b"); break;
    case RESERVE_BOOK:
        setStyle("Đặt sách", 6, "#fdd835");
        lblAction->setStyleSheet(baseStyle + "QLabel { background-color: #fdd835; color: #1b1b1b; }");
        break;
    case BORROW_BOOK:       setStyle("Mượn sách",          7, "#7cb342"); break;
    case LIKE_BOOK:         setStyle("Yêu thích sách",     8, "#c2185b"); break;
    case DISLIKE_BOOK:      setStyle("Bỏ yêu thích",       9, "#9e9e9e"); break;
    case CONFIRM_BOOK:      setStyle("Xác nhận mượn",     10, "#512da8"); break;
    case RETURN_BOOK:       setStyle("Trả sách",          11, "#43a047"); break;
    case RETURN_OVERDUE:    setStyle("Trả quá hạn",       12, "#e53935"); break;
    case REMOVE_BOOK:       setStyle("Xóa sách",          13, "#c62828"); break;
    case ADD_BOOK:          setStyle("Thêm sách",         14, "#0097a7"); break;
    case UPDATE_BOOK:       setStyle("Cập nhật sách",     15, "#6a1b9a"); break;
    case ADD_BOOK_COPY:     setStyle("Thêm bản sao",      16, "#8e24aa"); break;
    case REMOVE_BOOK_COPY:  setStyle("Xóa bản sao",       17, "#d84315"); break;
    case ADJ_BOOK:          setStyle("Điều chỉnh sách",   18, "#ff8f00"); break;
    case ADJ_USER:          setStyle("Điều chỉnh người dùng", 19, "#26a69a"); break;
    case UNKNOWN:
    default:
        lblAction->setText("Khác");
        lblAction->setStyleSheet(baseStyle + "QLabel { background-color: #607d8b; color: white; }");
        break;
    }

    layout->addWidget(lblAction);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    return container;
}

void info::on_ho_so_ca_nhan_clicked()
{
    set_anh_dai_dien();
    ui->vung_hien_thi->setCurrentIndex(2);
    set_thong_tin_ca_nhan();
}

void info::set_thong_tin_ca_nhan(){
    ui->ten_dang_nhap->setText(QString::fromStdString(lib.get_acc_sign_in().get_ten_dang_nhap()));
    ui->ho_va_ten->setText(QString::fromStdString(lib.get_acc_sign_in().get_ten_tai_khoan()));
    ui->email->setText(QString::fromStdString(lib.get_acc_sign_in().get_email()));
    ui->so_dien_thoai->setText(QString::fromStdString(lib.get_acc_sign_in().get_phone_number()));
    if (lib.get_acc_sign_in().get_level() == "Admin"){
        ui->chuc_vu->setText("Quản trị viên");
    }
    else if (lib.get_acc_sign_in().get_level() == "Librarian"){
        ui->chuc_vu->setText("Thủ thư");
    }
    else{
        ui->chuc_vu->setText("Người dùng");
    }
    ui->ngay_sinh->setDate(QDate::fromString(QString::fromStdString(lib.get_acc_sign_in().get_ngay_sinh().get_date()), "dd/MM/yyyy"));
    if (lib.get_acc_sign_in().get_gioi_tinh() == 0){
        ui->gioi_tinh->setCurrentIndex(0);
    }
    else if (lib.get_acc_sign_in().get_gioi_tinh() == 1){
        ui->gioi_tinh->setCurrentIndex(1);
    }
    else{
        ui->gioi_tinh->setCurrentIndex(2);
    }
    QString soSachMuon = QString("%1/%2")
            .arg(lib.get_borrow_data().sach_dang_muon(lib.get_acc_sign_in().get_ID()))
            .arg(settings_file::getInstance()->get_so_quyen_muon_toi_da());
    ui->so_sach_muon->setText(soSachMuon);
}
void info::on_luu_thong_tin_clicked()
{
    string password_old = ui->mat_khau_hien_tai->text().trimmed().toStdString();
    if (password_old != lib.get_acc_sign_in().get_pass()){
        QMessageBox::warning(this, "Lỗi", "Mật khẩu hiện tại không đúng!");
        return;
    }
    
    string pass_new = ui->mat_khau_moi->text().trimmed().toStdString();
    string pass_confirm = ui->mat_khau_moi_again->text().trimmed().toStdString();
    if (pass_new != "" || pass_confirm != ""){
        if (pass_new != pass_confirm){
            QMessageBox::warning(this, "Lỗi", "Mật khẩu mới và xác nhận mật khẩu không khớp!");
        }
        else{
        lib.get_acc_sign_in().set_pass(pass_new);
        }
    }

    // Kiểm tra email đúng format
    string email = ui->email->text().trimmed().toStdString();
    QRegularExpression emailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.\\w+$");
    if (!emailRegex.match(QString::fromStdString(email)).hasMatch()){
        QMessageBox::warning(this, "Lỗi", "Email không đúng định dạng!");
        return;
    }
    
    // Kiểm tra số điện thoại đúng format (10-11 chữ số)
    string phone = ui->so_dien_thoai->text().trimmed().toStdString();
    QRegularExpression phoneRegex("^0\\d{9,10}$");
    if (!phoneRegex.match(QString::fromStdString(phone)).hasMatch()){
        QMessageBox::warning(this, "Lỗi", "Số điện thoại không đúng định dạng (phải bắt đầu bằng 0 và có 10-11 chữ số)!");
        return;
    }
    
    if( lib.get_account_data().check_ten_dang_nhap(ui->ten_dang_nhap->text().trimmed().toStdString()) &&
        ui->ten_dang_nhap->text().trimmed().toStdString() != lib.get_acc_sign_in().get_ten_dang_nhap()){
        QMessageBox::warning(this, "Lỗi", "Tên đăng nhập đã tồn tại!");
        return;
    }

    lib.get_acc_sign_in().set_ten_tai_khoan(ui->ho_va_ten->text().trimmed().toStdString());
    lib.get_acc_sign_in().set_email(email);
    lib.get_acc_sign_in().set_phone_number(phone);
    my_time ngay_sinh(ui->ngay_sinh->date().toString("dd/MM/yyyy").toStdString());
    lib.get_acc_sign_in().set_ngay_sinh(ngay_sinh);
    lib.get_acc_sign_in().set_gioi_tinh(ui->gioi_tinh->currentIndex());
    Account acc_new;
    acc_new = lib.get_acc_sign_in();
    lib.get_account_data().update(lib.get_acc_sign_in(), acc_new);
    ghi_Account(lib.get_account_data());
    record.log_action(lib.get_acc_sign_in().get_ten_dang_nhap(), ActionType::ADJ_USER, lib.get_acc_sign_in().get_ID(), "Cập nhật thông tin cá nhân");
    QMessageBox::information(this, "Thành công", "Cập nhật thông tin cá nhân thành công!");
}


void info::on_pushButton_3_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, 
        "Chọn ảnh đại diện", 
        "", 
        "Image Files (*.jpg *.png *.jpeg)");

    if (filePath.isEmpty()) {
        return;
    }

    QImage image(filePath);
    if (image.isNull()) {
        QMessageBox::warning(this, "Lỗi", "Không thể đọc file ảnh!");
        return;
    }

    QString newFileName = QString("../../anh_dai_dien/%1.png").arg(lib.get_acc_sign_in().get_ID());
    QDir dir;
    dir.mkpath("../../anh_dai_dien");

    if (!image.save(newFileName, "PNG")) {
        QMessageBox::warning(this, "Lỗi", "Không thể lưu ảnh!");
        return;
    }

    QMessageBox::information(this, "Thành công", "Đã cập nhật ảnh đại diện!");
    set_anh_dai_dien();
}


void info::on_pushButton_4_clicked()
{
    on_pushButton_3_clicked();
}

void info::on_dang_xuat_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Xác nhận đăng xuất",
        "Bạn có chắc chắn muốn đăng xuất?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        lib.dang_xuat_tai_khoan();
        QApplication::processEvents(); // Đảm bảo mọi sự kiện hiện tại được xử lý

        QWidget *parentWin = this->parentWidget();
        this->close();
        if (parentWin) {
            parentWin->close();
            auto win = new pbl2;
            win->setAttribute(Qt::WA_DeleteOnClose, true);
            win->show();
        }
    }
}

