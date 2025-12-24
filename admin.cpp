#include "admin.h"
#include "ui_admin.h"
#include "book.h"
#include "tree.h"
#include "global.h"
#include "library.h"
#include "history.h"
#include "add_book.h"
#include "info_book.h"
#include "muon_sach.h"
#include "my_string.h"
#include "phieu_tra_sach.h"
#include "dang_ky_dialog.h"
#include "Account.h"
#include "info_user.h"
#include "the_loai_chuyen_nganh.h"
#include "add_book_copy.h"
#include "my_time.h"
#include "settings_file.h"
#include "exception.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>
#include <QMenu>
#include <QToolTip>
#include <QCursor>
#include <QHeaderView>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QFrame>
#include <QTimer>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>

admin::admin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::admin)
{
    ui->setupUi(this);
    ui->name->setText(QString::fromStdString(lib.get_acc_sign_in().get_ten_tai_khoan()));
    string chuc_vu;
    if (lib.get_acc_sign_in().get_level() == "Admin"){
        chuc_vu = "Quản trị viên";
    } else if (lib.get_acc_sign_in().get_level() == "Librarian"){
        chuc_vu = "Thủ thư";
    } else {
        chuc_vu = "Độc giả";
    }
    ui->chuc_vu->setText(QString::fromStdString(chuc_vu));
    // Cấu hình bảng sách
    ui->sach_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->sach_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->sach_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    record.load_from_file();
    connect(ui->sach_table, &QTableWidget::cellClicked,
            this, &admin::on_sach_table_cellClicked);

    can_chinh_table(ui->sach_table);
    ui->sach_table->setContextMenuPolicy(Qt::CustomContextMenu);

    // Trang mặc định + hiển thị thống kê
    ui->noi_dung_layout->setCurrentIndex(0);
    QTimer::singleShot(0, this, [this](){
        this->set_anh_dai_dien();
        this->set_up_top_doc_nhieu_nhat();
        this->set_up_top_muon_nhieu_nhat();
    });
    this->hien_thi_thong_ke();
    this->set_thong_ke();
    // Load dữ liệu sách ban đầu
    add_book_(lib.get_book_data());
}

admin::~admin()
{
    delete ui;
}

void admin::set_anh_dai_dien(){
    QString id_path = QString::fromUtf8("../../anh_dai_dien/%1.png").arg(lib.get_acc_sign_in().get_ID());
    QString default_path = QString::fromUtf8("../../anh_dai_dien/anh_dai_dien.png");
    QString png_path = QFile::exists(id_path) ? id_path : default_path;

    // Tính size thật (nhân với PixelRatio để nét trên màn hình 2K/4K)
    QSize realSize = ui->anh_dai_dien->size() * ui->anh_dai_dien->devicePixelRatio();

    // GỌI HÀM MỚI cho anh_dai_dien
    QPixmap pix = load_image_pro(png_path, realSize, 15, true);
    pix.setDevicePixelRatio(ui->anh_dai_dien->devicePixelRatio());
    ui->anh_dai_dien->setPixmap(pix);
}

void admin::set_thong_ke(){
    int tong_sach = lib.get_book_data().count_data();
    int tong_ban_sao = lib.get_book_copy_data().count_data();
    int tong_doc_gia = lib.get_account_data().count_doc_gia();
    int tong_thu_thu = lib.get_account_data().count_thu_thu();
    int tong_chuyen_nganh = lib.get_chuyen_nganh_data().count_data();
    int tong_sach_ranh;
    int tong_sach_dat;
    int tong_sach_dang_muon;
    int tong_sach_qua_han;
    lib.get_borrow_data().tong_sach_dat_muon_qua_han(tong_sach_dat, tong_sach_dang_muon, tong_sach_qua_han);
    tong_sach_ranh = tong_ban_sao - tong_sach_dang_muon;
    int luot_xem_thang;
    int luot_muon_thang;
    int luot_tai_thang;
    my_time current_date = my_time::now();
    record.luot_xem_muon_tai_thang(current_date.get_month(), current_date.get_year(),
                              luot_xem_thang, luot_muon_thang, luot_tai_thang);
    ui->tong_sach_label->setText(QString::number(tong_sach));
    ui->ban_sao_label->setText(QString::number(tong_ban_sao) + " bản sao");
    ui->tong_doc_gia_label->setText(QString::number(tong_doc_gia));
    ui->tong_chuyen_nganh_label->setText(QString::number(tong_chuyen_nganh));
    ui->tong_sach_ranh_label->setText(QString::number(tong_sach_ranh));
    ui->tong_sach_dat_label->setText(QString::number(tong_sach_dat));
    ui->tong_sach_dang_muon_label->setText(QString::number(tong_sach_dang_muon));
    ui->tong_sach_qua_han_label->setText(QString::number(tong_sach_qua_han));
    ui->luot_xem_thang_label->setText(QString::number(luot_xem_thang));
    ui->tong_luot_muon_thang_label->setText(QString::number(luot_muon_thang));
    ui->tong_luot_tai_thang->setText(QString::number(luot_tai_thang));

}

void admin::hien_thi_thong_ke()
{
    QChartView *barChartLuotMuon = createLuotMuonChart();
    barChartLuotMuon->setMinimumHeight(300);
    ui->thong_ke_theo_nam_the_loai->addWidget(barChartLuotMuon);
    // Thêm đường thẳng đứng (Vertical Line) giữa 2 chart
    QFrame *vLine = new QFrame(this);
    vLine->setFrameShape(QFrame::VLine);
    vLine->setFrameShadow(QFrame::Sunken);
    ui->thong_ke_theo_nam_the_loai->addWidget(vLine);
    QChartView *pieChartTheLoai = createPhanboTheLoaiChart();
    ui->thong_ke_theo_nam_the_loai->addWidget(pieChartTheLoai);
}

QChartView* admin::createLuotMuonChart()
{
    // Tạo dữ liệu
    QBarSet *set0 = new QBarSet("Lượt mượn");
    int lmt[12] = {0};
    int lx, lt;
    my_time current_date = my_time::now();
    for (int i = 0; i < current_date.get_month(); i++) {
        record.luot_xem_muon_tai_thang(i + 1, current_date.get_year(), lx, lmt[i], lt);
        *set0 << lmt[i];
    }
    for (int i = current_date.get_month(); i < 12; i++) {
        *set0 << 0;
    }
    set0->setColor(QColor("#0088ff"));
    set0->setBorderColor(QColor("#0088ff"));

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    QObject::connect(set0, &QBarSet::hovered,
                     this, [=](bool status, int index){
        this->showBarToolTip(status, index, set0);
    });

    // Tạo chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Lượt mượn theo tháng");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(false);

    // Trục X
    QStringList categories;
    categories << "T1" << "T2" << "T3" << "T4" << "T5" << "T6"
               << "T7" << "T8" << "T9" << "T10" << "T11" << "T12";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Trục Y
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 0);
    axisY->setTickCount(5);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("border: 2px solid #e0e0e0; "
                             "border-radius: 12px; "
                             "background-color: white;");
    return chartView;
}

void admin::showBarToolTip(bool status, int index, QBarSet *barSet)
{
    if (status) {
        const QPoint globalPos = QCursor::pos();
        const QString value = QString::number(barSet->at(index));
        const QString text = QString("T%1\nluotMuon : %2")
                                 .arg(index + 1)
                                 .arg(value);
        QToolTip::showText(globalPos, text);
    } else {
        QToolTip::hideText();
    }
}

QChartView* admin::createPhanboTheLoaiChart()
{
    QPieSeries *series = new QPieSeries();

    int total = 0;

    lib.get_the_loai_data().traverse_ascending([&](The_loai &tl) {
        int count = lib.get_book_data().count_sach_theo_the_loai(tl.get_id());
        if (count > 0) {
            total += count;
            series->append(QString::fromStdString(tl.get_name()), count);
        }
    });

    if (total == 0) {
        auto chart = new QChart();
        chart->setTitle("Phân bổ theo thể loại (không có dữ liệu)");
        QChartView *emptyView = new QChartView(chart);
        emptyView->setRenderHint(QPainter::Antialiasing);
        return emptyView;
    }

    for (QPieSlice *slice : series->slices()) {
        double percent = slice->percentage() * 100.0;
        slice->setLabel(QString("%1: %2%").arg(slice->label()).arg(percent, 0, 'f', 1));
        slice->setLabelVisible(true);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Phân bổ theo thể loại");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setFont(QFont("Arial", 9));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("border: 2px solid #e0e0e0; "
                             "border-radius: 12px; "
                             "background-color: white;");
    return chartView;
}

void admin::can_chinh_table(QTableWidget *table)
{
    QHeaderView *header = table->horizontalHeader();
    header->setStretchLastSection(false);

    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(7, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(8, QHeaderView::ResizeToContents);

    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(2, QHeaderView::Stretch);
    header->setSectionResizeMode(3, QHeaderView::Stretch);
    header->setSectionResizeMode(4, QHeaderView::Stretch);
}

QTableWidgetItem* admin::makeCheckItem(bool value)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setCheckState(value ? Qt::Checked : Qt::Unchecked);
    item->setText("");
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

void admin::add_book_(BST_Book &Book)
{
    Book.traverse_ascending([this](book &b){
        add_book_to_table(ui->sach_table, &b);
    });
}

QWidget* admin::createStatusWidget(bool isOnline, bool isDownloadable)
{
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);
    QLabel *lblStatus = new QLabel();
    lblStatus->setAlignment(Qt::AlignCenter);

    if (isOnline) {
        lblStatus->setText("Online");
        lblStatus->setStyleSheet(
            "color: #28a745; font-weight: bold; font-size: 9px; text-align: center;");
    } else {
        lblStatus->setText("Offline");
        lblStatus->setStyleSheet(
            "color: gray; font-weight: bold; font-size: 9px; text-align: center;");
    }

    if (!isDownloadable) {
        layout->addWidget(lblStatus);
        layout->setContentsMargins(5, 5, 5, 5);
        layout->setSpacing(1);
        return container;
    }

    QLabel *lblDownload = new QLabel("Tải xuống");
    lblDownload->setAlignment(Qt::AlignCenter);
    lblDownload->setStyleSheet(
        "color: #007bff; font-weight: bold; font-size: 9px; text-align: center;");

    layout->addWidget(lblStatus);
    layout->addWidget(lblDownload);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(1);

    return container;
}

