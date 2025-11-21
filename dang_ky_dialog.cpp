#include "dang_ky_dialog.h"
#include "ui_dang_ky_dialog.h"
#include "my_string.h"
#include "history.h"
#include "global.h"
#include <QStackedWidget>
#include <QWidget>

dang_ky_dialog::dang_ky_dialog(QWidget *parent)
    : QMainWindow(parent)
    , ui_2(new Ui::dang_ky_dialog)
{
    ui_2->setupUi(this);
    auto actUser = ui_2->username_input->addAction(
        QIcon(":/icons/icons_/user-interface.png"),
        QLineEdit::LeadingPosition
        );
    ui_2->username_input->setTextMargins(0, 0, 8, 0);
    ui_2->return_home->setIcon(QIcon(":/icons/icons_/home.png"));
    auto actPass = ui_2->password_input->addAction(
        QIcon(":/icons/icons_/password.png"),
        QLineEdit::LeadingPosition
        );
    ui_2->password_input->setTextMargins(0, 0, 8, 0);
    ui_2->return_home->setIcon(QIcon(":/icons/icons_/home.png"));
    ui_2->stackedWidget->setCurrentWidget(ui_2->page_2);
    ui_2->user_input->addAction(
        QIcon(":/icons/icons_/user-interface.png"),
        QLineEdit::LeadingPosition);
    ui_2->user_input->setTextMargins(0, 0, 8, 0);
    ui_2->email_input->addAction(
        QIcon(":/icons/icons_/emai.png"),
        QLineEdit::LeadingPosition);
    ui_2->email_input->setTextMargins(0, 0, 8, 0);
    ui_2->pass_input->addAction(
        QIcon(":/icons/icons_/pass.png"),
        QLineEdit::LeadingPosition);
    ui_2->pass_input->setTextMargins(0, 0, 8, 0);
    ui_2->pass_again_input->addAction(
        QIcon(":/icons/icons_/pass.png"),
        QLineEdit::LeadingPosition);
    ui_2->pass_again_input->setTextMargins(0, 0, 8, 0);
    ui_2->name_input->addAction(
        QIcon(":/icons/icons_/user-interface.png"),
        QLineEdit::LeadingPosition);
    ui_2->name_input->setTextMargins(0, 0, 8, 0);
    ui_2->so_dien_thoai_input->addAction(
        QIcon(":/icons/icons_/phone.png"),
        QLineEdit::LeadingPosition);
    ui_2->so_dien_thoai_input->setTextMargins(0, 0, 8, 0);


}

dang_ky_dialog::~dang_ky_dialog()
{
    delete ui_2;
}

static void markError(QLineEdit* w, const QString& msg) {
    w->clear();
    w->setPlaceholderText(msg);
    w->setStyleSheet("QLineEdit{border:2px solid #e53935;border-radius: 14px;color: rgb(15,15,15);}");
    QPalette pal = w->palette();
    pal.setColor(QPalette::PlaceholderText, QColor("#e53935"));
    w->setPalette(pal);
    w->setFocus();
}

static void clearError(QLineEdit* w) {
    w->setStyleSheet("QLineEdit{background: rgb(255, 255, 255); color: rgb(15, 15, 15); border: 2px solid rgb(15, 15, 15); border-radius: 14px;}");
    w->setPalette(QPalette());
}

void dang_ky_dialog::on_return_home_clicked()
{
    emit returned();
    this->close();
}


void dang_ky_dialog::on_sign_in_button_clicked()
{
    int check = 1;
    string ten_dang_nhap = ui_2->username_input->text().trimmed().toUtf8().toStdString();
    string pass = ui_2->password_input->text().toUtf8().toStdString();

    if (ten_dang_nhap.empty()){
        check = 0;
        markError(ui_2->username_input,"Vui lòng nhập tên người dùng");
    }
    else{
        clearError(ui_2->username_input);
    }
    if (pass.empty()){
        check = 0;
        markError(ui_2->password_input,"Vui lòng nhập mật khẩu");
    }
    else{
        clearError(ui_2->password_input);
    }
    ten_dang_nhap = ma_hoa_str_(ten_dang_nhap);
    pass = ma_hoa_str_(pass);
    if (check){
        if(!accout_data.check_accout(ten_dang_nhap,pass,acc_sign_in) && !ten_dang_nhap.empty() && !pass.empty()){
            markError(ui_2->username_input,"Tên người dùng hoặc mật khẩu sai");
            ui_2->password_input->clear();
            ui_2->password_input->setPlaceholderText("Mật khẩu");
            ui_2->password_input->setStyleSheet("QLineEdit{border:2px solid rgb(15,15,15);border-radius: 14px;color:rgb(15,15,15);}");
            QPalette pal = ui_2->password_input->palette();
            pal.setColor(QPalette::PlaceholderText, QColor("#0f0f0f"));
            ui_2->password_input->setPalette(pal);
            ui_2->password_input->setFocus();
        }
        else{
            history his;
            his.log_action(giai_ma_str_(ten_dang_nhap), LOGIN, 0, "");
            emit registered(acc_sign_in);
            //ui->info->setCurrentIndex(1);
            ui_2->username_input->setText("");
            ui_2->password_input->setText("");
            //ui->user_name_layout->setText(QString::fromStdString("Xin chào " + giai_ma_str_(acc_sign_in.getAccout_Name()) + ","));
            //ui->score_layout->setText("Admin");
        }
    }
}
void dang_ky_dialog::on_dang_ky_2_button_clicked()
{
    int check = 1; //neu tat ca thong tin deu hop le
    string ten_dang_nhap = ui_2->user_input->text().trimmed().toUtf8().toStdString();
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
    if (ten_dang_nhap.empty()){
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
        p.set_ID(accout_data.find_max_id() + 1);
        p.set_ten_dang_nhap(ten_dang_nhap);
        p.set_ten_tai_khoan(user_name);
        p.set_email(email_address);
        p.set_doi_tuong(doi_tuong);
        p.set_gioi_tinh(gioi_tinh);
        p.set_ngay_sinh(my_time(ngay_sinh));
        p.set_phone_number(so_dien_thoai);
        p.set_pass(mat_khau);
        p.set_level("Admin");
        p.ma_hoa_();
        history his;
        his.log_action(ten_dang_nhap, REGISTER, 0, "");
        acc_sign_in = p;
        accout_data.insert(p);
        ghi_accout(accout_data);
        box_thong_bao("Đăng ký thành công");
        emit registered(p);
        this->close();
    }
}

void dang_ky_dialog::on_sign_up_button_clicked()
{
    ui_2->stackedWidget->setCurrentWidget(ui_2->page);
}

