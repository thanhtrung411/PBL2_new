#include "dang_ky_dialog.h"
#include "ui_dang_ky_dialog.h"
#include "my_string.h"
#include "history.h"
#include "global.h"
#include "library.h"
#include <QStackedWidget>
#include <QWidget>
#include <QTimer>
#include <QMessageBox>

dang_ky_dialog::dang_ky_dialog(QWidget *parent)
    : QMainWindow(parent)
    , ui_2(new Ui::dang_ky_dialog)
{
    ui_2->setupUi(this);
    auto actUser = ui_2->username_input->addAction(
        QIcon(":/icons/icons_/user-interface.png"),
        QLineEdit::LeadingPosition
        );
    ui_2->username_input->setTextMargins(0,0,4,0);
    //ui_2->return_home->setIcon(QIcon(":/icons/icons_/home.png"));
    auto actPass = ui_2->password_input->addAction(
        QIcon(":/icons/icons_/password.png"),
        QLineEdit::LeadingPosition
        );
    ui_2->password_input->setTextMargins(0, 0, 4, 0);
    //ui_2->return_home->setIcon(QIcon(":/icons/icons_/home.png"));
    ui_2->stackedWidget->setCurrentWidget(ui_2->page_2);
    ui_2->ten_dang_nhap_2_input->addAction(
        QIcon(":/icons/icons_/user-interface.png"),
        QLineEdit::LeadingPosition);
    ui_2->ten_dang_nhap_2_input->setTextMargins(0, 0, 4, 0);
    ui_2->ho_ten_2_input->addAction(
        QIcon(":/icons/icons_/user-interface.png"),
        QLineEdit::LeadingPosition);
    ui_2->ho_ten_2_input->setTextMargins(0, 0, 4, 0);
    ui_2->email_2_input->addAction(
        QIcon(":/icons/icons_/emai.png"),
        QLineEdit::LeadingPosition);
    ui_2->email_2_input->setTextMargins(0, 0, 4, 0);
    ui_2->so_dien_thoai_2_input->addAction(
        QIcon(":/icons/icons_/phone.png"),
        QLineEdit::LeadingPosition);
    ui_2->so_dien_thoai_2_input->setTextMargins(0, 0, 4, 0);
    if (QLineEdit* dateLineEdit = ui_2->ngay_sinh_2_input->findChild<QLineEdit*>()) {
        dateLineEdit->addAction(
            QIcon(":/icons/icons_/date.png"),
            QLineEdit::LeadingPosition);
        dateLineEdit->setTextMargins(0, 0, 0, 0);
    }
    ui_2->password_2_input->addAction(
        QIcon(":/icons/icons_/pass.png"),
        QLineEdit::LeadingPosition);
    ui_2->password_2_input->setTextMargins(0, 0, 4, 0);
    ui_2->pass_again_2_input->addAction(
        QIcon(":/icons/icons_/pass.png"),
        QLineEdit::LeadingPosition);
    ui_2->pass_again_2_input->setTextMargins(0, 0, 4, 0);
    on_dang_nhap_button_clicked();
    this->adjustSize();
    ui_2->so_dien_thoai_quen_input->addAction(
        QIcon(":/icons/icons_/phone.png"),
        QLineEdit::LeadingPosition);
    ui_2->so_dien_thoai_quen_input->setTextMargins(0, 0, 4, 0);
    ui_2->email_quen->addAction(
        QIcon(":/icons/icons_/emai.png"),
        QLineEdit::LeadingPosition);
    ui_2->email_quen->setTextMargins(0, 0, 4, 0);
    QTimer::singleShot(0, this, [this](){
        this->resize(600, 425);
    });
}

dang_ky_dialog::~dang_ky_dialog()
{
    delete ui_2;
}

