#include "info_book.h"
#include "global.h"
#include "ui_info_book.h"
#include "book.h"
#include <QPainter>
#include <QPainterPath>
#include <QImageReader>
#include <QScreen>
#include <QGuiApplication>
#include <QFile>

info_book::info_book(const book &book_inf, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::info_book)
    , book_info(book_inf)
{
    ui->setupUi(this);
    displayBookInfo();
    this->setWindowTitle(QString::fromStdString(book_info.get_Name()));
    this->setMaximumHeight(0);
}

info_book::~info_book()
{
    delete ui;
}
void info_book::displayBookInfo()
{
    set_up_anh();
    ui->name_book->setText(QString::fromStdString(book_info.get_Name()));
    ui->nam_xuat_ban_label->setText(QString::number(book_info.get_NamXB()));
    ui->author_name->setText(QString::fromStdString(book_info.get_Author()));
    ui->nha_xuat_ban->setText(QString::fromStdString(book_info.get_NXB()));
    ui->so_trang->setText(QString::number(book_info.get_So_trang()));
    ui->isbn->setText(QString::fromStdString(book_info.get_ISBN()));
    ui->ngon_ngu->setText(QString::fromStdString(book_info.get_Language()));
    ui->tom_tat->setText(QString::fromStdString(book_info.get_Tom_tat()));
    ui->the_loai->setText(QString::fromStdString(book_info.get_The_loai_name()));
    ui->chuyen_nganh->setText(QString::fromStdString(book_info.get_Chuyen_nganh_name()));
    ui->luot_xem->setText(QString::number(book_info.get_luot_xem()));
    ui->luot_muon->setText(QString::number(book_info.get_luot_muon()));
    ui->luot_tai->setText(QString::number(book_info.get_luot_tai()));
    ui->tong_sach->setText(QString::number(book_info.get_tong_sach()));
    ui->sach_dang_muon->setText(QString::number(book_info.get_tong_sach_dang_muon()));
    ui->sach_dang_dat->setText(QString::number(book_info.get_tong_sach_dang_dat()));
    ui->sach_ranh->setText(QString::number(book_info.get_tong_sach_ranh()));
    string inf = "Được tạo vào ngày " + book_info.get_Date_created().get_date() + " bởi " + book_info.get_Created_by();
    ui->created_by->setText(QString::fromStdString(inf));
}

QPixmap info_book::loadScaled(const QString& path, const QSize& physicalSize, int radius)
{
    QPixmap src(path);
    if (src.isNull()) {
        // Thử load ảnh mặc định
        src = QPixmap("../../png_background/default_book.png");
        if (src.isNull()) {
            // Nếu ảnh mặc định cũng không có, dùng màu nền
            QPixmap ph(physicalSize);
            ph.fill(QColor("#f1f5f9"));
            return ph;
        }
    }
    QPixmap scaled = src.scaled(physicalSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    int x = (scaled.width() - physicalSize.width()) / 2;
    int y = (scaled.height() - physicalSize.height()) / 2;
    QPixmap cropped = scaled.copy(x, y, physicalSize.width(), physicalSize.height());

    QPixmap dest(physicalSize);
    dest.fill(Qt::transparent);

    QPainter painter(&dest);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QPainterPath pathObj;
    pathObj.addRoundedRect(0, 0, physicalSize.width(), physicalSize.height(), radius, radius);
    
    painter.setClipPath(pathObj);
    painter.drawPixmap(0, 0, cropped);

    // Viền mờ
    painter.setClipping(false);
    painter.setPen(QPen(QColor(0, 0, 0, 20), 1)); 
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(0, 0, physicalSize.width()-1, physicalSize.height()-1, radius, radius);

    return dest;
}

void info_book::set_up_anh(){
    QString png_path = QString::fromUtf8(book_info.get_Link_png().c_str());
    
    qreal dpr = QGuiApplication::primaryScreen()->devicePixelRatio();
    QSize logicalSize(200, 250);
    QSize physicalSize = logicalSize * dpr;
    int physicalRadius = 12 * dpr;
    
    ui->book_png->setFixedSize(logicalSize);
    ui->book_png->setAlignment(Qt::AlignCenter);
    
    QPixmap result = loadScaled(png_path, physicalSize, physicalRadius);
    result.setDevicePixelRatio(dpr);
    
    ui->book_png->setPixmap(result);
    ui->book_png->setStyleSheet("background-color: transparent; border: none;");
}