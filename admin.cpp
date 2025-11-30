#include "admin.h"
#include "ui_admin.h"
#include "book.h"
#include "tree.h"
#include "global.h"
#include "history.h"
#include "add_book.h"
#include "info_book.h"
#include "muon_sach.h"
#include "my_string.h"
#include "phieu_tra_sach.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>
#include <QMenu>
#include <QToolTip>
#include <QCursor>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

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

    // Cấu hình bảng sách
    ui->sach_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->sach_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->sach_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    history h;
    h.load_from_file();
    connect(ui->sach_table, &QTableWidget::cellClicked,
            this, &admin::on_sach_table_cellClicked);

    can_chinh_table(ui->sach_table);
    ui->sach_table->setContextMenuPolicy(Qt::CustomContextMenu);

    // Trang mặc định + hiển thị thống kê
    ui->noi_dung_layout->setCurrentIndex(0);
    hien_thi_thong_ke();
    set_thong_ke();

    // Load dữ liệu sách ban đầu
    add_book_(book_data);
}

admin::~admin()
{
    delete ui;
}

void admin::set_thong_ke(){
    int tong_sach = book_data.count_data();
    int tong_ban_sao = book_copy_data.count_data();
    int tong_doc_gia = accout_data.count_doc_gia();
    int tong_thu_thu = accout_data.count_thu_thu();
    int tong_chuyen_nganh = chuyen_nganh_data.count_data();
    int tong_sach_ranh;
    int tong_sach_dat;
    int tong_sach_dang_muon;
    int tong_sach_qua_han;
    borrow_data.tong_sach_dat_muon_qua_han(tong_sach_dat, tong_sach_dang_muon, tong_sach_qua_han);
    tong_sach_ranh = tong_ban_sao - tong_sach_dang_muon;
    int luot_xem_thang;
    int luot_muon_thang;
    int luot_tai_thang;
    my_time current_date = my_time::now();
    history h;
    h.luot_xem_muon_tai_thang(current_date.get_month(), current_date.get_year(),
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

    QChartView *pieChartTheLoai = createPhanboTheLoaiChart();
    ui->thong_ke_theo_nam_the_loai->addWidget(pieChartTheLoai);
}

QChartView* admin::createLuotMuonChart()
{
    // Tạo dữ liệu
    QBarSet *set0 = new QBarSet("Lượt mượn");
    *set0 << 44 << 55 << 66 << 34 << 45 << 13 << 78 << 43 << 65 << 45 << 23 << 11;
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
    axisY->setRange(0, 100);
    axisY->setTickCount(5);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("border: 1px solid #e0e0e0; "
                             "border-radius: 10px; "
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
    // Tạo pie
    QPieSeries *series = new QPieSeries();
    // Dữ liệu mẫu
    series->append("Công nghệ", 35);
    series->append("Kinh tế", 20);
    series->append("Lịch sử", 15);
    series->append("Văn học", 12);
    series->append("Khoa học", 10);
    series->append("Khác", 8);

    for (QPieSlice *slice : series->slices()) {
        const QString label = QString("%1: %2%")
                                  .arg(slice->label())
                                  .arg(slice->value());
        slice->setLabel(label);

        if (slice->label().contains("Công nghệ")) {
            slice->setExploded();
            slice->setLabelVisible(true);
            slice->setPen(QPen(Qt::white, 2));
        } else {
            slice->setLabelVisible(true);
        }
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
    chartView->setStyleSheet("border: 1px solid #e0e0e0; "
                             "border-radius: 10px; "
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
        add_book_(book_data);
        return;
    }

    BST_Book kq_search;
    int type_the_loai = 0;   // 0: tất cả thể loại
    int type_tuy_chon = 0;   // 0: có chứa
    int type_bieu_ghi = 1;   // 1: tên sách
    std::string key_word = arg1.toStdString();

    book_data.search(type_the_loai, type_tuy_chon, type_bieu_ghi,
                     key_word, book_data, kq_search);
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
    QAction *actSua  = menu.addAction("Xem bản sao");
    QAction *actXoa  = menu.addAction("Xóa sách");

    QAction *chosen = menu.exec(ui->sach_table->viewport()->mapToGlobal(pos));
    if (!chosen)
        return;

    book selectedBook;
    if (!book_data.find(id, selectedBook)) {
        return;
    }

    if (chosen == actXem) {
        info_book *win = new info_book(selectedBook, this);
        win->setAttribute(Qt::WA_DeleteOnClose, true);
        win->show();
    } else if (chosen == actSua) {
        // TODO: xử lý xem / sửa bản sao
    } else if (chosen == actXoa) {
        // TODO: xử lý xóa sách
    }
}

void admin::on_thong_ke_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(0);
    ui->thong_ke_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");

    ui->dau_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");

    ui->ban_sao_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");

    ui->doc_gia_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->muon_tra_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->thu_thu_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
}

void admin::on_dau_sach_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(1);
    ui->dau_sach_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");

    ui->thong_ke_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");

    ui->ban_sao_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");

    ui->doc_gia_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->muon_tra_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->thu_thu_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
}

void admin::on_ban_sao_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(2);
    ui->ban_sao_button->setStyleSheet(
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

    ui->doc_gia_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->muon_tra_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
    ui->thu_thu_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
}

void admin::on_doc_gia_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(3);
    ui->doc_gia_button->setStyleSheet(
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
    ui->thu_thu_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
        "border-radius: 10px;");
}