void admin::add_book_to_table(QTableWidget *table, book *b){
    int row = table->rowCount();
    table->insertRow(row);

    auto setText = [&](int col, const QString &text, bool center = false) {
        QTableWidgetItem *item = new QTableWidgetItem(text);
        if (center)
            item->setTextAlignment(Qt::AlignCenter);
        table->setItem(row, col, item);
    };
    setText(0, QString::number(b->get_ID()), true);
    setText(1, QString::fromStdString(b->get_Name()));
    setText(2, QString::fromStdString(b->get_Author()));
    setText(3, QString::fromStdString(b->get_The_loai_name()));
    setText(4, QString::fromStdString(b->get_Chuyen_nganh_name()));
    setText(5, QString::number(b->get_luot_xem()),true);
    setText(6, QString::number(b->get_luot_muon()),true);
    string tong_ranh = to_string(b->get_tong_sach_ranh()) + "/" + to_string(b->get_tong_sach());
    setText(7, QString::fromStdString(tong_ranh), true);
    table->setCellWidget(row, 8, createStatusWidget(b->get_is_Read_online(), b->get_is_Download()));
}

void admin::on_them_sach_button_clicked()
{
    add_book *win = new add_book(this);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
}

void admin::on_sach_table_cellClicked(int row, int /*column*/)
{
    QTableWidgetItem *idItem = ui->sach_table->item(row, 0);
    if (!idItem)
        return;

    long long id = idItem->text().toLongLong();
    Q_UNUSED(id);
    // Nếu muốn: mở info_book ở đây luôn
}

void admin::remove_table(QTableWidget *table)
{
    while (table->rowCount() > 0) {
        table->removeRow(0);
    }
}

void admin::on_lineEdit_textChanged(const QString &arg1)
{
    remove_table(ui->sach_table);

    if (arg1.isEmpty()) {
        add_book_(lib.get_book_data());
        return;
    }

    BST_Book kq_search;
    int type_the_loai = 0;   // 0: tất cả thể loại
    int type_tuy_chon = 0;   // 0: có chứa
    int type_bieu_ghi = 1;   // 1: tên sách
    std::string key_word = arg1.toStdString();

    lib.get_book_data().search(type_the_loai, type_tuy_chon, type_bieu_ghi,
                     key_word, lib.get_book_data(), kq_search);
    add_book_(kq_search);
}

void admin::on_sach_table_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu(this);

    int row = ui->sach_table->rowAt(pos.y());
    if (row < 0)
        return;

    QTableWidgetItem *idItem = ui->sach_table->item(row, 0);
    if (!idItem)
        return;

    long long id = idItem->text().toLongLong();

    QAction *actXem  = menu.addAction("Xem chi tiết");
    QAction *actSua  = menu.addAction("Sửa thông tin");
    QAction *actXoa  = menu.addAction("Xóa sách");

    QAction *chosen = menu.exec(ui->sach_table->viewport()->mapToGlobal(pos));
    if (!chosen)
        return;

    book selectedBook;
    if (!lib.get_book_data().find(id, selectedBook)) {
        return;
    }

    if (chosen == actXem) {
        info_book *win = new info_book(selectedBook, this);
        win->setAttribute(Qt::WA_DeleteOnClose, true);
        win->show();
    } else if (chosen == actSua) {
        add_book *win = new add_book(this);
        win->setAttribute(Qt::WA_DeleteOnClose, true);
        win->set_up_chinh_sua_mode(selectedBook);
        win->show();
        connect(win, &add_book::destroyed, this, [this]() {
            remove_table(ui->sach_table);
            add_book_(lib.get_book_data());
        });
    } else if (chosen == actXoa) {
        QMessageBox::StandardButton reply =
            QMessageBox::question(
                this,
                "Xác nhận xóa",
                "Bạn có chắc chắn muốn xóa sách:\n" +
                QString::number(id) + " - " +
                QString::fromStdString(selectedBook.get_Name()),
                QMessageBox::Yes | QMessageBox::No
            );

        if (reply != QMessageBox::Yes)
            return;

        try {
            lib.xoa_sach_va_ban_sao(id);
            QMessageBox::information(
                this,
                "Thành công",
                "Đã xóa sách và các bản sao thành công."
            );

            remove_table(ui->sach_table);
            add_book_(lib.get_book_data());
        }
        catch (AppException &e) {
            QMessageBox::warning(
                this,
                QString::fromStdString(e.getTitle()),
                QString::fromStdString(e.what())
            );
        }
    }
}

void admin::on_thong_ke_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(0);

    reset_side_buttons_style();

    ui->thong_ke_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");
}
void admin::reset_side_buttons_style()
{
    const char *inactiveStyle =
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;";

    ui->thong_ke_button->setStyleSheet(inactiveStyle);
    ui->dau_sach_button->setStyleSheet(inactiveStyle);
    ui->ban_sao_button->setStyleSheet(inactiveStyle);
    ui->doc_gia_button->setStyleSheet(inactiveStyle);
    ui->muon_tra_button->setStyleSheet(inactiveStyle);
    ui->thu_thu_button->setStyleSheet(inactiveStyle);
    ui->lich_su_button->setStyleSheet(inactiveStyle);
    ui->cai_dat_button->setStyleSheet(inactiveStyle);
}
void admin::on_dau_sach_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(1);

    reset_side_buttons_style();

    ui->dau_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");

    int i = 0;
    int j = 0;
    ui->the_loai_combo->clear();
    ui->chuyen_nganh_combo->clear();
    ui->the_loai_combo->addItem("Tất cả thể loại");
    ui->the_loai_combo->setProperty("status", i++);
    ui->chuyen_nganh_combo->addItem("Tất cả chuyên ngành");
    ui->chuyen_nganh_combo->setProperty("status", j++);

    lib.get_chuyen_nganh_data().traverse_ascending([this, &j](Chuyen_nganh &cn){
        ui->chuyen_nganh_combo->addItem(QString::fromStdString(cn.get_name()));
        ui->chuyen_nganh_combo->setProperty("status", j++);
    });
    lib.get_the_loai_data().traverse_ascending([this, &i](The_loai &tl){
        ui->the_loai_combo->addItem(QString::fromStdString(tl.get_name()));
        ui->the_loai_combo->setProperty("status", i++);
    });
}

void admin::closeEvent(QCloseEvent *event)
{
    QWidget *parentWin = this->parentWidget();
    if (parentWin) {
        parentWin->show();
    }
    this->deleteLater();
    event->accept();
}

void admin::on_muon_tra_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(5);
    ui->quan_ly_muon_tra_hien_thi->setCurrentIndex(0);
    cau_hinh_dat_sach();

    reset_side_buttons_style();

    ui->muon_tra_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");
}

