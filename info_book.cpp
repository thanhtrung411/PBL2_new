#include "info_book.h"
#include "global.h"
#include "ui_info_book.h"
#include "book.h"
#include <QPainter>
#include <QPainterPath>

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

info_book::info_book(const book &book_inf, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::info_book)
    , book_info(book_inf)
{
    ui->setupUi(this);
    displayBookInfo();
}

info_book::~info_book()
{
    delete ui;
}
void info_book::displayBookInfo()
{
    QString png_path = QString::fromUtf8(book_info.get_Link_png());
    ui->book_png->setFixedSize(175,220);
    QSize targetSize = ui->book_png->size();
    targetSize = targetSize * ui->book_png->devicePixelRatio(); 
    ui->book_png->setPixmap(loadScaled(png_path, targetSize, 15));
    QPixmap finalPix = loadScaled(png_path, targetSize, 15);
    finalPix.setDevicePixelRatio(ui->book_png->devicePixelRatio());
    ui->book_png->setPixmap(finalPix);

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
