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
class sach{
    private:
    string ma_sach;
    string anh_sach;
    string ten_sach;
    string tac_gia;
    string nha_xuat_ban;
    string nam_xuat;
    string hinh_thuc;
    string so trang;
    string ma_Deway;
    string vi_tri_luu_tru;
    string loai_tai_lieu;
    string ISBN;
    string don_gia;
    string ngon_ngu;
    string tu_khoa;
    string chu_de;
    string chuyen_nganh;
    string mo_ta;
    public:
    sach(string ma_sach, string anh_sach, string ten_sach, string tac_gia, string nha_xuat_ban,
         string nam_xuat, string hinh_thuc, string so_trang, string ma_Deway, string vi_tri_luu_tru,
         string loai_tai_lieu, string ISBN, string don_gia, string ngon_ngu, string tu_khoa,
         string chu_de, string chuyen_nganh, string mo_ta) {
        this->ma_sach = ma_sach;
        this->anh_sach = anh_sach;
        this->ten_sach = ten_sach;
        this->tac_gia = tac_gia;
        this->nha_xuat_ban = nha_xuat_ban;
        this->nam_xuat = nam_xuat;
        this->hinh_thuc = hinh_thuc;
        this->so_trang = so_trang;
        this->ma_Deway = ma_Deway;
        this->vi_tri_luu_tru = vi_tri_luu_tru;
        this->loai_tai_lieu = loai_tai_lieu;
        this->ISBN = ISBN;
        this->don_gia = don_gia;
        this->ngon_ngu = ngon_ngu;
        this->tu_khoa = tu_khoa;
        this->chu_de = chu_de;
        this->chuyen_nganh = chuyen_nganh;
        this->mo_ta = mo_ta;
    }
    sach() {}
    void setMa_sach(string ma_sach) {
        this->ma_sach = ma_sach;
    }
    string getMa_sach() {
        return ma_sach;
    }
    void setAnh_sach(string anh_sach) {
        this->anh_sach = anh_sach;
    }
    string getAnh_sach() {
        return anh_sach;
    }
    void setTen_sach(string ten_sach) {
        this->ten_sach = ten_sach;
    }
    string getTen_sach() {
        return ten_sach;
    }
    void setTac_gia(string tac_gia) {
        this->tac_gia = tac_gia;
    }
    string getTac_gia() {
        return tac_gia;
    }
    void setNha_xuat_ban(string nha_xuat_ban) {
        this->nha_xuat_ban = nha_xuat_ban;
    }
    string getNha_xuat_ban() {
        return nha_xuat_ban;
    }
    void setNam_xuat(string nam_xuat) {
        this->nam_xuat = nam_xuat;
    }
    string getNam_xuat() {
        return nam_xuat;
    }
    void setHinh_thuc(string hinh_thuc) {
        this->hinh_thuc = hinh_thuc;
    }
    string getHinh_thuc() {
        return hinh_thuc;
    }
    void setSo_trang(string so_trang) {
        this->so_trang = so_trang;
    }
    string getSo_trang() {
        return so_trang;
    }
    void setMa_Deway(string ma_Deway) {
        this->ma_Deway = ma_Deway;
    }
    string getMa_Deway() {
        return ma_Deway;
    }
    void setVi_tri_luu_tru(string vi_tri_luu_tru) {
        this->vi_tri_luu_tru = vi_tri_luu_tru;
    }
    string getVi_tri_luu_tru() {
        return vi_tri_luu_tru;
    }
    void setLoai_tai_lieu(string loai_tai_lieu) {
        this->loai_tai_lieu = loai_tai_lieu;
    }
    string getLoai_tai_lieu() {
        return loai_tai_lieu;
    }
    void setISBN(string ISBN) {
        this->ISBN = ISBN;
    }
    string getISBN() {
        return ISBN;
    }
    void setDon_gia(string don_gia) {
        this->don_gia = don_gia;
    }
    string getDon_gia() {
        return don_gia;
    }
    void setNgon_ngu(string ngon_ngu) {
        this->ngon_ngu = ngon_ngu;
    }
    string getNgon_ngu() {
        return ngon_ngu;
    }
    void setTu_khoa(string tu_khoa) {
        this->tu_khoa = tu_khoa;
    }
    string getTu_khoa() {
        return tu_khoa;
    }
    void setChu_de(string chu_de) {
        this->chu_de = chu_de;
    }
    string getChu_de() {
        return chu_de;
    }
    void setChuyen_nganh(string chuyen_nganh) {
        this->chuyen_nganh = chuyen_nganh;
    }
    string getChuyen_nganh() {
        return chuyen_nganh;
    }
    void setMo_ta(string mo_ta) {
        this->mo_ta = mo_ta;
    }
    string getMo_ta() {
        return mo_ta;
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
    Node* head;
    Node* tail;

public:
    du_lieu_user() {
        head = tail = NULL;
    }

    // Them vao cuoi
    void push_back(people p) {
        Node* newNode = new Node(p);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Duyet danh sach
    void display() {
        Node* temp = head;
        while (temp) {
            cout << "User: " << temp->data.getUser()
            << " | Name: " << temp->data.getName()
            << " | Email: " << temp->data.getEmail()
            << " | Phone: " << temp->data.getPhonenumber() << endl;
            temp = temp->next;
        }
    }

    void remove(string username) {
        Node* temp = head;
        while (temp) {
            if (temp->data.getUser() == username) {
                if (temp == head) head = temp->next;
                if (temp == tail) tail = temp->prev;
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                delete temp;
                return;
            }
            temp = temp->next;
        }
    }
};

du_lieu_user users_;

void Doc_File(){
    peoples = fopen("user.txt","r");
    people s;
    s.setDoi_tuong(5);

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