void admin::cau_hinh_dat_sach(){
    ui->dat_sach_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dat_sach_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->dat_sach_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->dat_sach_table->setContextMenuPolicy(Qt::CustomContextMenu);
    QHeaderView *header = ui->dat_sach_table->horizontalHeader();
    header->setStretchLastSection(false);

    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents);

    header->setSectionResizeMode(0, QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    BST_Borrow b;
    b.tim_sach_dat_thu_thu(b);
    int tong;
    int cho_xu_ly;
    int san_sang;
    int qua_han;
    b.thong_ke_sach_dat(cho_xu_ly, san_sang, qua_han, b);
    tong = cho_xu_ly + san_sang + qua_han;
    ui->tat_ca_number->setText(QString::number(tong));
    ui->xu_ly_number->setText(QString::number(cho_xu_ly));
    ui->san_sang_number->setText(QString::number(san_sang));
    ui->qua_han_number->setText(QString::number(qua_han));

    hien_thi_sach_dat(b);
}
void admin::hien_thi_sach_dat(BST_Borrow &b){
    remove_table(ui->dat_sach_table);
    b.traverse_ascending([this](borrow &br){
        int row = ui->dat_sach_table->rowCount();
        ui->dat_sach_table->insertRow(row);

        auto setText = [&](int col, const QString &text, bool center = false) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            if (center)
                item->setTextAlignment(Qt::AlignCenter);
            ui->dat_sach_table->setItem(row, col, item);
        };
        setText(0, QString::fromStdString((br.get_user_name())));
        setText(1, QString::fromStdString(br.get_book_name()));
        setText(2, QString::fromStdString(br.get_ngay_dat().get_date()), true);
        setText(3, QString::fromStdString((br.get_ngay_dat() + 3).get_date()), true);
        string trang_thai;
        if (br.get_status() == StatusType::XU_LY)
            trang_thai = "Chờ xử lý";
        else if (br.get_status() == StatusType::SAN_SANG)
            trang_thai = "Sẵn sàng";
        else if (br.get_status() == StatusType::QUA_HAN_DAT)
            trang_thai = "Quá hạn đặt";
        else
            trang_thai = "Hủy đặt";
        ui->dat_sach_table->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(trang_thai)));
        ui->dat_sach_table->setCellWidget(row, 4, createStatusDatWidget(br.get_status(),0));
        ui->dat_sach_table->setCellWidget(row, 5, createNutDatWidget(br.get_status(), br.get_id()));
    });
}
QWidget* admin::createStatusDatWidget(StatusType trang_thai, int days = 0)
{
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);
    QLabel *lblStatus = new QLabel();
    lblStatus->setAlignment(Qt::AlignCenter);
    switch (trang_thai)
    {
    case StatusType::XU_LY:
        lblStatus->setText("Chờ xử lý");
        lblStatus->setStyleSheet(
            "QPushButton {"
            "   background-color: #e0e0e0;"
            "   color: #333333;"
            "   border: 1px solid #bfbfbf;"
            "   border-radius: 10px;"
            "   font-weight: bold;"
            "   font-size: 11px;"
            "   padding: 2px 8px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #d0d0d0;"
            "}"
        );
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

QWidget* admin::createNutDatWidget(StatusType trang_thai,long long id)
{
    QWidget *container = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(container);
    QPushButton *lblNut = new QPushButton();
    if (trang_thai == StatusType::XU_LY || trang_thai == StatusType::SAN_SANG) {
        QPushButton *lblNut = new QPushButton();
        lblNut->setProperty("ID", QString::number(id));

        if (trang_thai == StatusType::XU_LY) {
            lblNut->setText("Xử lý");
            lblNut->setStyleSheet("color: #007c00; font-weight: bold; font-size: 11px; text-align: center;background-color:  #f7fbff;border: 2px solid #007c00;padding: 2px 8px;");
            lblNut->setCursor(Qt::PointingHandCursor);
            connect(lblNut, &QPushButton::clicked, this, &admin::onXuLyClicked);
        } else if (trang_thai == StatusType::SAN_SANG) {
            lblNut->setText("Xác nhận");
            lblNut->setStyleSheet("color: blue; font-weight: bold; font-size: 11px; text-align: center;background-color:  #f7fbff;border: 2px solid blue;padding: 2px 8px;");
            lblNut->setCursor(Qt::PointingHandCursor);
            connect(lblNut, &QPushButton::clicked, this, &admin::onXacNhanClicked);
        }
        layout->addWidget(lblNut);
    }
    QPushButton *Xoa = new QPushButton();
    Xoa->setText("Xóa");
    Xoa->setProperty("ID", QString::number(id));
    Xoa->setStyleSheet( "color: red; font-weight: bold; font-size: 12px; text-align: center;background-color:  #f7fbff;border: 2px solid red;padding: 2px 8px;");
    Xoa->setCursor(Qt::PointingHandCursor);
    connect(Xoa, &QPushButton::clicked, this, &admin::onXoaDatSachClicked);
    layout->addWidget(Xoa);
    layout->setContentsMargins(5,5,5,5);
    layout->setSpacing(5);
    return container;
}

void admin::onXuLyClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    long long id = button->property("ID").toLongLong();
    try{
        lib.xu_ly_sach(id);
    } catch (AppException &e){
        QMessageBox::warning(this, "Lỗi", QString::fromStdString(e.what()));
        return;
    }
    cau_hinh_dat_sach();
}
void admin::onXacNhanClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    long long id = button->property("ID").toLongLong();

    borrow br;
    if (!lib.get_borrow_data().find(id, br)) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy yêu cầu đặt.");
        return;
    }

    auto win = new muon_sach(br, this);
    win->set_up_xu_ly_muon_sach();
    win->setWindowModality(Qt::ApplicationModal);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();

    connect(win, &muon_sach::muon_sach_thanh_cong,
        this, [this, id, win]() {
        QMessageBox::information(
            this,
            "Thành công",
            "Xác nhận mượn sách thành công."
        );

        cau_hinh_dat_sach();
        cau_hinh_muon_sach();
        });
}
void admin::onXoaDatSachClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;

    long long id = button->property("ID").toLongLong();

    QMessageBox::StandardButton reply =
        QMessageBox::question(
            this,
            "Xác nhận hủy đặt",
            "Bạn có chắc chắn muốn hủy yêu cầu đặt sách này?",
            QMessageBox::Yes | QMessageBox::No
        );

    if (reply != QMessageBox::Yes)
        return;

    try {
        lib.huy_dat_sach(id);

        QMessageBox::information(
            this,
            "Thành công",
            "Đã hủy đặt sách thành công."
        );

        cau_hinh_dat_sach();
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


void admin::on_dat_sach_button_clicked()
{
    ui->quan_ly_muon_tra_hien_thi->setCurrentIndex(0);
    cau_hinh_dat_sach();
    ui->dat_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");
    ui->muon_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->tra_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
}


void admin::on_muon_sach_button_clicked()
{
    ui->quan_ly_muon_tra_hien_thi->setCurrentIndex(1);
    ui->muon_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");
    ui->dat_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->tra_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    cau_hinh_muon_sach();
}


void admin::on_tra_sach_button_clicked()
{
    ui->quan_ly_muon_tra_hien_thi->setCurrentIndex(2);
    cau_hinh_tra_sach();
    ui->tra_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");
    ui->dat_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->muon_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
}


void admin::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString chon_loc = arg1;
    int column = 4;
    int rowCount = ui->dat_sach_table->rowCount();
    for (int i = 0; i < rowCount ; i++){
        if (chon_loc == "Tất cả trạng thái"){
            ui->dat_sach_table->setRowHidden(i, false);
            continue;
        }
        QTableWidgetItem *item = ui->dat_sach_table->item(i, column);
        if (item) {
            if (item->text().trimmed() == chon_loc) {
                ui->dat_sach_table->setRowHidden(i, false);
            } else {
                ui->dat_sach_table->setRowHidden(i, true);
            }
        }
    }
}


void admin::on_tim_kiem_dat_textChanged(const QString &arg1)
{
    QString keyword = QString::fromStdString(xoa_dau_lower(arg1.trimmed().toLower().toStdString()));
    int rowCount = ui->dat_sach_table->rowCount();
    if (keyword.isEmpty()) {
        for (int i = 0; i < rowCount; ++i) {
            ui->dat_sach_table->setRowHidden(i, false);
        }
        return;
    }

    for (int i = 0; i < rowCount; ++i) {
        bool match = false;
        for (int j = 0; j < 2; ++j) {
            QTableWidgetItem *item = ui->dat_sach_table->item(i, j);
            if (item) {
                QString itemText = QString::fromStdString(xoa_dau_lower(item->text().toLower().toStdString()));
                if (itemText.contains(keyword)) {
                    match = true;
                    break;
                }
            }
        }
        ui->dat_sach_table->setRowHidden(i, !match);
    }
}


void admin::cau_hinh_muon_sach(){
    ui->muon_sach_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->muon_sach_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->muon_sach_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->muon_sach_table->setContextMenuPolicy(Qt::CustomContextMenu);
    QHeaderView *header = ui->muon_sach_table->horizontalHeader();
    header->setStretchLastSection(false);

    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(6, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(7, QHeaderView::ResizeToContents);

    header->setSectionResizeMode(0, QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    BST_Borrow b;
    b.tim_sach_muon_thu_thu(b);
    int dang_muon;
    int qua_han;
    b.thong_ke_sach_muon(dang_muon, qua_han, b);
    ui->dang_muon_number->setText(QString::number(dang_muon));
    ui->qua_han_number_2->setText(QString::number(qua_han));

    hien_thi_sach_muon(b);
}

void admin::hien_thi_sach_muon(BST_Borrow &b){
    remove_table(ui->muon_sach_table);
    b.traverse_ascending([this](borrow &br){
        int row = ui->muon_sach_table->rowCount();
        ui->muon_sach_table->insertRow(row);


        auto setText = [&](int col, const QString &text, bool center = false) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            if (center)
                item->setTextAlignment(Qt::AlignCenter);
            ui->muon_sach_table->setItem(row, col, item);
        };
        setText(0, QString::fromStdString(to_stringll_(br.get_user_id()) + " - " + (br.get_user_name())));
        setText(1, QString::fromStdString(to_stringll_(br.get_book_id()) + " - " + br.get_book_name()));
        setText(2, QString::fromStdString("BS-" + to_stringll_(br.get_book_copy_id())), true);
        setText(3, QString::fromStdString(br.get_ngay_muon().get_date()), true);
        setText(4, QString::fromStdString(br.get_ngay_phai_tra().get_date()), true);
        string trang_thai;
        if (br.get_status() == StatusType::DANG_MUON)
            trang_thai = "Đang mượn";
        else if (br.get_status() == StatusType::QUA_HAN_MUON)
            trang_thai = "Quá hạn mượn";
        string so_gia_han = to_string(br.get_lan_gia_han()) + "/" + to_string(settings_file::getInstance()->get_so_lan_gia_han());
        setText(5, QString::fromStdString(so_gia_han), true);
        ui->muon_sach_table->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(trang_thai)));
        ui->muon_sach_table->setCellWidget(row, 6, createStatusDatWidget(br.get_status(), 0));
        ui->muon_sach_table->setCellWidget(row, 7, createNutMuonWidget(br.get_status(), br.get_id()));
    });
}

QWidget* admin::createNutMuonWidget(StatusType trang_thai,long long id){
    QWidget *container = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(container);
    borrow br;
    book bk;
    if (!lib.get_borrow_data().find(id, br)) {
        return container;
    }
    lib.get_book_data().find(br.get_book_id(), bk);
    qDebug() << "So lan gia han: " << br.get_lan_gia_han();
    qDebug() << "So lan gia han cho phep: " << settings_file::getInstance()->get_so_lan_gia_han();
    qDebug() << "Tong sach ranh: " << bk.get_tong_sach_ranh();
    if (br.get_lan_gia_han() < settings_file::getInstance()->get_so_lan_gia_han() && bk.get_tong_sach_ranh() > 0){
        QPushButton *lblNut = new QPushButton();
        lblNut->setProperty("ID", QString::number(id));

        lblNut->setText("Gia hạn");
        lblNut->setStyleSheet("color: #007c00; font-weight: bold; font-size: 11px; text-align: center;background-color:  #f7fbff;border: 2px solid #007c00;padding: 2px 8px;");
        lblNut->setCursor(Qt::PointingHandCursor);
        connect(lblNut, &QPushButton::clicked, this, &admin::onGiaHanSachClicked);

        layout->addWidget(lblNut);
        layout->setContentsMargins(5,5,5,5);
        layout->setSpacing(5);
    }
    QPushButton *XemMuon = new QPushButton();
    XemMuon->setText("Xem");
    XemMuon->setProperty("ID", QString::number(id));
    XemMuon->setStyleSheet( "color: #007bff; font-weight: bold; font-size: 12px; text-align: center;background-color:  #f7fbff;border: 2px solid #007bff;padding: 2px 8px;");
    XemMuon->setCursor(Qt::PointingHandCursor);
    connect(XemMuon, &QPushButton::clicked, this, &admin::onXemChiTietMuonClicked);
    layout->addWidget(XemMuon);
    layout->setContentsMargins(5,5,5,5);
    return container;
}

