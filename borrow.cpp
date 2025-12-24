#include "borrow.h"
#include "global.h"
#include "library.h"
#include <iostream>
#include "my_string.h"
#include "book.h"
#include "book_copies.h"
#include "Account.h"
using namespace std;

borrow::borrow(){
    ID = 0;
    Book_ID = 0;
    Book_copy_ID = 0;
    User_id = 0;
    Ngay_dat = my_time();
    Ngay_muon = my_time();
    Ngay_phai_tra = my_time();
    Ngay_tra = my_time();
    Status = StatusType::NONE;
    Tinh_trang_sach = TOT;
    lan_gia_han = 0;
    Ghi_chu = "";
    Tien_phat = 0;
}

borrow::borrow(long long ID, long long Book_ID, long long Book_copy_ID, long long User_id,
               const my_time& Ngay_dat, const my_time& Ngay_muon, const my_time& Ngay_phai_tra, const my_time& Ngay_tra,
               StatusType Status, TinhTrangsach Tinh_trang_sach, int lan_gia_han, const string& Ghi_chu, int Tien_phat){
    this->ID = ID;
    this->Book_ID = Book_ID;
    this->Book_copy_ID = Book_copy_ID;
    this->User_id = User_id;
    this->Ngay_dat = Ngay_dat;
    this->Ngay_muon = Ngay_muon;
    this->Ngay_phai_tra = Ngay_phai_tra;
    this->Ngay_tra = Ngay_tra;
    this->Status = Status;
    this->Tinh_trang_sach = Tinh_trang_sach;
    this->lan_gia_han = lan_gia_han;
    this->Ghi_chu = Ghi_chu;
    this->Tien_phat = Tien_phat;
}

borrow::~borrow(){}

void borrow::set_id(long long ID){
    this->ID = ID;
}

void borrow::set_book_id(long long Book_ID){
    this->Book_ID = Book_ID;
}

void borrow::set_book_copy_id(long long Book_copy_ID){
    this->Book_copy_ID = Book_copy_ID;
}

void borrow::set_user_id(long long User_id){
    this->User_id = User_id;
}

void borrow::set_ngay_dat(const my_time& Ngay_dat){
    this->Ngay_dat = Ngay_dat;
}

void borrow::set_ngay_muon(const my_time& Ngay_muon){
    this->Ngay_muon = Ngay_muon;
}

void borrow::set_ngay_phai_tra(const my_time& Ngay_phai_tra){
    this->Ngay_phai_tra = Ngay_phai_tra;
}

void borrow::set_ngay_tra(const my_time& Ngay_tra){
    this->Ngay_tra = Ngay_tra;
}

void borrow::set_status(StatusType Status){
    this->Status = Status;
}
void borrow::set_status(const string& Status_str){
    if (Status_str == "XU_LY"){
        this->Status = XU_LY;
    }
    else if (Status_str == "SAN_SANG"){
        this->Status = SAN_SANG;
    }
    else if (Status_str == "QUA_HAN_DAT"){
        this->Status = QUA_HAN_DAT;
    }
    else if (Status_str == "DANG_MUON"){
        this->Status = DANG_MUON;
    }
    else if (Status_str == "QUA_HAN_MUON"){
        this->Status = QUA_HAN_MUON;
    }
    else if (Status_str == "TRA_DUNG_HAN"){
        this->Status = TRA_DUNG_HAN;
    }
    else if (Status_str == "TRA_QUA_HAN"){
        this->Status = TRA_QUA_HAN;
    }
    else{
        this->Status = NONE;
    }
}
void borrow::set_tinh_trang_sach(TinhTrangsach Tinh_trang_sach){
    this->Tinh_trang_sach = Tinh_trang_sach;
}
void borrow::set_tinh_trang_sach(const string& Tinh_trang_sach_str){
    if (Tinh_trang_sach_str == "TOT"){
        this->Tinh_trang_sach = TOT;
    }
    else if (Tinh_trang_sach_str == "BINH_THUONG"){
        this->Tinh_trang_sach = BINH_THUONG;
    }
    else if (Tinh_trang_sach_str == "HONG"){
        this->Tinh_trang_sach = HONG;
    }
    else if (Tinh_trang_sach_str == "MAT"){
        this->Tinh_trang_sach = MAT;
    }
    else{
        this->Tinh_trang_sach = TOT;
    }
}
void borrow::set_lan_gia_han(int lan_gia_han){
    this->lan_gia_han = lan_gia_han;
}

void borrow::set_ghi_chu(const string& Ghi_chu){
    this->Ghi_chu = Ghi_chu;
}

void borrow::set_tien_phat(int Tien_phat){
    this->Tien_phat = Tien_phat;
}

long long borrow::get_id() const{
    return ID;
}

long long borrow::get_book_id() const{
    return Book_ID;
}
string borrow::get_book_name() const{
    book temp;
    lib.get_book_data().find(Book_ID, temp);
    return temp.get_Name();
}
long long borrow::get_book_copy_id() const{
    return Book_copy_ID;
}

long long borrow::get_user_id() const{
    return User_id;
}
string borrow::get_user_name() const{
     Account temp;
    lib.get_account_data().find(User_id, temp);
    return temp.get_ten_tai_khoan();
}

my_time borrow::get_ngay_dat() const{
    return Ngay_dat;
}

my_time borrow::get_ngay_muon() const{
    return Ngay_muon;
}

my_time borrow::get_ngay_phai_tra() const{
    return Ngay_phai_tra;
}

my_time borrow::get_ngay_tra() const{
    return Ngay_tra;
}

StatusType borrow::get_status() const{
    return Status;
}

string borrow::get_status_string() const{
    switch (Status){
        case XU_LY:
            return "XU_LY";
        case SAN_SANG:
            return "SAN_SANG";
        case QUA_HAN_DAT:
            return "QUA_HAN_DAT";
        case DANG_MUON:
            return "DANG_MUON";
        case QUA_HAN_MUON:
            return "QUA_HAN_MUON";
        case TRA_DUNG_HAN:
            return "TRA_DUNG_HAN";
        case TRA_QUA_HAN:
            return "TRA_QUA_HAN";
        default:
            return "NONE";
    }
}

TinhTrangsach borrow::get_tinh_trang_sach() const{
    return Tinh_trang_sach;
}
string borrow::get_tinh_trang_sach_string() const{
    switch (Tinh_trang_sach){
        case TOT:
            return "TOT";
        case BINH_THUONG:
            return "BINH_THUONG";
        case HONG:
            return "HONG";
        case MAT:
            return "MAT";
        default:
            return "TOT";
    }
}
int borrow::get_lan_gia_han() const{
    return lan_gia_han;
}

string borrow::get_ghi_chu() const{
    return Ghi_chu;
}

int borrow::get_tien_phat() const{
    return Tien_phat;
}

// --- Relations implementations ---
bool borrow::fetch_book(book& out) const{
    return lib.get_book_data().find(Book_ID, out);
}
bool borrow::fetch_copy(Book_copies& out) const{
    return lib.get_book_copy_data().find(Book_copy_ID, out);
}
bool borrow::fetch_user(Account& out) const{
    return lib.get_account_data().find(User_id, out);
}