void dang_ky_dialog::set_up_register_mode(std::string role) {
    this->register_role = role;
    this->is_admin = true;

    // Chuyển ngay sang trang đăng ký
    on_dang_ky_button_clicked();

    // Ẩn mấy cái nút thừa thải đi
    if (ui_2->horizontalWidget_3) ui_2->horizontalWidget_3->setVisible(false); // Nút toggle trên cùng
    if (ui_2->pushButton) ui_2->pushButton->setVisible(false); // Nút "Bạn đã có tài khoản"
    if (ui_2->label_4) ui_2->label_4->setVisible(false); // Dòng text chào mừng

    // Đổi tiêu đề cho đúng
    if (role == "Librarian") {
        ui_2->label_6->setText("THÊM THỦ THƯ MỚI");
    } else {
        ui_2->label_6->setText("THÊM ĐỘC GIẢ MỚI");
    }
}

static void markError(QLineEdit* w, const QString& msg) {
    w->clear();
    w->setPlaceholderText(msg);
    w->setStyleSheet(R"(QLineEdit {
                background-color: #e8ecef; 
                border-radius: 5px; 
                border: 1px solid #ff0000; 
                padding: 8px 10px; 
                color: #1E1E1E; 
                font-size: 12px;
            }

            QLineEdit:hover {
                background-color: #E5E9ED;
            }
            QLineEdit:focus {
                background-color: #FFFFFF; 
                border: 1px solid #3498db; 
            })");
    QPalette pal = w->palette();
    pal.setColor(QPalette::PlaceholderText, QColor("#e53935"));
    w->setPalette(pal);
    w->setFocus();
}

static void clearError(QLineEdit* w) {
    w->setStyleSheet(R"(QLineEdit {
                background-color: #e8ecef; 
                border-radius: 5px; 
                border: 1px solid #E0E4E8; 
                padding: 8px 10px; 
                color: #1E1E1E; 
                font-size: 12px;
            }

            QLineEdit:hover {
                background-color: #E5E9ED;
            }
            QLineEdit:focus {
                background-color: #FFFFFF; 
                border: 1px solid #3498db; 
            })");
    w->setPalette(QPalette());
}

void dang_ky_dialog::on_return_home_clicked()
{
    emit returned();
    this->close();
}


void dang_ky_dialog::on_sign_in_button_clicked()
{
    try {
        Account acc;
        string ten_dang_nhap = ui_2->username_input->text().trimmed().toUtf8().toStdString();
        string pass = ui_2->password_input->text().toUtf8().toStdString();
        ten_dang_nhap = ma_hoa_str_(ten_dang_nhap);
        pass = ma_hoa_str_(pass);
        lib.dang_nhap_tai_khoan(acc,ten_dang_nhap, pass);
        emit registered(acc);
        this->close();
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Đăng nhập thất bại", QString::fromStdString(e.what()));
    }
    catch (...) {
        QMessageBox::warning(this, "Đăng nhập thất bại", "Đã có lỗi xảy ra trong quá trình đăng nhập.");
    }
}

//////////
void dang_ky_dialog::on_sign_up_button_clicked()
{
    ui_2->stackedWidget->setCurrentWidget(ui_2->page);
}


void dang_ky_dialog::on_dang_nhap_button_clicked()
{
    ui_2->user_label->setVisible(true);
    ui_2->password_label->setVisible(true);
    ui_2->username_input->setVisible(true);
    ui_2->password_input->setVisible(true);
    ui_2->quen_mk_layout->setEnabled(true);
    ui_2->dang_nhap_button_layout->setEnabled(true);    
    ui_2->ten_dang_nhap_label->setVisible(false);
    ui_2->ho_ten_label->setVisible(false);
    ui_2->email_label->setVisible(false);
    ui_2->so_dien_thoai_label->setVisible(false);
    ui_2->ngay_sinh_label->setVisible(false);
    ui_2->password_label_2->setVisible(false);
    ui_2->pass_again_input_2->setVisible(false);
    ui_2->ten_dang_nhap_2_input->setVisible(false);
    ui_2->ho_ten_2_input->setVisible(false);
    ui_2->email_2_input->setVisible(false);
    ui_2->so_dien_thoai_2_input->setVisible(false);
    ui_2->ngay_sinh_2_input->setVisible(false);
    ui_2->password_2_input->setVisible(false);
    ui_2->pass_again_2_input->setVisible(false);
    ui_2->layout_dang_ky->setEnabled(false);
    ui_2->dieu_khoan->setVisible(false);
    ui_2->forget_button->setVisible(true);
    ui_2->dang_ky_2_button_2->setVisible(false);
    ui_2->gioi_tinh->setVisible(false);
    ui_2->sign_in_button->setVisible(true);
    ui_2->dang_nhap_button->setStyleSheet(R"(color: rgb(0, 0, 0);
        background-color: rgb(255,255,255);
        border-radius: 10px;)");
    ui_2->dang_ky_button->setStyleSheet(R"(color: rgb(0, 0, 0);
        background-color: rgb(236, 235, 240);
        border-radius: 10px;
        border: 0px;)");
    this->resize(600, 425);
}