void admin::onGiaHanSachClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    long long id = button->property("ID").toLongLong();

    try {
        lib.gia_han_muon_sach_(id);

        QMessageBox::information(
            this,
            "Thành công",
            "Gia hạn sách thành công."
        );

        cau_hinh_muon_sach();
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

void admin::onXemChiTietMuonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    long long id = button->property("ID").toLongLong();

    borrow br;
    if (!lib.get_borrow_data().find(id, br)) {
        return;
    }
    auto win = new muon_sach(br, this);
    win->set_up_borrow_info();
    win->setWindowModality(Qt::ApplicationModal);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
}

void admin::on_nhan_tra_clicked()
{

}


void admin::on_phieu_tra_sach_button_clicked()
{
    auto win = new phieu_tra_sach(this);
    win->setWindowModality(Qt::ApplicationModal);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
    connect(win, &phieu_tra_sach::tra_sach_thanh_cong, this, [this]() {
        cau_hinh_tra_sach();
        });
}

void admin::cau_hinh_tra_sach(){
    ui->tra_sach_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tra_sach_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tra_sach_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tra_sach_table->setContextMenuPolicy(Qt::CustomContextMenu);
    QHeaderView *header = ui->tra_sach_table->horizontalHeader();
    header->setStretchLastSection(false);

    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(7, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(8, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(9, QHeaderView::ResizeToContents);


    header->setSectionResizeMode(0, QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    BST_Borrow b;
    b.tim_sach_tra_thu_thu(b);
    int tong_sach_tra;
    int tra_qua_han;
    int hu_hong_mat;
    long long tong_tien_phat;

    b.thong_ke_sach_tra(tong_sach_tra, tra_qua_han, hu_hong_mat, tong_tien_phat, b);
    ui->tong_luot_tra_number->setText(QString::number(tong_sach_tra));
    ui->tra_tre_number->setText(QString::number(tra_qua_han));
    ui->hu_hong_mat_number->setText(QString::number(hu_hong_mat));
    ui->tong_phat_number->setText(QString::fromStdString(tien_te_vnd(tong_tien_phat)) + " VND");

    hien_thi_sach_tra(b);
}

void admin::hien_thi_sach_tra(BST_Borrow &b){
    remove_table(ui->tra_sach_table);
    b.traverse_ascending([this](borrow &br){
        int row = ui->tra_sach_table->rowCount();
        ui->tra_sach_table->insertRow(row);

        auto setText = [&](int col, const QString &text, bool center = false) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            if (center)
                item->setTextAlignment(Qt::AlignCenter);
            ui->tra_sach_table->setItem(row, col, item);
        };
        setText(0, QString::fromStdString(to_stringll_(br.get_user_id()) + " - " + br.get_user_name()));
        setText(1, QString::fromStdString(to_stringll_(br.get_book_id()) + " - " + br.get_book_name()));
        setText(2, "BS-" + QString::number(br.get_book_copy_id()), true);
        setText(3, QString::fromStdString(br.get_ngay_muon().get_date()), true);
        setText(4, QString::fromStdString(br.get_ngay_phai_tra().get_date()), true);
        setText(5, QString::fromStdString(br.get_ngay_tra().get_date()), true);
        int so_ngay_qua_han = (br.get_ngay_tra() - br.get_ngay_phai_tra()).get_day();
        ui->tra_sach_table->setCellWidget(row, 6, createStatusDatWidget(br.get_status(), so_ngay_qua_han));
        ui->tra_sach_table->setCellWidget(row, 7, createTinhTrangWidget(br.get_tinh_trang_sach(), br.get_id()));
        setText(8, QString::fromStdString(tien_te_vnd(br.get_tien_phat()) + " VND"), true);
        ui->tra_sach_table->setCellWidget(row, 9, createNutXemTraWidget(br.get_id()));
    });
}

QWidget* admin::createTinhTrangWidget(TinhTrangsach tinh_trang, long long id)
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

QWidget* admin::createNutXemTraWidget(long long id){
    QWidget *container = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(container);
    QPushButton *XemTra = new QPushButton();
    XemTra->setText("Xem");
    XemTra->setProperty("ID", QString::number(id));
    XemTra->setStyleSheet( "color: #007bff; font-weight: bold; font-size: 11px; text-align: center;background-color:  #f7fbff;border: 2px solid #007bff;padding: 2px 8px;");
    XemTra->setCursor(Qt::PointingHandCursor);
    layout->addWidget(XemTra);
    connect(XemTra, &QPushButton::clicked, this, &admin::onXemChiTietTraClicked);
    layout->setContentsMargins(5,5,5,5);
    return container;
}

void admin::onXemChiTietTraClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    long long id = button->property("ID").toLongLong();

    borrow br;
    if (!lib.get_borrow_data().find(id, br)) {
        return;
    }
    //info_borrow *win = new info_borrow(br, this);
    //win->setAttribute(Qt::WA_DeleteOnClose, true);
    //win->show();
}

void admin::on_comboBox_2_currentIndexChanged(int index)
{
    int rowCount = ui->muon_sach_table->rowCount();
    for (int i = 0; i < rowCount ; i++){
        if (index == 0){
            ui->muon_sach_table->setRowHidden(i, false);
            continue;
        }
        QWidget *widget = ui->muon_sach_table->cellWidget(i, 6);
        if (widget) {
            QLabel *lblStatus = widget->findChild<QLabel*>();
            if (lblStatus) {
                int status = lblStatus->property("status").toInt();
                if (status - 3 == index) {
                    ui->muon_sach_table->setRowHidden(i, false);
                } else {
                    ui->muon_sach_table->setRowHidden(i, true);
                }
            }
        }
    }
}


void admin::on_trang_thai_tra_activated(int index)
{
    int rowCount = ui->tra_sach_table->rowCount();
    for (int i = 0; i < rowCount ; i++){
        if (index == 0){
            ui->tra_sach_table->setRowHidden(i, false);
            continue;
        }
        QWidget *widget = ui->tra_sach_table->cellWidget(i, 7);
        if (widget) {
            QLabel *lblStatus = widget->findChild<QLabel*>();
            if (lblStatus) {
                int status = lblStatus->property("status").toInt();
                if (status + 1 == index) {
                    ui->tra_sach_table->setRowHidden(i, false);
                } else {
                    ui->tra_sach_table->setRowHidden(i, true);
                }
            }
        }
    }
}


void admin::on_tim_kiem_muon_textChanged(const QString &arg1)
{
    QString keyword = QString::fromStdString(xoa_dau_lower(arg1.trimmed().toLower().toStdString()));
    int rowCount = ui->muon_sach_table->rowCount();
    if (keyword.isEmpty()) {
        for (int i = 0; i < rowCount; ++i) {
            ui->muon_sach_table->setRowHidden(i, false);
        }
        return;
    }

    for (int i = 0; i < rowCount; ++i) {
        bool match = false;
        for (int j = 0; j < 4; ++j) {
            QTableWidgetItem *item = ui->muon_sach_table->item(i, j);
            if (item) {
                QString itemText = QString::fromStdString(xoa_dau_lower(item->text().toLower().toStdString()));
                if (itemText.contains(keyword)) {
                    match = true;
                    break;
                }
            }
        }
        ui->muon_sach_table->setRowHidden(i, !match);
    }
}


void admin::on_tim_kiem_tra_textChanged(const QString &arg1)
{
    QString keyword = QString::fromStdString(xoa_dau_lower(arg1.trimmed().toLower().toStdString()));
    int rowCount = ui->tra_sach_table->rowCount();
    if (keyword.isEmpty()) {
        for (int i = 0; i < rowCount; ++i) {
            ui->tra_sach_table->setRowHidden(i, false);
        }
        return;
    }

    for (int i = 0; i < rowCount; ++i) {
        bool match = false;
        for (int j = 0; j < 3; ++j) {
            QTableWidgetItem *item = ui->tra_sach_table->item(i, j);
            if (item) {
                QString itemText = QString::fromStdString(xoa_dau_lower(item->text().toLower().toStdString()));
                if (itemText.contains(keyword)) {
                    match = true;
                    break;
                }
            }
        }
        ui->tra_sach_table->setRowHidden(i, !match);
    }
}

void admin::cau_hinh_ban_sao(){
    ui->ban_sao_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ban_sao_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ban_sao_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ban_sao_table->setContextMenuPolicy(Qt::CustomContextMenu);
    QHeaderView *header = ui->ban_sao_table->horizontalHeader();
    header->setStretchLastSection(false);

    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);
}

void admin::on_ban_sao_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(2);

    // Sử dụng hàm reset_side_buttons_style thay vì set thủ công từng nút
    reset_side_buttons_style();

    ui->ban_sao_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");

    cau_hinh_ban_sao();
    ui->dau_sach->clear();
    string s;
    lib.get_book_data().traverse_ascending([this,&s](book &bk){
        s = to_stringll_(bk.get_ID()) + " - " + bk.get_Name();
        ui->dau_sach->addItem(QString::fromStdString(s), QVariant::fromValue(bk.get_ID()));
    });
    BST_book_copy bc;
    bc.copies_of_book(ui->dau_sach->currentData().toLongLong(), bc);
    hien_thi_ban_sao(bc);
}

