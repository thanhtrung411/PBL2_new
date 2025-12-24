#ifndef BORROW_H
#define BORROW_H
#include <iostream>
#include "my_time.h"
#include "my_string.h"
using namespace std;
class book;
class Book_copies;
class Account;

enum StatusType {
    NONE,
    XU_LY,
    SAN_SANG,
    QUA_HAN_DAT,

    DANG_MUON,
    QUA_HAN_MUON,

    TRA_DUNG_HAN,
    TRA_QUA_HAN
};

enum TinhTrangsach {
    TOT,
    BINH_THUONG,
    HONG,
    MAT
};

class borrow {
private:
    long long ID;
    long long Book_ID; //FK
    long long Book_copy_ID; //FK
    long long User_id; //FK
    my_time Ngay_dat;
    my_time Ngay_muon;
    my_time Ngay_phai_tra;
    my_time Ngay_tra;
    StatusType Status;
    int lan_gia_han;
    TinhTrangsach Tinh_trang_sach;
    string Ghi_chu;
    int Tien_phat;

public:
    borrow();
    borrow(long long ID,
           long long Book_ID,
           long long Book_copy_ID,
           long long User_id,
           const my_time& Ngay_dat,
           const my_time& Ngay_muon,
           const my_time& Ngay_phai_tra,
           const my_time& Ngay_tra,
           StatusType Status,
           TinhTrangsach Tinh_trang_sach,
           int lan_gia_han,
           const string& Ghi_chu,
           int Tien_phat);
    ~borrow();

    void set_id(long long ID);
    void set_book_id(long long Book_ID);
    void set_book_copy_id(long long Book_copy_ID);
    void set_user_id(long long User_id);
    void set_ngay_dat(const my_time& Ngay_dat);
    void set_ngay_muon(const my_time& Ngay_muon);
    void set_ngay_phai_tra(const my_time& Ngay_phai_tra);
    void set_ngay_tra(const my_time& Ngay_tra);
    void set_status(StatusType Status);
    void set_status(const string& Status_str);
    void set_tinh_trang_sach(TinhTrangsach Tinh_trang_sach);
    void set_tinh_trang_sach(const string& Tinh_trang_sach_str);
    void set_lan_gia_han(int lan_gia_han);
    void set_ghi_chu(const string& Ghi_chu);
    void set_tien_phat(int Tien_phat);

    long long get_id() const;
    long long get_book_id() const;
    string get_book_name() const;
    long long get_book_copy_id() const;
    long long get_user_id() const;
    string get_user_name() const;
    my_time get_ngay_dat() const;
    my_time get_ngay_muon() const;
    my_time get_ngay_phai_tra() const;
    my_time get_ngay_tra() const;
    StatusType get_status() const;
    TinhTrangsach get_tinh_trang_sach() const;
    string get_tinh_trang_sach_string() const;
    int get_lan_gia_han() const;
    string get_status_string() const;
    string get_ghi_chu() const;
    int get_tien_phat() const;

    // Relations
    bool fetch_book(book& out) const;
    bool fetch_copy(Book_copies& out) const;
    bool fetch_user(Account& out) const;
};

#endif // BORROW_H
