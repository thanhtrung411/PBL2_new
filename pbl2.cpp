/*
#include "iostream"
#include "pbl2.h"
#include "./ui_pbl2.h"
#include "dang_ky_dialog.h"
#include "ui_dang_ky_dialog.h"
using namespace std;

int so_sanh_chuoi(const char *a, const char *b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++;
        b++;
    }
    return (*a == '\0' && *b == '\0') ? 1 : 0;
}

pbl2::pbl2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pbl2)
{
    ui->setupUi(this);
}

pbl2::~pbl2()
{
    delete ui;
}

dang_ky_dialog::dang_ky_dialog(QWidget *parent)
    : QMainWindow(parent)
    , ui_2(new Ui::dang_ky_dialog)
{
    ui_2->setupUi(this);
}

dang_ky_dialog::~dang_ky_dialog()
{
    delete ui_2;
}

void pbl2::on_dang_ky_button_clicked()
{
    auto win = new dang_ky_dialog();

    // Khi cửa sổ đăng ký đóng, hiển thị lại Pbl2
    connect(win, &dang_ky_dialog::destroyed, this, [=]() {
        this->show();
    });

    win->show();
    this->hide(); // Ẩn cửa sổ chính
}

static void markError(QLineEdit* w, const QString& msg) {
    w->clear();
    w->setPlaceholderText(msg);
    w->setStyleSheet("QLineEdit{border:2px solid #e53935;}");
    QPalette pal = w->palette();
    pal.setColor(QPalette::PlaceholderText, QColor("#e53935"));
    w->setPalette(pal);
    w->setFocus();
}

static void clearError(QLineEdit* w) {
    w->setStyleSheet("");
    w->setPalette(QPalette());
}

void pbl2::on_dang_nhap_button_clicked()
{
    const QString user = ui->ten_nguoi_dung_input->text().trimmed();
    const QString pass = ui->mat_khau_input->text();
    if (user.isEmpty()){
        markError(ui->ten_nguoi_dung_input,"Vui long nhap ten nguoi dung");
    }
    else{
        clearError(ui->ten_nguoi_dung_input);
    }
    if (pass.isEmpty()){
        markError(ui->mat_khau_input,"Vui long nhap mat khau");
    }
    else{
        clearError(ui->mat_khau_input);
    }
}

void dang_ky_dialog::on_dang_ky_2_button_clicked()
{
    const QString user_nguoi_dung = ui_2->user_input->text().trimmed();
    const QString user_name       = ui_2->name_input->text();
    string ngay_sinh       = ui_2->date_birthday_input->text().toUtf8().toStdString();
    const QString email_address   = ui_2->email_input->text();
    const QString so_dien_thoai   = ui_2->so_dien_thoai_input->text();
    const QString doi_tuong       = ui_2->Doi_tuong_input->currentText();
    const QString mat_khau        = ui_2->pass_input->text();
    const QString mat_khau_again  = ui_2->pass_again_input->text();
    int gioi_tinh = -1;
    int dieu_khoan = -1;
    if (ui_2->Boy_button->isChecked()) gioi_tinh = 0;
    if (ui_2->Girl_button->isChecked()) gioi_tinh = 1;
    if (ui_2->dieu_khoan_input->isChecked()) dieu_khoan = 1;
    if (user_nguoi_dung.isEmpty()){
        markError(ui_2->user_input,"Vui long nhap ten nguoi dung");
    }
    else clearError(ui_2->user_input);
    if (user_name.isEmpty()){
        markError(ui_2->user_input,"Vui long nhap ho va ten");
    }
    else clearError(ui_2->user_input);
}

*/