void admin::hien_thi_ban_sao(BST_book_copy &bc){
    remove_table(ui->ban_sao_table);
    book b;
    lib.get_book_data().find(ui->dau_sach->currentData().toLongLong(), b);
    bc.traverse_ascending([this,&b](Book_copies &br){
        int row = ui->ban_sao_table->rowCount();
        ui->ban_sao_table->insertRow(row);

        auto setText = [&](int col, const QString &text, bool center = false) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            QFont font = item->font();
            font.setPointSize(10);
            font.setBold(true);
            item->setFont(font);
            if (center)
            item->setTextAlignment(Qt::AlignCenter);
            ui->ban_sao_table->setItem(row, col, item);
        };
        setText(0, QString::fromStdString( "BS-" + to_string(br.get_id())),true);
        setText(1, QString::fromStdString(to_string(br.get_id_book()) + " - " + b.get_Name()));
        if (br.get_status() == "available")
            setText(2, "Sẵn sàng", true);
        else if (br.get_status() == "DA_MUON")
            setText(2, "Đang mượn", true);
        else if (br.get_status() == "damaged")
            setText(2, "Hư hỏng", true);
        else if (br.get_status() == "lost")
            setText(2, "Mất", true);
        else
        setText(2, QString::fromStdString(br.get_status()), true);
        ui->ban_sao_table->setCellWidget(row, 3, createNutXoaWidget(br.get_id()));
    });
}
void admin::on_dau_sach_currentIndexChanged(int index)
{
    long long id_dau_sach = ui->dau_sach->itemData(index).toLongLong();
    BST_book_copy bc;
    bc.copies_of_book(id_dau_sach, bc);
    hien_thi_ban_sao(bc);
}
QWidget* admin::createNutXoaWidget(long long id){
    QWidget *container = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(container);
    QPushButton *Xoa = new QPushButton();
    Xoa->setText("Xóa");
    Xoa->setProperty("ID", QString::number(id));
    Xoa->setStyleSheet( "color: red; font-weight: bold; font-size: 11px; text-align: center;background-color:  #f7fbff;border: 2px solid red;padding: 2px 8px;");
    Xoa->setCursor(Qt::PointingHandCursor);
    connect(Xoa, &QPushButton::clicked, this, &admin::onXoaBanSaoClicked);
    layout->addWidget(Xoa);
    layout->setContentsMargins(5,5,5,5);
    return container;
}

void admin::onXoaBanSaoClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    long long id = button->property("ID").toLongLong();

    // Tìm thông tin bản sao để hiển thị tên
    Book_copies bc;
    if (!lib.get_book_copy_data().find(id, bc)) {
        return;
    }

    book b;
    if (!lib.get_book_data().find(bc.get_id_book(), b)) {
        return;
    }

    QString ten_ban_sao = QString::fromStdString("BS-" + to_string(id) + " - " + b.get_Name());

    // Hiển thị hộp thoại xác nhận
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận xóa",
                                   "Bạn có chắc chắn muốn xóa bản sao:\n" + ten_ban_sao + "?",
                                   QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        lib.get_book_copy_data().remove_by_Key(id);
        ghi_copy_book(lib.get_book_copy_data());
        BST_book_copy bc_list;
        bc_list.copies_of_book(ui->dau_sach->currentData().toLongLong(), bc_list);
        hien_thi_ban_sao(bc_list);
        record.log_action(lib.get_acc_sign_in().get_ten_dang_nhap(), ActionType::REMOVE_BOOK_COPY, id, "Đã xóa bản sao " + to_stringll_(b.get_ID()) + " - " + b.get_Name());
        QMessageBox::information(this, "Xóa thành công", "Bản sao đã được xóa thành công.");
    }
}

void admin::on_thu_thu_button_clicked()
{

    reset_side_buttons_style();

    ui->thu_thu_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");
    if (lib.get_acc_sign_in().get_level() != "Admin"){
        ui->noi_dung_layout->setCurrentIndex(8);
        return;
    }
    ui->noi_dung_layout->setCurrentIndex(4);
    cau_hinh_thu_thu();
    BST_Account u;
    lib.get_account_data().tim_thu_thu(u);
    hien_thi_thu_thu(u);
}

void admin::cau_hinh_thu_thu(){
    ui->thu_thu_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->thu_thu_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->thu_thu_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->thu_thu_table->setContextMenuPolicy(Qt::CustomContextMenu);
    QHeaderView *header = ui->thu_thu_table->horizontalHeader();
    header->setStretchLastSection(false);
    header->setSectionResizeMode(3, QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(6, QHeaderView::ResizeToContents);
}

void admin::hien_thi_thu_thu(BST_Account &u){
    remove_table(ui->thu_thu_table);
    u.traverse_ascending([this](Account &ac){
        int row = ui->thu_thu_table->rowCount();
        ui->thu_thu_table->insertRow(row);

        auto setText = [&](int col, const QString &text, bool center = false) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            QFont font = item->font();
            font.setPointSize(10);
            font.setBold(true);
            item->setFont(font);
            if (center)
            item->setTextAlignment(Qt::AlignCenter);
            ui->thu_thu_table->setItem(row, col, item);
        };
        setText(0, QString::fromStdString(ac.get_ten_dang_nhap()));
        setText(1, QString::fromStdString((ac.get_ten_tai_khoan())));
        setText(2, QString::fromStdString(ac.get_phone_number()), true);
        setText(3, QString::fromStdString((ac.get_email())));
        setText(4, QString::fromStdString("Trực tuyến"));
        setText(5, QString::fromStdString(ac.get_level()), true);
        ui->thu_thu_table->setCellWidget(row, 6, createNutThongTinUserWidget(ac.get_ID()));
    });
}
void admin::on_them_doc_gia_clicked()
{
    auto win = new dang_ky_dialog(this);
    //win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->set_up_register_mode("User");
    win->show();
    connect(win, &dang_ky_dialog::registered, this, [this, win](const Account& user) {
        this->on_doc_gia_button_clicked();
    });
}


void admin::on_them_thu_thu_clicked()
{
    auto win = new dang_ky_dialog(this);
    //win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->set_up_register_mode("Librarian");
    win->show();
    connect(win, &dang_ky_dialog::registered, this, [this, win](const Account& user) {
        this->on_thu_thu_button_clicked();
    });
}

QWidget* admin::createNutThongTinUserWidget(long long user_id) {
    QWidget *container = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(container);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(8);

    QPushButton *btnXem = new QPushButton("Xem");
    btnXem->setProperty("UserID", QString::number(user_id));
    btnXem->setCursor(Qt::PointingHandCursor);
    btnXem->setStyleSheet(
        "color: #0d6efd; font-weight: bold; font-size: 11px;"
        "background-color: #f7fbff; border: 2px solid #0d6efd;"
        "padding: 2px 10px; border-radius: 6px;");
    connect(btnXem, &QPushButton::clicked, this, &admin::onXemThongTinUserClicked);
    layout->addWidget(btnXem);

    QPushButton *btnXoa = new QPushButton("Xóa");
    btnXoa->setProperty("UserID", QString::number(user_id));
    btnXoa->setCursor(Qt::PointingHandCursor);
    btnXoa->setStyleSheet(
        "color: #dc3545; font-weight: bold; font-size: 11px;"
        "background-color: #fff5f5; border: 2px solid #dc3545;"
        "padding: 2px 10px; border-radius: 6px;");
    connect(btnXoa, &QPushButton::clicked, this, &admin::onXoaUserClicked);
    layout->addWidget(btnXoa);

    return container;
}

void admin::onXemThongTinUserClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    long long user_id = button->property("UserID").toLongLong();

    Account ac;
    if (!lib.get_account_data().find(user_id, ac)) {
        return;
    }

    auto win = new info_user(ac, this);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
}

void admin::onXoaUserClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    long long user_id = button->property("UserID").toLongLong();

    Account ac;
    if (!lib.get_account_data().find(user_id, ac)) {
        return;
    }

    QString ten_user = QString::fromStdString(ac.get_ten_tai_khoan());
    string level = ac.get_level();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận xóa",
                                   "Bạn có chắc chắn muốn xóa người dùng:\n" + ten_user + "?",
                                   QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        lib.get_account_data().remove_by_Key(user_id);
        ghi_Account(lib.get_account_data());
        this->on_doc_gia_button_clicked();
        record.log_action(lib.get_acc_sign_in().get_ten_dang_nhap(), ActionType::ADJ_USER, user_id, "Đã xóa người dùng " + ac.get_ten_tai_khoan());
        QMessageBox::information(this, "Xóa thành công", "Người dùng đã được xóa thành công.");
        if (level == "Librarian") {
            this->on_thu_thu_button_clicked();
        }
        else {
            this->on_doc_gia_button_clicked();
        }
    }
}

void admin::on_doc_gia_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(3);

    // Dùng hàm reset chung
    reset_side_buttons_style();

    ui->doc_gia_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");

    cau_hinh_doc_gia();
    BST_Account u;
    lib.get_account_data().tim_doc_gia(u);
    hien_thi_doc_gia(u);
}

void admin::cau_hinh_doc_gia(){
    ui->doc_gia_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->doc_gia_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->doc_gia_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->doc_gia_table->setContextMenuPolicy(Qt::CustomContextMenu);
    QHeaderView *header = ui->doc_gia_table->horizontalHeader();
    header->setStretchLastSection(false);
    header->setSectionResizeMode(3, QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(6, QHeaderView::ResizeToContents);

}

void admin::hien_thi_doc_gia(BST_Account &u){
    remove_table(ui->doc_gia_table);
    u.traverse_ascending([this](Account &ac){
        int row = ui->doc_gia_table->rowCount();
        ui->doc_gia_table->insertRow(row);

        auto setText = [&](int col, const QString &text, bool center = false) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            QFont font = item->font();
            font.setPointSize(10);
            font.setBold(true);
            item->setFont(font);
            if (center)
            item->setTextAlignment(Qt::AlignCenter);
            ui->doc_gia_table->setItem(row, col, item);
        };
        setText(0, QString::fromStdString(ac.get_ten_dang_nhap()));
        setText(1, QString::fromStdString((ac.get_ten_tai_khoan())));
        setText(2, QString::fromStdString(ac.get_phone_number()), true);
        setText(3, QString::fromStdString((ac.get_email())));
        setText(4, QString::fromStdString("Trực tuyến"),true);
        setText(5, QString::fromStdString(ac.get_level()), true);
        ui->doc_gia_table->setCellWidget(row, 6, createNutThongTinUserWidget(ac.get_ID()));
    });
}
void admin::on_nhap_tu_file_clicked()
{
    add_book *win = new add_book(this);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
    win->set_up_file_mode();
    connect(win, &add_book::destroyed, this, [this]() {
        remove_table(ui->sach_table);
        add_book_(lib.get_book_data());
    });
}


