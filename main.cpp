#include "iostream"
#include "fstream"
#include "pbl2.h"
#include "./ui_pbl2.h"
#include "dang_ky_dialog.h"
#include "ui_dang_ky_dialog.h"
#include "accout.h"
#include "tree.h"
#include "my_string.h"
#include "my_file.h"
#include <QApplication>
#include <QMessageBox>
#include <QStyleFactory>
using namespace std;

////////////////////////////

FILE *peoples;
BST_Accout accout_data;
accout acc_sign_in;

////////////////////////////
void box_thong_bao(string s){
    QMessageBox box;
    box.setWindowTitle("Thông báo");
    box.setText(QString::fromStdString(s));
    box.setIconPixmap(QPixmap(":/icons/icons_/error.png").scaled(16,16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    box.setStyleSheet(R"(
    QMessageBox { background: rgb(243,246,255); }           
    QMessageBox QLabel { color:#0868ad; }           
    QMessageBox QPushButton {
    background:#fff; color:#0868ad;
    border:1px solid #d0d0d0; border-radius:8px; padding:6px 12px;
    }
    QMessageBox QPushButton:hover  { background:#f5f5f5; }
    QMessageBox QPushButton:default{ border-color:#0078d7; }
    )");
    box.exec();
}

static void applyFusionDark(QApplication& app) {
    app.setStyle(QStyleFactory::create("Fusion"));

    QPalette p;
    p.setColor(QPalette::Window,        QColor(243,246,255));
    p.setColor(QPalette::WindowText,    Qt::white);
    p.setColor(QPalette::Base,          Qt::white);
    //p.setColor(QPalette::AlternateBase, QColor(45,45,48));
    p.setColor(QPalette::Text,          QColor(8, 104, 100));
    p.setColor(QPalette::Button,        QColor(8, 104, 100));
    p.setColor(QPalette::ButtonText,    Qt::white);
    //p.setColor(QPalette::ToolTipBase,   QColor(60,60,60));
    //p.setColor(QPalette::ToolTipText,   Qt::white);
    p.setColor(QPalette::BrightText,    QColor(255,85,85));
    p.setColor(QPalette::Highlight,     QColor(0,120,215));   // “accent” khi chọn/hover
    p.setColor(QPalette::HighlightedText, Qt::white);
    p.setColor(QPalette::PlaceholderText, QColor(255,255,255));
    app.setPalette(p);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    doc_accout(accout_data);
    //applyFusionDark(a);
    pbl2 w;
    w.show();
    return a.exec();
}

void pbl2::on_dang_ky_button_clicked()
{
    auto win = new dang_ky_dialog(this);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    // Khi cửa sổ đăng ký đóng, hiển thị lại Pbl2
    connect(win, &dang_ky_dialog::registered, this, [this, win](const accout& user) {
        acc_sign_in = user;
        ui->info->setCurrentIndex(1);
        ui->vung_hien_thi->setCurrentIndex(1);
        ui->user_name_layout->setText(
            QString::fromStdString("Xin chào " + giai_ma_str_(acc_sign_in.getAccout_Name()) + ","));
        ui->score_layout->setText("Admin");
        this->show();
        this->raise();
        this->activateWindow();
        win->deleteLater();
    });
    connect(win, &dang_ky_dialog::returned, this, [this,win](){
        this->show();
        this->raise();
        this->activateWindow();
    });
   win->show();
    this->hide(); // Ẩn cửa sổ chính
}

static void markError(QLineEdit* w, const QString& msg) {
    w->clear();
    w->setPlaceholderText(msg);
    w->setStyleSheet("QLineEdit{border:2px solid #e53935;border-radius: 6px;}");
    QPalette pal = w->palette();
    pal.setColor(QPalette::PlaceholderText, QColor("#e53935"));
    w->setPalette(pal);
    w->setFocus();
}

static void clearError(QLineEdit* w) {
    w->setStyleSheet("QLineEdit{background: rgb(243, 246, 255); color: rgb(8, 104, 173); border: 2px solid rgb(69, 104, 173); border-radius: 6px;}");
    w->setPalette(QPalette());
}

void pbl2::on_dang_nhap_button_clicked()
{
    int check = 1;
    string users_id = ui->ten_nguoi_dung_input->text().trimmed().toUtf8().toStdString();
    string pass = ui->mat_khau_input->text().toUtf8().toStdString();

    if (users_id.empty()){
        check = 0;
        markError(ui->ten_nguoi_dung_input,"Vui lòng nhập tên người dùng");
    }
    else{
        clearError(ui->ten_nguoi_dung_input);
    }
    if (pass.empty()){
        check = 0;
        markError(ui->mat_khau_input,"Vui lòng nhập mật khẩu");
    }
    else{
        clearError(ui->mat_khau_input);
    }
    pass = ma_hoa_str_(pass);
    if (check){
        if(!accout_data.check_accout(users_id,pass,acc_sign_in) && !users_id.empty() && !pass.empty()){
            markError(ui->ten_nguoi_dung_input,"Tên người dùng hoặc mật khẩu sai");
            ui->mat_khau_input->clear();
            ui->mat_khau_input->setPlaceholderText("Mật khẩu");
            ui->mat_khau_input->setStyleSheet("QLineEdit{border:2px solid rgb(8, 104, 173);border-radius: 6px;}");
            QPalette pal = ui->mat_khau_input->palette();
            pal.setColor(QPalette::PlaceholderText, QColor("#0868ad"));
            ui->mat_khau_input->setPalette(pal);
            ui->mat_khau_input->setFocus();
        }
        else{
            ui->info->setCurrentIndex(1);
            ui->ten_nguoi_dung_input->setText("");
            ui->mat_khau_input->setText("");
            ui->user_name_layout->setText(QString::fromStdString("Xin chào " + giai_ma_str_(acc_sign_in.getAccout_Name()) + ","));
            ui->score_layout->setText("Admin");
        }
    }
}

void dang_ky_dialog::on_return_home_clicked()
{
    emit returned();
    this->close();
}


void dang_ky_dialog::on_dang_ky_2_button_clicked()
{
    int check = 1; //neu tat ca thong tin deu hop le
    string user_nguoi_dung = ui_2->user_input->text().trimmed().toUtf8().toStdString();
    string user_name       = ui_2->name_input->text().toUtf8().toStdString();
    string ngay_sinh       = ui_2->date_birthday_input->text().toUtf8().toStdString();
    string email_address   = ui_2->email_input->text().toUtf8().toStdString();
    string so_dien_thoai   = ui_2->so_dien_thoai_input->text().toUtf8().toStdString();
    int doi_tuong          = ui_2->Doi_tuong_input->currentText().toInt();
    string mat_khau        = ui_2->pass_input->text().toUtf8().toStdString();
    string mat_khau_again  = ui_2->pass_again_input->text().toUtf8().toStdString();
    int gioi_tinh = -1;
    int dieu_khoan = -1;
    if (ui_2->Boy_button->isChecked()) gioi_tinh = 0;
    if (ui_2->Girl_button->isChecked()) gioi_tinh = 1;
    if (ui_2->dieu_khoan_input->isChecked()) dieu_khoan = 1;
    if (user_nguoi_dung.empty()){
        check = 0;
        markError(ui_2->user_input,"Vui lòng nhập tên người dùng");
    }
    else clearError(ui_2->user_input);
    if (user_name.empty()){
        check = 0;
        markError(ui_2->name_input,"Vui lòng nhập họ tên");
    }
    else clearError(ui_2->name_input);
    if (gioi_tinh==-1){
        check = 0;
        QLabel* lb = ui_2->gioi_tinh_input;
        lb->setStyleSheet("color: #e53935;");
        ui_2->gioi_tinh_input->setText("Vui lòng nhập giới tính");
        ui_2->gioi_tinh_input->setFocus();
    }
    else{
        ui_2->gioi_tinh_input->setStyleSheet("");
        ui_2->gioi_tinh_input->setPalette(QPalette());
    }
    if (email_address.empty()){
        check = 0;
        markError(ui_2->email_input,"Vui long nhap dia chi email");
    }
    else{
        clearError(ui_2->email_input);
    }
    if (so_dien_thoai.empty()){
        check = 0;
        markError(ui_2->so_dien_thoai_input,"Vui long nhap so dien thoai");
    }
    else clearError(ui_2->so_dien_thoai_input);
    if (mat_khau.empty()){
        check = 0;
        markError(ui_2->pass_input,"Vui long nhap mat khau");
    }
    else clearError(ui_2->pass_input);
    if (mat_khau_again.empty()){
        check = 0;
        markError(ui_2->pass_again_input,"Vui long nhap lai mat khau");
    }
    else{
        clearError(ui_2->pass_again_input);
        if (!(mat_khau==mat_khau_again)){
            check = 0;
            markError(ui_2->pass_again_input,"Mật khẩu không đúng");
        }
        else{
            clearError(ui_2->pass_again_input);
        }
    }
    if (!(ui_2->dieu_khoan_input->isChecked())){
        check = 0;
        QLabel* lb = ui_2->Dieu_khoan_canh_bao;
        lb->setStyleSheet("color: #e53935;");
        ui_2->Dieu_khoan_canh_bao->setText("Vui lòng đồng ý với điều khoản");
        ui_2->Dieu_khoan_canh_bao->setFocus();
    }
    else {
        ui_2->Dieu_khoan_canh_bao->clear();
        ui_2->Dieu_khoan_canh_bao->setFocus();
    }
    if (check){
        accout p;
        p.setAccout_id(user_nguoi_dung);
        p.setAccout_name(user_name);
        p.setEmail(email_address);
        p.setDoi_tuong(doi_tuong);
        p.setGioi_tinh(gioi_tinh);
        p.setNgay_sinh(ngay_sinh);
        p.setPhonenumber(so_dien_thoai);
        p.setPass(mat_khau);
        p.setlevel("Admin");
        p.ma_hoa_();
        acc_sign_in = p;
        accout_data.insert_Accout(p);
        ghi_accout(accout_data);
        box_thong_bao("Đăng ký thành công");
        emit registered(p);
        this->close();
    }
}
