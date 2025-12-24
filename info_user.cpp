#include "info_user.h"
#include "ui_info_user.h"
#include "Account.h"
#include "global.h"
#include "exception.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include<QPixmap>
#include <QFile>
#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QPainterPath>

info_user::info_user(Account ac, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::info_user)
{
    acc_info = ac;
    ui->setupUi(this);
    set_info_user();
    set_locker();
}

info_user::~info_user()
{
    delete ui;
}

void info_user::set_info_user(){
    ui->ten_dang_nhap->setText(QString::fromStdString(acc_info.get_ten_dang_nhap()));
    ui->ho_va_ten->setText(QString::fromStdString(acc_info.get_ten_tai_khoan()));
    ui->email->setText(QString::fromStdString(acc_info.get_email()));
    ui->so_dien_thoai->setText(QString::fromStdString(acc_info.get_phone_number()));
    if (acc_info.get_level() == "Admin"){
        ui->chuc_vu->setText("Quản trị viên");
    }
    else if (acc_info.get_level() == "Librarian"){
        ui->chuc_vu->setText("Thủ thư");
    }
    else{
        ui->chuc_vu->setText("Người dùng");
    }
    ui->ngay_sinh->setDate(QDate::fromString(QString::fromStdString(acc_info.get_ngay_sinh().get_date()), "dd/MM/yyyy"));
    if (acc_info.get_gioi_tinh() == 0){
        ui->gioi_tinh->setCurrentIndex(0);
    }
    else if (acc_info.get_gioi_tinh() == 1){
        ui->gioi_tinh->setCurrentIndex(1);
    }
    else{
        ui->gioi_tinh->setCurrentIndex(2);
    }
    ui->so_diem->setText(QString::number(acc_info.get_score()));
    ui->so_sach_muon->setText(QString::number(lib.get_borrow_data().sach_dang_muon(acc_info.get_ID())));
    set_anh_dai_dien();
}

void info_user::on_luu_thong_tin_clicked()
{
    Account acc_old = acc_info;
    std::string pass_new = ui->mat_khau_moi->text().trimmed().toStdString();
    std::string pass_confirm = ui->mat_khau_moi_again->text().trimmed().toStdString();
    if (!pass_new.empty() || !pass_confirm.empty()) {
        if (pass_new != pass_confirm) {
            QMessageBox::warning(this, "Lỗi", "Mật khẩu mới và xác nhận mật khẩu không khớp!");
            return;
        }
        acc_info.set_pass(pass_new);
    }

    std::string email = ui->email->text().trimmed().toStdString();
    QRegularExpression emailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.\\w+$");
    if (!emailRegex.match(QString::fromStdString(email)).hasMatch()) {
        QMessageBox::warning(this, "Lỗi", "Email không đúng định dạng!");
        return;
    }

    std::string phone = ui->so_dien_thoai->text().trimmed().toStdString();
    QRegularExpression phoneRegex("^0\\d{9,10}$");
    if (!phoneRegex.match(QString::fromStdString(phone)).hasMatch()) {
        QMessageBox::warning(this, "Lỗi", "Số điện thoại không đúng định dạng (phải bắt đầu bằng 0 và có 10-11 chữ số)!");
        return;
    }

    std::string username = ui->ten_dang_nhap->text().trimmed().toStdString();
    if (lib.get_account_data().check_ten_dang_nhap(username) && username != acc_old.get_ten_dang_nhap()) {
        QMessageBox::warning(this, "Lỗi", "Tên đăng nhập đã tồn tại!");
        return;
    }

    acc_info.set_ten_dang_nhap(username);
    acc_info.set_ten_tai_khoan(ui->ho_va_ten->text().trimmed().toStdString());
    acc_info.set_email(email);
    acc_info.set_phone_number(phone);
    my_time ngay_sinh(ui->ngay_sinh->date().toString("dd/MM/yyyy").toStdString());
    acc_info.set_ngay_sinh(ngay_sinh);
    acc_info.set_gioi_tinh(ui->gioi_tinh->currentIndex());

    lib.get_account_data().update(acc_old, acc_info);
    ghi_Account(lib.get_account_data());
    QMessageBox::information(this, "Thành công", "Cập nhật thông tin cá nhân thành công!");
}


void info_user::on_pushButton_3_clicked()
{
    on_pushButton_4_clicked();
}


void info_user::on_pushButton_4_clicked()
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

void info_user::set_anh_dai_dien(){
    QString id_path = QString::fromUtf8("../../anh_dai_dien/%1.png").arg(acc_info.get_ID());
    QString default_path = QString::fromUtf8("../../anh_dai_dien/anh_dai_dien.png");
    QString png_path = QFile::exists(id_path) ? id_path : default_path;

    // Tính size thật (nhân với PixelRatio để nét trên màn hình 2K/4K)
    QSize realSize = ui->anh_dai_dien->size() * ui->anh_dai_dien->devicePixelRatio();

    // GỌI HÀM MỚI cho anh_dai_dien
    QPixmap pix = load_image_pro(png_path, realSize, 15, true);
    pix.setDevicePixelRatio(ui->anh_dai_dien->devicePixelRatio());
    ui->anh_dai_dien->setPixmap(pix);

}

QPixmap info_user::load_image_pro(const QString &path, const QSize &targetSize, int radius, bool cropToFill) {
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

void info_user::set_locker()
{
    if (acc_info.get_doi_tuong() ==  -1){
        ui->khoa_tai_khoan->setVisible(false);
        ui->mo_khoa_tai_khoan->setVisible(true);
    }
    else{
        ui->khoa_tai_khoan->setVisible(true);
        ui->mo_khoa_tai_khoan->setVisible(false);
    }
    ui->so_diem->setText(QString::number(acc_info.get_score()));
}

void info_user::on_khoa_tai_khoan_clicked()
{
    try{
        lib.khoa_tai_khoan(acc_info.get_ID());
        QMessageBox::information(this, "Thành công", "Khóa tài khoản thành công!");
    }
    catch (AppException &e) {
        QMessageBox::warning(
            this,
            QString::fromStdString(e.getTitle()),
            QString::fromStdString(e.what())
        );
    }
    lib.get_account_data().find(acc_info.get_ID(), acc_info);
    set_locker();
}


void info_user::on_mo_khoa_tai_khoan_clicked()
{
    try{
        lib.mo_khoa_tai_khoan(acc_info.get_ID());
        QMessageBox::information(this, "Thành công", "Mở khóa tài khoản thành công!");
    }
    catch (AppException &e) {
        QMessageBox::warning(
            this,
            QString::fromStdString(e.getTitle()),
            QString::fromStdString(e.what())
        );
    }
    lib.get_account_data().find(acc_info.get_ID(), acc_info);
    set_locker();
}


void info_user::on_khoi_phuc_diem_clicked()
{
    try{
        lib.khoi_phuc_diem(acc_info.get_ID());
        QMessageBox::information(this, "Thành công", "Khôi phục điểm thành công!");
    }
    catch (AppException &e) {
        QMessageBox::warning(
            this,
            QString::fromStdString(e.getTitle()),
            QString::fromStdString(e.what())
        );
    }
    lib.get_account_data().find(acc_info.get_ID(), acc_info);
    set_locker();
}