void admin::on_tao_phieu_muon_sach_clicked()
{
    borrow br;
    auto win = new muon_sach(br, this);
    win->setWindowModality(Qt::ApplicationModal);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
    connect(win, &muon_sach::muon_sach_thanh_cong, this, [this]() {
        cau_hinh_muon_sach();
        });
}


void admin::on_the_loai_combo_activated(int index)
{
    const QString selected = ui->the_loai_combo->itemText(index).trimmed();
    const bool showAll = (index == 0);

    int rowCount = ui->sach_table->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        if (showAll) {
            ui->sach_table->setRowHidden(i, false);
            continue;
        }
        QTableWidgetItem *item = ui->sach_table->item(i, 3); // cột thể loại
        if (item) {
            bool match = (item->text().trimmed() == selected);
            ui->sach_table->setRowHidden(i, !match);
        }
    }
}


void admin::on_chuyen_nganh_combo_activated(int index)
{
    const QString selected = ui->chuyen_nganh_combo->itemText(index).trimmed();
    const bool showAll = (index == 0);

    int rowCount = ui->sach_table->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        if (showAll) {
            ui->sach_table->setRowHidden(i, false);
            continue;
        }
        QTableWidgetItem *item = ui->sach_table->item(i, 4); // cột chuyên ngành
        if (item) {
            bool match = (item->text().trimmed() == selected);
            ui->sach_table->setRowHidden(i, !match);
        }
    }
}


void admin::on_tao_ban_sao_button_clicked()
{
    add_book_copy *win = new add_book_copy(this);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
    connect(win, &add_book_copy::destroyed, this, [this]() {
        this->on_ban_sao_button_clicked();
    });
}

void admin::set_up_time_lich_su(QComboBox* ngay, QComboBox* thang, QComboBox* nam){
    ngay->clear();
    thang->clear();
    nam->clear();

    for (int i = 1; i <= 12; ++i) {
        thang->addItem(QString("Tháng %1").arg(i));
    }

    int currentYear = QDate::currentDate().year();
    for (int i = currentYear; i >= 2020; --i) {
        nam->addItem(QString("Năm %1").arg(i));
    }

    const QDate today = QDate::currentDate();
    int currentMonth = today.month();

    int yearIndex = nam->findText(QString("Năm %1").arg(today.year()));
    if (yearIndex >= 0) {
        nam->setCurrentIndex(yearIndex);
    }
    thang->setCurrentIndex(currentMonth - 1);

    refresh_ngay_lich_su(currentMonth - 1, today.year());
    int dayIndex = ngay->findText(QString("Ngày %1").arg(today.day()));
    if (dayIndex >= 0) {
        ngay->setCurrentIndex(dayIndex);
    }
}

void admin::refresh_ngay_lich_su(int thang, int nam){
    ui->ngay_lich_su->clear();
    int so_ngay = get_days_in_month(nam, thang + 1);
    for (int i = 1; i <= so_ngay; ++i) {
        ui->ngay_lich_su->addItem(QString("Ngày %1").arg(i));
    }
}

void admin::on_ngay_lich_su_activated(int index)
{
    Q_UNUSED(index);
    on_user_lich_su_activated(ui->user_lich_su->currentIndex());
}

void admin::on_thang_lich_su_activated(int index)
{
    QStringList parts = ui->nam_lich_su->currentText().split(' ');
    int year = parts.isEmpty() ? QDate::currentDate().year() : parts.last().toInt();
    refresh_ngay_lich_su(index, year);
    on_user_lich_su_activated(ui->user_lich_su->currentIndex());
}

void admin::on_nam_lich_su_activated(int index)
{
    Q_UNUSED(index);
    int monthIndex = ui->thang_lich_su->currentIndex();
    QStringList parts = ui->nam_lich_su->currentText().split(' ');
    int year = parts.isEmpty() ? QDate::currentDate().year() : parts.last().toInt();
    refresh_ngay_lich_su(monthIndex, year);
    on_user_lich_su_activated(ui->user_lich_su->currentIndex());
}



void admin::on_lich_su_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(6);
    QHeaderView *historyHeader = ui->lich_su_table->horizontalHeader();
    historyHeader->setStretchLastSection(false);
    historyHeader->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    historyHeader->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    historyHeader->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->lich_su_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");

    ui->thong_ke_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");

    ui->dau_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");

    ui->ban_sao_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->muon_tra_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->doc_gia_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    set_up_time_lich_su(ui->ngay_lich_su, ui->thang_lich_su, ui->nam_lich_su);
    set_up_user_lich_su();
    on_user_lich_su_activated(ui->user_lich_su->currentIndex());
}

void admin::set_up_user_lich_su(){
    ui->user_lich_su->clear();
    BST_Account u;
    lib.get_account_data().traverse_ascending([this,&u](Account &ac){
        ui->user_lich_su->addItem(QString::fromStdString(ac.get_ten_tai_khoan()), QVariant::fromValue(ac.get_ID()));
    });
}

void admin::on_user_lich_su_activated(int index)
{
    int ngay = ui->ngay_lich_su->currentIndex() + 1;
    int thang = ui->thang_lich_su->currentIndex() + 1;
    QStringList parts = ui->nam_lich_su->currentText().split(' ');
    int nam = parts.isEmpty() ? QDate::currentDate().year() : parts.last().toInt();
    long long user_id = ui->user_lich_su->itemData(index).toLongLong();
    BST_History h;
    Account a;
    lib.get_account_data().find(user_id, a);
    h.tim_lich_su_user_ngay(a.get_ten_tai_khoan(), ngay, thang, nam, h);
    hien_thi_lich_su(h);
}

void admin::hien_thi_lich_su(BST_History &h){
    remove_table(ui->lich_su_table);
    h.traverse_ascending([this](history_record &his){
        book b;
        int row = ui->lich_su_table->rowCount();
        ui->lich_su_table->insertRow(row);

        auto setText = [&](int col, const QString &text, bool center = false) {
            QTableWidgetItem *item = new QTableWidgetItem(text);
            QFont font = item->font();
            font.setPointSize(10);
            font.setBold(true);
            item->setFont(font);
            if (center)
            item->setTextAlignment(Qt::AlignCenter);
            ui->lich_su_table->setItem(row, col, item);
        };
        setText(0, QString::fromStdString(his.get_date_action().get_datetime()), true);
        QWidget* actionWidget = createActionLichSuWidget(his.get_action_type());
        ui->lich_su_table->setCellWidget(row, 1, actionWidget);
        string ghi_chu;
        switch (his.get_action_type())
        {
        case LOGIN:
            ghi_chu = his.get_ghi_chu();
            break;
        case REGISTER:
            ghi_chu = his.get_ghi_chu();
            break;
        case RESET_PASSWORD:
            ghi_chu = his.get_ghi_chu();
            break;
        case ADD_BOOK_COPY:
            ghi_chu = his.get_ghi_chu();
            break;
        case REMOVE_BOOK_COPY:
            ghi_chu = his.get_ghi_chu();
            break;
        default:
        {
            ghi_chu = his.get_ghi_chu();
            // if (lib.get_book_data().find(his.get_book_id(), b)) {
            //     ghi_chu = to_stringll_(b.get_ID()) + " - " + b.get_Name();
            // } else {
            //     ghi_chu = "Sách đã bị xóa hoặc không tồn tại";
            // }
            break;
        }
        }
        setText(2, QString::fromStdString(ghi_chu));
    });
}