void admin::on_thu_thu_button_clicked()
{
    ui->noi_dung_layout->setCurrentIndex(4);
    ui->thu_thu_button->setStyleSheet(
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
    ui->muon_tra_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(255, 255, 255);"
        "border-radius: 10px;");
    ui->thu_thu_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
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

    ui->doc_gia_button->setStyleSheet(
        "color: rgb(0, 0, 0);"
        "background-color: rgb(236, 235, 240);"
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
        setText(0, QString::fromStdString(giai_ma_str_(br.get_user_name())));
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

    borrow br;
    if (!borrow_data.find(id, br)) {
        return;
    }
    br.set_status(StatusType::SAN_SANG);
    book bk;
    book_data.find(id, bk);
    bk.set_luot_muon(bk.get_luot_muon() + 1);
    bk.set_tong_sach_ranh(bk.get_tong_sach_ranh() - 1);
    book_data.update(bk, bk);
    borrow_data.update(br, br);
    cau_hinh_dat_sach();
}
void admin::onXacNhanClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    long long id = button->property("ID").toLongLong();

    borrow br;
    if (!borrow_data.find(id, br)) {
        return;
    }
    auto win = new muon_sach(br, this);
    win->setWindowModality(Qt::ApplicationModal);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
    connect(win, &muon_sach::muon_sach_thanh_cong, this, [this, win, button, id]() {
        QWidget *widgetContainer = button->parentWidget();
        if (!widgetContainer) return;
        QPoint pos = widgetContainer->pos();
        QModelIndex index = ui->dat_sach_table->indexAt(pos);
        int currentRow = index.row();
        if (currentRow >= 0) {
            ui->dat_sach_table->setCellWidget(currentRow, 4, createStatusDatWidget(StatusType::DANG_MUON,0));
            ui->dat_sach_table->setCellWidget(currentRow, 5, createNutDatWidget(StatusType::DANG_MUON, id));
        }
        });
    //cau_hinh_dat_sach();
}
void admin::onXoaDatSachClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    long long id = button->property("ID").toLongLong();
    borrow_data.remove_by_Key(id);
    cau_hinh_dat_sach();
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
        setText(0, QString::fromStdString(giai_ma_str_(br.get_user_name())));
        setText(1, QString::fromStdString(br.get_book_name()));
        setText(2, QString::number(br.get_book_copy_id()), true);
        setText(3, QString::fromStdString(br.get_ngay_muon().get_date()), true);
        setText(4, QString::fromStdString(br.get_ngay_phai_tra().get_date()), true);
        string trang_thai;
        if (br.get_status() == StatusType::DANG_MUON)
            trang_thai = "Đang mượn";
        else if (br.get_status() == StatusType::QUA_HAN_MUON)
            trang_thai = "Quá hạn mượn";
        string so_gia_han = to_string(br.get_lan_gia_han()) + "/2";
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
    book_data.find(id, bk);
    if (!borrow_data.find(id, br)) {
        return container;
    }
    if (br.get_lan_gia_han() < 2 && bk.get_tong_sach_ranh() > 0){
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
    if (!button)
        return;
    long long id = button->property("ID").toLongLong();

    borrow br;
    if (!borrow_data.find(id, br)) {
        return;
    }
    br.set_lan_gia_han(br.get_lan_gia_han() + 1);
    br.set_ngay_phai_tra(br.get_ngay_phai_tra() + 7);
    borrow_data.update(br, br);
    cau_hinh_muon_sach();
}

void admin::onXemChiTietMuonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;
    long long id = button->property("ID").toLongLong();

    borrow br;
    if (!borrow_data.find(id, br)) {
        return;
    }
    //info_borrow *win = new info_borrow(br, this);
    //win->setAttribute(Qt::WA_DeleteOnClose, true);
    //win->show();
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
        setText(0, QString::fromStdString((br.get_user_name())));
        setText(1, QString::fromStdString(br.get_book_name()));
        setText(2,"BS-" + QString::number(br.get_book_copy_id()), true);
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
    if (!borrow_data.find(id, br)) {
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

