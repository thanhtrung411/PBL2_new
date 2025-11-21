#include "admin.h"
#include "ui_admin.h"
#include "book.h"
#include "tree.h"
#include "global.h"
#include "add_book.h"
#include "info_book.h"

#include <QTableWidget>
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

    connect(ui->sach_table, &QTableWidget::cellClicked,
            this, &admin::on_sach_table_cellClicked);

    can_chinh_table(ui->sach_table);
    ui->sach_table->setContextMenuPolicy(Qt::CustomContextMenu);

    // Trang mặc định + hiển thị thống kê
    ui->noi_dung_layout->setCurrentIndex(0);
    hien_thi_thong_ke();

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