QWidget* admin::createActionLichSuWidget(ActionType action_type){
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

void admin::on_cai_dat_button_clicked()
{
    // Dùng hàm reset chung
    reset_side_buttons_style();

    ui->cai_dat_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");
    if (lib.get_acc_sign_in().get_level() != "Admin"){
        ui->noi_dung_layout->setCurrentIndex(8);
        return;
    }
    ui->noi_dung_layout->setCurrentIndex(7);
    cau_hinh_cai_dat();
}

void admin::cau_hinh_cai_dat(){
    ui->so_luong_sach_moi->setValue(settings_file::getInstance()->get_so_sach_moi());
    ui->so_luong_sach_goi_y->setValue(settings_file::getInstance()->get_so_sach_goi_y());
    ui->so_lan_gia_han->setValue(settings_file::getInstance()->get_so_lan_gia_han());
    ui->so_ngay_gia_han->setValue(settings_file::getInstance()->get_so_ngay_gia_han());
    ui->so_ngay_dat_sach->setValue(settings_file::getInstance()->get_so_ngay_dat_sach());
    ui->tien_phat_khi_hong_sach->setValue(settings_file::getInstance()->get_tien_phat_hu_hong());
    ui->tien_phat_khi_mat_sach->setValue(settings_file::getInstance()->get_tien_phat_mat());
    ui->phi_phat_moi_ngay->setValue(settings_file::getInstance()->get_phi_phat_moi_ngay());
    ui->pass_quen->setText(QString::fromStdString(settings_file::getInstance()->get_mat_khau_quen()));
    ui->so_sach_muon_toi_da->setValue(settings_file::getInstance()->get_so_quyen_muon_toi_da());
}

void admin::on_cap_nhat_cai_dat_clicked()
{
    settings_file::getInstance()->set_so_sach_moi(ui->so_luong_sach_moi->value());
    settings_file::getInstance()->set_so_sach_goi_y(ui->so_luong_sach_goi_y->value());
    settings_file::getInstance()->set_so_lan_gia_han(ui->so_lan_gia_han->value());
    settings_file::getInstance()->set_so_ngay_gia_han(ui->so_ngay_gia_han->value());
    settings_file::getInstance()->set_so_ngay_dat_sach(ui->so_ngay_dat_sach->value());
    settings_file::getInstance()->set_tien_phat_hu_hong(ui->tien_phat_khi_hong_sach->value());
    settings_file::getInstance()->set_tien_phat_mat(ui->tien_phat_khi_mat_sach->value());
    settings_file::getInstance()->set_phi_phat_moi_ngay(ui->phi_phat_moi_ngay->value());
    settings_file::getInstance()->set_mat_khau_quen(ui->pass_quen->text().toStdString());
    settings_file::getInstance()->set_so_quyen_muon_toi_da(ui->so_sach_muon_toi_da->value());
    settings_file::getInstance()->ghi_file_settings();
    QMessageBox::information(this, "Cập nhật thành công", "Cài đặt đã được cập nhật thành công.\nVui lòng khởi động lại ứng dụng để áp dụng các thay đổi.");
}

void admin::xuat_csv_dau_sach(){

}

void admin::set_up_top_muon_nhieu_nhat()
{
    BST_Book_by_luot_muon luot_muon_book_data;
    luot_muon_book_data.find_5_most_borrowed(luot_muon_book_data);
    // Thiết lập giao diện cho 5 cuốn sách này
    ui->muon_nhieu->setVisible(true);
    ui->muon_nhieu_2->setVisible(true);
    ui->muon_nhieu_3->setVisible(true);
    ui->muon_nhieu_4->setVisible(true);
    ui->muon_nhieu_5->setVisible(true);

    ui->muon_nhieu->installEventFilter(this);
    ui->muon_nhieu_2->installEventFilter(this);
    ui->muon_nhieu_3->installEventFilter(this);
    ui->muon_nhieu_4->installEventFilter(this);
    ui->muon_nhieu_5->installEventFilter(this);

    ui->muon_nhieu->setProperty("book_id", luot_muon_book_data[4].get_ID());
    ui->muon_nhieu_2->setProperty("book_id", luot_muon_book_data[3].get_ID());
    ui->muon_nhieu_3->setProperty("book_id", luot_muon_book_data[2].get_ID());
    ui->muon_nhieu_4->setProperty("book_id", luot_muon_book_data[1].get_ID());
    ui->muon_nhieu_5->setProperty("book_id", luot_muon_book_data[0].get_ID());

    QString bookName = QString::fromStdString(luot_muon_book_data[4].get_Name());
    QString authorName = QString::fromStdString(luot_muon_book_data[4].get_Author());

    QFontMetrics fmBook(ui->sach_muon_nhieu->font());
    QString elidedBookName = fmBook.elidedText(bookName, Qt::ElideRight, ui->sach_muon_nhieu->width());
    ui->sach_muon_nhieu->setText(elidedBookName);

    QFontMetrics fmAuthor(ui->tac_gia_muon_nhieu->font());
    QString elidedAuthorName = fmAuthor.elidedText(authorName, Qt::ElideRight, ui->tac_gia_muon_nhieu->width());
    ui->tac_gia_muon_nhieu->setText(elidedAuthorName);

    ui->muon_nhieu_info->setText(QString::number(luot_muon_book_data[4].get_luot_muon()));

    bookName = QString::fromStdString(luot_muon_book_data[3].get_Name());
    authorName = QString::fromStdString(luot_muon_book_data[3].get_Author());
    elidedBookName = fmBook.elidedText(bookName, Qt::ElideRight, ui->sach_muon_nhieu_2->width());
    ui->sach_muon_nhieu_2->setText(elidedBookName);
    elidedAuthorName = fmAuthor.elidedText(authorName, Qt::ElideRight, ui->tac_gia_muon_nhieu_2->width());
    ui->tac_gia_muon_nhieu_2->setText(elidedAuthorName);
    ui->muon_nhieu_info_2->setText(QString::number(luot_muon_book_data[3].get_luot_muon()));

    bookName = QString::fromStdString(luot_muon_book_data[2].get_Name());
    authorName = QString::fromStdString(luot_muon_book_data[2].get_Author());
    elidedBookName = fmBook.elidedText(bookName, Qt::ElideRight, ui->sach_muon_nhieu_3->width());
    ui->sach_muon_nhieu_3->setText(elidedBookName);
    elidedAuthorName = fmAuthor.elidedText(authorName, Qt::ElideRight, ui->tac_gia_muon_nhieu_3->width());
    ui->tac_gia_muon_nhieu_3->setText(elidedAuthorName);
    ui->muon_nhieu_info_3->setText(QString::number(luot_muon_book_data[2].get_luot_muon()));

    bookName = QString::fromStdString(luot_muon_book_data[1].get_Name());
    authorName = QString::fromStdString(luot_muon_book_data[1].get_Author());
    elidedBookName = fmBook.elidedText(bookName, Qt::ElideRight, ui->sach_muon_nhieu_4->width());
    ui->sach_muon_nhieu_4->setText(elidedBookName);
    elidedAuthorName = fmAuthor.elidedText(authorName, Qt::ElideRight, ui->tac_gia_muon_nhieu_4->width());
    ui->tac_gia_muon_nhieu_4->setText(elidedAuthorName);
    ui->muon_nhieu_info_4->setText(QString::number(luot_muon_book_data[1].get_luot_muon()));

    bookName = QString::fromStdString(luot_muon_book_data[0].get_Name());
    authorName = QString::fromStdString(luot_muon_book_data[0].get_Author());
    elidedBookName = fmBook.elidedText(bookName, Qt::ElideRight, ui->sach_muon_nhieu_5->width());
    ui->sach_muon_nhieu_5->setText(elidedBookName);
    elidedAuthorName = fmAuthor.elidedText(authorName, Qt::ElideRight, ui->tac_gia_muon_nhieu_5->width());
    ui->tac_gia_muon_nhieu_5->setText(elidedAuthorName);
    ui->muon_nhieu_info_5->setText(QString::number(luot_muon_book_data[0].get_luot_muon()));
}

void admin::set_up_top_doc_nhieu_nhat()
{
    // Tìm 5 cuốn sách đọc nhiều nhất
    BST_Book_by_luot_xem luot_xem_book_data;
    luot_xem_book_data.find_5_most_viewed(luot_xem_book_data);
    // Thiết lập giao diện cho 5 cuốn sách này
    ui->doc_nhieu_1->setVisible(true);
    ui->doc_nhieu_2->setVisible(true);
    ui->doc_nhieu_3->setVisible(true);
    ui->doc_nhieu_4->setVisible(true);
    ui->doc_nhieu_5->setVisible(true);

    ui->doc_nhieu_1->installEventFilter(this);
    ui->doc_nhieu_2->installEventFilter(this);
    ui->doc_nhieu_3->installEventFilter(this);
    ui->doc_nhieu_4->installEventFilter(this);
    ui->doc_nhieu_5->installEventFilter(this);

    ui->doc_nhieu_1->setProperty("book_id", luot_xem_book_data[4].get_ID());
    ui->doc_nhieu_2->setProperty("book_id", luot_xem_book_data[3].get_ID());
    ui->doc_nhieu_3->setProperty("book_id", luot_xem_book_data[2].get_ID());
    ui->doc_nhieu_4->setProperty("book_id", luot_xem_book_data[1].get_ID());
    ui->doc_nhieu_5->setProperty("book_id", luot_xem_book_data[0].get_ID());

    QString bookName = QString::fromStdString(luot_xem_book_data[4].get_Name());
    QString authorName = QString::fromStdString(luot_xem_book_data[4].get_Author());

    QFontMetrics fmBook(ui->sach_doc_nhieu->font());
    QString elidedBookName = fmBook.elidedText(bookName, Qt::ElideRight, ui->sach_doc_nhieu->width());
    ui->sach_doc_nhieu->setText(elidedBookName);

    QFontMetrics fmAuthor(ui->tac_gia_doc_nhieu->font());
    QString elidedAuthorName = fmAuthor.elidedText(authorName, Qt::ElideRight, ui->tac_gia_doc_nhieu->width());
    ui->tac_gia_doc_nhieu->setText(elidedAuthorName);

    ui->doc_nhieu_info->setText(QString::number(luot_xem_book_data[4].get_luot_xem()));

    bookName = QString::fromStdString(luot_xem_book_data[3].get_Name());
    authorName = QString::fromStdString(luot_xem_book_data[3].get_Author());
    elidedBookName = fmBook.elidedText(bookName, Qt::ElideRight, ui->sach_doc_nhieu_1->width());
    ui->sach_doc_nhieu_1->setText(elidedBookName);
    elidedAuthorName = fmAuthor.elidedText(authorName, Qt::ElideRight, ui->tac_gia_doc_nhieu_1->width());
    ui->tac_gia_doc_nhieu_1->setText(elidedAuthorName);
    ui->doc_nhieu_info_1->setText(QString::number(luot_xem_book_data[3].get_luot_xem()));

    bookName = QString::fromStdString(luot_xem_book_data[2].get_Name());
    authorName = QString::fromStdString(luot_xem_book_data[2].get_Author());
    elidedBookName = fmBook.elidedText(bookName, Qt::ElideRight, ui->sach_doc_nhieu_2->width());
    ui->sach_doc_nhieu_2->setText(elidedBookName);
    elidedAuthorName = fmAuthor.elidedText(authorName, Qt::ElideRight, ui->tac_gia_doc_nhieu_2->width());
    ui->tac_gia_doc_nhieu_2->setText(elidedAuthorName);
    ui->doc_nhieu_info_2->setText(QString::number(luot_xem_book_data[2].get_luot_xem()));

    bookName = QString::fromStdString(luot_xem_book_data[1].get_Name());
    authorName = QString::fromStdString(luot_xem_book_data[1].get_Author());
    elidedBookName = fmBook.elidedText(bookName, Qt::ElideRight, ui->sach_doc_nhieu_3->width());
    ui->sach_doc_nhieu_3->setText(elidedBookName);
    elidedAuthorName = fmAuthor.elidedText(authorName, Qt::ElideRight, ui->tac_gia_doc_nhieu_3->width());
    ui->tac_gia_doc_nhieu_3->setText(elidedAuthorName);
    ui->doc_nhieu_info_3->setText(QString::number(luot_xem_book_data[1].get_luot_xem()));

    bookName = QString::fromStdString(luot_xem_book_data[0].get_Name());
    authorName = QString::fromStdString(luot_xem_book_data[0].get_Author());
    elidedBookName = fmBook.elidedText(bookName, Qt::ElideRight, ui->sach_doc_nhieu_4->width());
    ui->sach_doc_nhieu_4->setText(elidedBookName);
    elidedAuthorName = fmAuthor.elidedText(authorName, Qt::ElideRight, ui->tac_gia_doc_nhieu_4->width());
    ui->tac_gia_doc_nhieu_4->setText(elidedAuthorName);
    ui->doc_nhieu_info_4->setText(QString::number(luot_xem_book_data[0].get_luot_xem()));
}

void admin::on_xuat_csv_sach_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        "Xuất danh sách đầu sách",
        QDir::homePath() + "/dau_sach.csv",
        "CSV Files (*.csv)");

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Lỗi", "Không thể tạo file CSV!");
        return;
    }

    QTextStream out(&file);

    // UTF-8 with BOM
    out << QChar(0xFEFF);

    // Header
    out << "ID,Tên sách,Tác giả,Nhà xuất bản,Năm xuất bản,Mã ISBN,Ngôn ngữ,Tóm tắt,Thể loại,Chuyên ngành,Số bản sao,Sách đang mượn,Sách đang đặt,Ngày tạo,Tạo bởi\n";

    // Data
    lib.get_book_data().traverse_ascending([&out](book &b) {
        out << b.get_ID() << ","
            << "\"" << QString::fromStdString(b.get_Name()) << "\","
            << "\"" << QString::fromStdString(b.get_Author()) << "\","
            << "\"" << QString::fromStdString(b.get_NXB()) << "\","
            << b.get_NamXB() << ","
            << "\"" << QString::fromStdString(b.get_ISBN()) << "\","
            << "\"" << QString::fromStdString(b.get_Language()) << "\","
            << "\"" << QString::fromStdString(b.get_Tom_tat()) << "\","
            << "\"" << QString::fromStdString(b.get_The_loai_name()) << "\","
            << "\"" << QString::fromStdString(b.get_Chuyen_nganh_name()) << "\","
            << b.get_tong_sach() << ","
            << (b.get_tong_sach() - b.get_tong_sach_ranh()) << ","
            << b.get_tong_sach_dang_dat() << ","
            << "\"" << QString::fromStdString(b.get_Date_created().get_date()) << "\","
            << "\"" << QString::fromStdString(b.get_Created_by()) << "\"\n";
    });

    file.close();
    QMessageBox::information(this, "Thành công", "Đã xuất file CSV thành công!");
}


