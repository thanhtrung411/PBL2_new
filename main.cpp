#include "iostream"
#include "fstream"
#include "pbl2.h"
#include "./ui_pbl2.h"
#include "dang_ky_dialog.h"
#include "ui_dang_ky_dialog.h"
#include <QApplication>
using namespace std;

////////////////////////////

FILE *peoples;

////////////////////////////

class people{
private:
    string user;
    string name;
    int gioi_tinh;
    string ngay_sinh;
    string email;
    int doi_tuong;
    string phonenumber;
    string pass;
public:
    people(string user,string name, int gioi_tinh,string ngay_sinh,string email,int doi_tuong, string phonenumber,string pass){
        this->user=user;
        this->name=name;
        this->gioi_tinh=gioi_tinh;
        this->ngay_sinh=ngay_sinh;
        this->email=email;
        this->doi_tuong=doi_tuong;
        this->phonenumber=phonenumber;
        this->pass=pass;
    };
    people();
    void setUser(string user){
        this->user=user;
    }
    string getUser(){
        return user;
    }
    void setName(string name){
        this->name=name;
    }
    string getName(){
        return name;
    }
    void setGioi_tinh(int gioi_tinh){
        if(gioi_tinh != 1 && gioi_tinh != 0){
            cout<<"khong hop le";
        }else{
        this->gioi_tinh=gioi_tinh;
        }
    }
    int getGioi_tinh(){
        return gioi_tinh;
    }
    void setNgay_sinh(string ngay_sinh){
        this->ngay_sinh=ngay_sinh;
    }
    string getNgay_sinh(){
        return ngay_sinh;
    }
    void setEmail(string email){
        this->email=email;
    }
    string getEmail(){
        return email;
    }
    void setDoi_tuong(int doi_tuong){
        this->doi_tuong=doi_tuong;
    }
    int getDoi_tuong(){
        return doi_tuong;
    }
    void setPhonenumber(string phonenumber){
        this->phonenumber=phonenumber;
    }
    string getPhonenumber(){
        return phonenumber;
    }
    void setPass(string pass){
        this->pass=pass;
    }
    string getPass(){
        return pass;
    }
};

struct Node {
    people data;
    Node* prev;
    Node* next;

    Node(people p) : data(p), prev(NULL), next(NULL) {}
};
class du_lieu_user {
private:
    people data_user_id;
    du_lieu_user* next;
    du_lieu_user* prev;
public:

};

void Doc_File(){
    peoples = fopen("user.txt","r");
    if (peoples == NULL) {
        fclose(peoples);
        fopen("user.txt","w");
        fclose(peoples);
        fopen("user.txt","r");
        return;
    }
    int n = 0;
    n = fscanf(peoples,"%d");

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pbl2 w;
    w.show();
    return a.exec();
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
    string user = ui->ten_nguoi_dung_input->text().trimmed().toUtf8().toStdString();
    string pass = ui->mat_khau_input->text().toUtf8().toStdString();

    if (user.empty()){
        markError(ui->ten_nguoi_dung_input,"Vui long nhap ten nguoi dung");
    }
    else{
        clearError(ui->ten_nguoi_dung_input);
    }
    if (pass.empty()){
        markError(ui->mat_khau_input,"Vui long nhap mat khau");
    }
    else{
        clearError(ui->mat_khau_input);
    }
}



void dang_ky_dialog::on_dang_ky_2_button_clicked()
{
    int check = 1; //neu tat ca thong tin deu hop le
    string user_nguoi_dung = ui_2->user_input->text().trimmed().toUtf8().toStdString();
    string user_name       = ui_2->name_input->text().toUtf8().toStdString();
    string ngay_sinh       = ui_2->date_birthday_input->text().toUtf8().toStdString();
    string email_address   = ui_2->email_input->text().toUtf8().toStdString();
    string so_dien_thoai   = ui_2->so_dien_thoai_input->text().toUtf8().toStdString();
    string doi_tuong       = ui_2->Doi_tuong_input->currentText().toUtf8().toStdString();
    string mat_khau        = ui_2->pass_input->text().toUtf8().toStdString();
    string mat_khau_again  = ui_2->pass_again_input->text().toUtf8().toStdString();
    int gioi_tinh = -1;
    int dieu_khoan = -1;
    if (ui_2->Boy_button->isChecked()) gioi_tinh = 0;
    if (ui_2->Girl_button->isChecked()) gioi_tinh = 1;
    if (ui_2->dieu_khoan_input->isChecked()) dieu_khoan = 1;
    if (user_nguoi_dung.empty()){
        check = 0;
        markError(ui_2->user_input,"Vui long nhap ten nguoi dung");
    }
    else clearError(ui_2->user_input);
    if (user_name.empty()){
        check = 0;
        markError(ui_2->name_input,"Vui long nhap ho va ten");
    }
    else clearError(ui_2->name_input);
    if (gioi_tinh==-1){
        check = 0;
        ui_2->gioi_tinh_input->setText("Vui long nhap gioi tinh");
        ui_2->gioi_tinh_input->setStyleSheet("QLabel{border:2px solid #e53935;}");
        QPalette pal = ui_2->gioi_tinh_input->palette();
        pal.setColor(QPalette::PlaceholderText, QColor("#e53935"));
        ui_2->gioi_tinh_input->setPalette(pal);
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
    if (check){
        //......neu tat ca deu thoa man thi them vao csdl
    }
}