void dang_ky_dialog::on_dang_ky_button_clicked()
{
    ui_2->user_label->setVisible(false);
    ui_2->password_label->setVisible(false);
    ui_2->username_input->setVisible(false);
    ui_2->password_input->setVisible(false);
    ui_2->quen_mk_layout->setEnabled(false);
    ui_2->dang_nhap_button_layout->setEnabled(false);
    ui_2->ten_dang_nhap_label->setVisible(true);
    ui_2->ho_ten_label->setVisible(true);
    ui_2->email_label->setVisible(true);
    ui_2->so_dien_thoai_label->setVisible(true);
    ui_2->ngay_sinh_label->setVisible(true);
    ui_2->password_label_2->setVisible(true);
    ui_2->pass_again_input_2->setVisible(true);
    ui_2->ten_dang_nhap_2_input->setVisible(true);
    ui_2->ho_ten_2_input->setVisible(true);
    ui_2->email_2_input->setVisible(true);
    ui_2->so_dien_thoai_2_input->setVisible(true);
    ui_2->ngay_sinh_2_input->setVisible(true);
    ui_2->password_2_input->setVisible(true);
    ui_2->pass_again_2_input->setVisible(true);
    ui_2->layout_dang_ky->setEnabled(true);
    ui_2->dieu_khoan->setVisible(true);
    ui_2->forget_button->setVisible(false);
    ui_2->dang_ky_2_button_2->setVisible(true);
    ui_2->gioi_tinh->setVisible(true);
    ui_2->sign_in_button->setVisible(false);
    ui_2->dang_ky_button->setStyleSheet(R"(color: rgb(0, 0, 0);
        background-color: rgb(255,255,255);
        border-radius: 10px;)");
    ui_2->dang_nhap_button->setStyleSheet(R"(color: rgb(0, 0, 0);
        background-color: rgb(236, 235, 240);
        border: 0px;
        border-radius: 10px;)");
    this->resize(this->width(), 755);
}


void dang_ky_dialog::on_forget_button_clicked()
{
    ui_2->stackedWidget->setCurrentWidget(ui_2->page_3);
    this->resize(600, 330);
}


void dang_ky_dialog::on_forget_button_2_clicked()
{
    ui_2->stackedWidget->setCurrentWidget(ui_2->page_2);
    on_dang_nhap_button_clicked();
}