void admin::on_xuat_csv_ban_sao_clicked()
{
    // Chọn vị trí lưu file
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Xuất danh sách bản sao",
        QDir::homePath() + "/ban_sao.csv",
        "CSV Files (*.csv)");

    if (fileName.isEmpty()) {
        return; // Người dùng hủy
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Lỗi", "Không thể tạo file CSV!");
        return;
    }

    QTextStream out(&file);
    out << QChar(0xFEFF);

    // Header
    out << "ID bản sao,ID đầu sách,Tên sách,Trạng thái\n";

    // Ghi dữ liệu
    lib.get_book_copy_data().traverse_ascending([&out](Book_copies &bc) {
        book b;
        QString tenSach = "Không tìm thấy";
        if (lib.get_book_data().find(bc.get_id_book(), b)) {
            tenSach = QString::fromStdString(b.get_Name());
        }

        out << bc.get_id() << ","
            << bc.get_id_book() << ","
            << "\"" << tenSach << "\","
            << "\"" << QString::fromStdString(bc.get_status()) << "\"\n";
    });

    file.close();
    QMessageBox::information(this, "Thành công", "Đã xuất file CSV bản sao thành công!");
}

void admin::on_xuat_csv_muon_tra_clicked()
{
    // Chọn vị trí lưu file
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Xuất danh sách mượn/trả",
        QDir::homePath() + "/muon_tra.csv",
        "CSV Files (*.csv)");

    if (fileName.isEmpty()) {
        return; // Người dùng hủy
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Lỗi", "Không thể tạo file CSV!");
        return;
    }

    QTextStream out(&file);
    out << QChar(0xFEFF);

    // Header
    out << "ID giao dịch,Người dùng,Tên sách,ID bản sao,Ngày mượn,"
           "Ngày phải trả,Ngày trả,Trạng thái,Tình trạng sách,Tiền phạt\n";

    // Ghi dữ liệu từ toàn bộ cây borrow_data
    lib.get_borrow_data().traverse_ascending([&out](borrow &br) {
        QString userName   = QString::fromStdString((br.get_user_name()));
        QString bookName   = QString::fromStdString(br.get_book_name());
        QString ngayMuon   = QString::fromStdString(br.get_ngay_muon().get_date());
        QString ngayPhaiTra= QString::fromStdString(br.get_ngay_phai_tra().get_date());
        QString ngayTra    = QString::fromStdString(br.get_ngay_tra().get_date());

        QString trangThai;
        switch (br.get_status()) {
        case StatusType::XU_LY:         trangThai = "Chờ xử lý";    break;
        case StatusType::SAN_SANG:      trangThai = "Sẵn sàng";     break;
        case StatusType::QUA_HAN_DAT:   trangThai = "Quá hạn đặt";  break;
        case StatusType::DANG_MUON:     trangThai = "Đang mượn";    break;
        case StatusType::QUA_HAN_MUON:  trangThai = "Quá hạn mượn"; break;
        case StatusType::TRA_DUNG_HAN:  trangThai = "Trả đúng hạn"; break;
        case StatusType::TRA_QUA_HAN:   trangThai = "Trả quá hạn";  break;
        default:                        trangThai = "Khác";         break;
        }

        QString tinhTrang;
        switch (br.get_tinh_trang_sach()) {
        case TinhTrangsach::TOT:          tinhTrang = "Tốt";          break;
        case TinhTrangsach::BINH_THUONG:  tinhTrang = "Bình thường";  break;
        case TinhTrangsach::HONG:         tinhTrang = "Hư hỏng";      break;
        case TinhTrangsach::MAT:          tinhTrang = "Mất";          break;
        default:                          tinhTrang = "N/A";          break;
        }

        out << br.get_id() << ","
            << "\"" << userName << "\","
            << "\"" << bookName << "\","
            << br.get_book_copy_id() << ","
            << "\"" << ngayMuon << "\","
            << "\"" << ngayPhaiTra << "\","
            << "\"" << ngayTra << "\","
            << "\"" << trangThai << "\","
            << "\"" << tinhTrang << "\","
            << br.get_tien_phat()
            << "\n";
    });

    file.close();
    QMessageBox::information(this, "Thành công", "Đã xuất file CSV mượn/trả thành công!");
}


void admin::on_xuat_csv_lich_su_clicked()
{
    // Chọn vị trí lưu file
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Xuất lịch sử hoạt động",
        QDir::homePath() + "/lich_su.csv",
        "CSV Files (*.csv)");

    if (fileName.isEmpty()) {
        return; // Người dùng hủy
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Lỗi", "Không thể tạo file CSV!");
        return;
    }

    QTextStream out(&file);
    out << QChar(0xFEFF); // UTF‑8 BOM

    // Header
    out << "Thời gian,Người dùng,Hành động,Ghi chú\n";

    // Ghi toàn bộ cây lịch sử
    record.traverse_ascending([&out](history_record &his) {
        QString time = QString::fromStdString(his.get_date_action().get_datetime());
        QString user = QString::fromStdString(his.get_user_name());
        QString note;

        // Chuyển ActionType sang chuỗi
        QString actionStr;
        switch (his.get_action_type()) {
        case LOGIN:             actionStr = "Đăng nhập"; break;
        case REGISTER:          actionStr = "Đăng ký"; break;
        case RESET_PASSWORD:    actionStr = "Đặt lại mật khẩu"; break;
        case VIEW_BOOK:         actionStr = "Xem thông tin sách"; break;
        case DOWNLOAD_BOOK:     actionStr = "Tải sách"; break;
        case READ_ONLINE:       actionStr = "Đọc online"; break;
        case RESERVE_BOOK:      actionStr = "Đặt sách"; break;
        case BORROW_BOOK:       actionStr = "Mượn sách"; break;
        case LIKE_BOOK:         actionStr = "Yêu thích sách"; break;
        case DISLIKE_BOOK:      actionStr = "Bỏ yêu thích"; break;
        case CONFIRM_BOOK:      actionStr = "Xác nhận mượn"; break;
        case RETURN_BOOK:       actionStr = "Trả sách"; break;
        case RETURN_OVERDUE:    actionStr = "Trả quá hạn"; break;
        case REMOVE_BOOK:       actionStr = "Xóa sách"; break;
        case ADD_BOOK:          actionStr = "Thêm sách"; break;
        case UPDATE_BOOK:       actionStr = "Cập nhật sách"; break;
        case ADD_BOOK_COPY:     actionStr = "Thêm bản sao"; break;
        case REMOVE_BOOK_COPY:  actionStr = "Xóa bản sao"; break;
        case ADJ_BOOK:          actionStr = "Điều chỉnh sách"; break;
        case ADJ_USER:          actionStr = "Điều chỉnh người dùng"; break;
        case UNKNOWN:
        default:                actionStr = "Khác"; break;
        }

        note = QString::fromStdString(his.get_ghi_chu());

        out << "\"" << time      << "\","
            << "\"" << user      << "\","
            << "\"" << actionStr << "\","
            << "\"" << note      << "\"\n";
    });

    file.close();
    QMessageBox::information(this, "Thành công", "Đã xuất file CSV lịch sử thành công!");
}

QPixmap admin::load_image_pro(const QString &path, const QSize &targetSize, int radius, bool cropToFill) {
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
