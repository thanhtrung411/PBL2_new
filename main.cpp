#include "iostream"
#include "fstream"
#include "pbl2.h"
#include "./ui_pbl2.h"
#include "dang_ky_dialog.h"
#include "ui_dang_ky_dialog.h"
#include "accout.h"
#include "tree.h"
#include "my_string.h"
#include <QApplication>
#include <QMessageBox>
#include <QStyleFactory>
using namespace std;

////////////////////////////

FILE *peoples;
BST_Accout accout_data;


////////////////////////////

class sach{
    private:
    string ma_sach;
    string anh_sach;
    string ten_sach;
    string tac_gia;
    string nha_xuat_ban;
    string nam_xuat;
    string hinh_thuc;
    string so_trang;
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

void doc_accout(){
    fstream file;
    file.open("../accout.txt", ios::in);
    if (!file.is_open()) {
        cout << "Khong the mo file de ghi." << endl;
        return;
    }
    int n = 0;
    file >> n;
    for (int i = 0; i < n; i++) {
        string user_id, user_name, email, phonenumber, pass;
        int gioi_tinh, doi_tuong;
        string ngay_sinh;
        file.ignore();
        getline(file, user_id);
        getline(file, user_name);
        getline(file, email);
        getline(file, phonenumber);
        file >> gioi_tinh;
        file.ignore();
        file >> doi_tuong;
        file.ignore();
        getline(file, ngay_sinh);
        getline(file, pass);
        accout p;
        p.setAccout_id(user_id);
        p.setAccout_name(user_name);
        p.setEmail(email);
        p.setDoi_tuong(doi_tuong);
        p.setGioi_tinh(gioi_tinh);
        p.setNgay_sinh(ngay_sinh);
        p.setPhonenumber(phonenumber);
        p.setPass(pass);
        int ok = 0;
        accout_data.insert_Accout(p);
    }
}

void ghi_accout(){
    fstream file;
    file.open("../accout.txt", ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "Khong the mo file de ghi." << endl;
        return;
    }
    int n = accout_data.count_accout();
    file << n << endl;
    accout_data.write_accout(file);
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

    doc_accout();
    QApplication a(argc, argv);
    //applyFusionDark(a);
    pbl2 w;
    w.show();
    return a.exec();
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
    string users_id = ui->ten_nguoi_dung_input->text().trimmed().toUtf8().toStdString();
    string pass = ui->mat_khau_input->text().toUtf8().toStdString();

    if (users_id.empty()){
        markError(ui->ten_nguoi_dung_input,"Vui lòng nhập tên người dùng");
    }
    else{
        clearError(ui->ten_nguoi_dung_input);
    }
    if (pass.empty()){
        markError(ui->mat_khau_input,"Vui lòng nhập mật khẩu");
    }
    else{
        clearError(ui->mat_khau_input);
    }
    accout sign_in;
    ma_hoa_str_(pass);
    if(!accout_data.check_accout(users_id,pass,sign_in) && !users_id.empty() && !pass.empty()){
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
        p.ma_hoa_();
        accout_data.insert_Accout(p);
        ghi_accout();
        QMessageBox box;
        box.setWindowTitle("Thông báo");
        box.setText("Bạn đã đăng ký thành công.");
        box.setIconPixmap(QPixmap(":/icons/icons_/check.png").scaled(16,16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        box.setStyleSheet(R"(
        QMessageBox { background: rgb(243,246,255); }             /* nền hộp */
        QMessageBox QLabel { color:#0868ad; }              /* màu chữ trong hộp */
        QMessageBox QPushButton {
        background:#fff; color:#0868ad;
        border:1px solid #d0d0d0; border-radius:8px; padding:6px 12px;
        }
        QMessageBox QPushButton:hover  { background:#f5f5f5; }
        QMessageBox QPushButton:default{ border-color:#0078d7; }
        )");
        box.exec();
    }
}