void dang_ky_dialog::on_dang_ky_2_button_2_clicked()
{
    int ok = 1;
    if (ui_2->ten_dang_nhap_2_input->text().trimmed().isEmpty()){
        ok = 0;
        markError(ui_2->ten_dang_nhap_2_input,"Vui lòng nhập tên đăng nhập");
    }
    else if (lib.get_account_data().check_ten_dang_nhap(ma_hoa_str_(ui_2->ten_dang_nhap_2_input->text().trimmed().toUtf8().toStdString()))){
        ok = 0;
    }
    else clearError(ui_2->ten_dang_nhap_2_input);
    if (ui_2->ho_ten_2_input->text().trimmed().isEmpty()){
        ok = 0;
        markError(ui_2->ho_ten_2_input,"Vui lòng nhập họ tên");
    }
    else clearError(ui_2->ho_ten_2_input);
    if (ui_2->email_2_input->text().trimmed().isEmpty()){
        ok = 0;
        markError(ui_2->email_2_input,"Vui lòng nhập địa chỉ email");
    }
    else clearError(ui_2->email_2_input);
    if (ui_2->so_dien_thoai_2_input->text().trimmed().isEmpty()){
        ok = 0;
        markError(ui_2->so_dien_thoai_2_input,"Vui lòng nhập số điện thoại");
    }
    else if (ui_2->so_dien_thoai_2_input->text().trimmed().size()<10 || ui_2->so_dien_thoai_2_input->text().trimmed().size()>11){
        ok = 0;
    }
    else{
        for (char c : ui_2->so_dien_thoai_2_input->text().trimmed().toUtf8().toStdString()) {
            if (!isdigit(c)) {
                ok = 0;
                break;
            }
        }
    }
    if (ok) clearError(ui_2->so_dien_thoai_2_input);
    if (ui_2->password_2_input->text().isEmpty()){
        ok = 0;
        markError(ui_2->password_2_input,"Vui lòng nhập mật khẩu");
    }
    else clearError(ui_2->password_2_input);
    if (ui_2->pass_again_2_input->text().isEmpty()){
        ok = 0;
        markError(ui_2->pass_again_2_input,"Vui lòng nhập lại mật khẩu");
    }
    else{
        clearError(ui_2->pass_again_2_input);
        if (!(ui_2->password_2_input->text() == ui_2->pass_again_2_input->text())){
            ok = 0;
            markError(ui_2->pass_again_2_input,"Mật khẩu không đúng");
        }
        else clearError(ui_2->pass_again_2_input);
    }
    ok = 1;
    if (ok){
        string ten_dang_nhap = ui_2->ten_dang_nhap_2_input->text().trimmed().toUtf8().toStdString();
        string ho_ten       = ui_2->ho_ten_2_input->text().toUtf8().toStdString();
        string email        = ui_2->email_2_input->text().toUtf8().toStdString();
        string so_dien_thoai= ui_2->so_dien_thoai_2_input->text().toUtf8().toStdString();
        my_time ngay_sinh;
        ngay_sinh = my_time(ui_2->ngay_sinh_2_input->text().toUtf8().toStdString());
        string mat_khau     = ui_2->password_2_input->text().toUtf8().toStdString();
        Account p;
        p.set_ID(lib.get_account_data().find_max_id() + 1);
        p.set_ten_dang_nhap(ten_dang_nhap);
        p.set_ten_tai_khoan(ho_ten);
        p.set_email(email);
        p.set_phone_number(so_dien_thoai);
        p.set_ngay_sinh(ngay_sinh);
        if (ui_2->gioi_tinh->currentIndex()==0)
            p.set_gioi_tinh(0);
        else if (ui_2->gioi_tinh->currentIndex()==1){
            p.set_gioi_tinh(1);
        }
        else {
            p.set_gioi_tinh(2);
        }
        p.set_doi_tuong(0);
        p.set_pass(mat_khau);
        p.set_level(this->register_role);
        my_time now = my_time::now();
        p.set_date_created(now);
        lib.dang_ky_tai_khoan(p);
        box_thong_bao("Đăng ký thành công!");
        emit registered(p);
        this->close();
    }
}


void dang_ky_dialog::on_ten_dang_nhap_2_input_textChanged(const QString &arg1)
{
    string ten_dang_nhap = arg1.trimmed().toUtf8().toStdString();
    string ten_dang_nhap_khong_ma_hoa = ten_dang_nhap;
    ten_dang_nhap = ma_hoa_str_(ten_dang_nhap);
    if (is_admin){
        if (lib.get_account_data().check_ten_dang_nhap(ten_dang_nhap_khong_ma_hoa)){
            ui_2->ten_dang_nhap_label->setText("Tên đăng nhập đã tồn tại");
            ui_2->ten_dang_nhap_label->setStyleSheet("color: #e53935;");

        }
        else{
            ui_2->ten_dang_nhap_label->setText("Tên đăng nhập");
            ui_2->ten_dang_nhap_label->setStyleSheet("color: #333333;");
        }
    }
    else{
        if (lib.get_account_data().check_ten_dang_nhap(ten_dang_nhap)){
            ui_2->ten_dang_nhap_label->setText("Tên đăng nhập đã tồn tại");
            ui_2->ten_dang_nhap_label->setStyleSheet("color: #e53935;");

        }
        else{
            ui_2->ten_dang_nhap_label->setText("Tên đăng nhập");
            ui_2->ten_dang_nhap_label->setStyleSheet("color: #333333;");
        }
    }
}


void dang_ky_dialog::on_email_2_input_textEdited(const QString &arg1)
{
    string email = arg1.trimmed().toUtf8().toStdString();
    if (!is_valid_email(email)){
        ui_2->email_label->setText("Địa chỉ email không hợp lệ");
        ui_2->email_label->setStyleSheet("color: #e53935;");
    }
    else{
        ui_2->email_label->setText("Địa chỉ email");
        ui_2->email_label->setStyleSheet("color: #333333;");
    }
}


void dang_ky_dialog::on_so_dien_thoai_2_input_textEdited(const QString &arg1)
{
}


void dang_ky_dialog::on_so_dien_thoai_2_input_textChanged(const QString &arg1)
{
    string so_dien_thoai = arg1.trimmed().toUtf8().toStdString();
    if (so_dien_thoai.size()<10 || so_dien_thoai.size()>11){
        ui_2->so_dien_thoai_label->setText("Số điện thoại không hợp lệ");
        ui_2->so_dien_thoai_label->setStyleSheet("color: #e53935;");
        return;
    }
    else{
        ui_2->so_dien_thoai_label->setText("Số điện thoại");
        ui_2->so_dien_thoai_label->setStyleSheet("color: #333333;");
    }
    int ok = 1;
    for (char c : so_dien_thoai) {
        if (!isdigit(c)) {
            ok = 0;
            ui_2->so_dien_thoai_label->setText("Số điện thoại chỉ được chứa chữ số");
            ui_2->so_dien_thoai_label->setStyleSheet("color: #e53935;");
            return;
        }
    }
    if (ok){
        ui_2->so_dien_thoai_label->setText("Số điện thoại");
        ui_2->so_dien_thoai_label->setStyleSheet("color: #333333;");
    }
}


void dang_ky_dialog::on_lay_lai_mat_khau_button_clicked()
{
    if (ui_2->so_dien_thoai_quen_input->text().trimmed().isEmpty() && ui_2->email_quen->text().trimmed().isEmpty()){
        box_thong_bao("Vui lòng nhập số điện thoại hoặc email để lấy lại mật khẩu");
        return;
    }
    string so_dien_thoai = ui_2->so_dien_thoai_quen_input->text().trimmed().toUtf8().toStdString();
    string email = ui_2->email_quen->text().trimmed().toUtf8().toStdString();
    so_dien_thoai = ma_hoa_str_(so_dien_thoai);
    email = ma_hoa_str_(email);
    Account a;

    try{
        lib.quen_mat_khau(so_dien_thoai, email);
        ui_2->so_dien_thoai_quen_input->setText("");
        ui_2->email_quen->setText("");
        box_thong_bao("Mật khẩu của bạn đã được đặt lại. Vui lòng kiểm tra và đổi mật khẩu sau khi đăng nhập.");
        emit registered(lib.get_acc_sign_in());
        this->close();
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Lấy lại mật khẩu thất bại", QString::fromStdString(e.what()));
    }
    catch (...) {
        QMessageBox::warning(this, "Lấy lại mật khẩu thất bại", "Đã có lỗi xảy ra trong quá trình lấy lại mật khẩu.");
    }
}

