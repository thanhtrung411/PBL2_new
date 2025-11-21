#ifndef ACCOUT_H
#define ACCOUT_H
#include <iostream>
#include "my_time.h"
using namespace std;

class accout{
private:
    int ID;
    string ten_dang_nhap;
    string ten_tai_khoan;
    int gioi_tinh;
    my_time ngay_sinh;
    string email;
    int doi_tuong;
    string phone_number;
    string pass;
    string level;
    int score;
    my_time date_created;
public:
    accout(int ID,string ten_dang_nhap,string ten_tai_khoan, int gioi_tinh,my_time ngay_sinh,string email,int doi_tuong, string phone_number,string pass,string level,int score,my_time date_created){
        this->ID = ID;
        this->ten_dang_nhap=ten_dang_nhap;
        this->ten_tai_khoan=ten_tai_khoan;
        this->gioi_tinh=gioi_tinh;
        this->ngay_sinh=ngay_sinh;
        this->email=email;
        this->doi_tuong=doi_tuong;
        this->phone_number=phone_number;
        this->pass=pass;
        this->level=level;
        this->score=score;
        this->date_created=date_created;
    };
    accout() {}
    ~accout() {}
    void ma_hoa_();
    void giai_ma_();
    void set_ID(int ID){
        this->ID = ID;
    };
    int get_ID() const{
        return ID;
    };
    void set_ten_dang_nhap(string ten_dang_nhap){
        this->ten_dang_nhap = ten_dang_nhap;
    };
    string get_ten_dang_nhap() const{
        return ten_dang_nhap;
    };
    void set_ten_tai_khoan(string ten_tai_khoan){
        this->ten_tai_khoan = ten_tai_khoan;
    };
    string get_ten_tai_khoan() const{
        return ten_tai_khoan;
    };
    void set_gioi_tinh(int gioi_tinh){
        this->gioi_tinh = gioi_tinh;
    };
    int get_gioi_tinh() const{
        return gioi_tinh;
    };
    void set_ngay_sinh(my_time ngay_sinh){
        this->ngay_sinh = ngay_sinh;
    };
    my_time get_ngay_sinh() const{
        return ngay_sinh;
    };
    void set_email(string email){
        this->email = email;
    };
    string get_email() const{
        return email;
    };
    void set_doi_tuong(int doi_tuong){
        this->doi_tuong = doi_tuong;
    };
    int get_doi_tuong() const{
        return doi_tuong;
    };
    void set_phone_number(string phone_number){
        this->phone_number = phone_number;
    };
    string get_phone_number() const{
        return phone_number;
    };
    void set_pass(string pass){
        this->pass = pass;
    };
    string get_pass() const{
        return pass;
    };
    void set_level(string level){
        this->level = level;
    };
    string get_level() const{
        return level;
    };
    void set_score(int score){
        this->score = score;
    };
    int get_score() const{
        return score;
    };
    void set_date_created(my_time date_created){
        this->date_created = date_created;
    };
    my_time get_date_created() const{
        return date_created;
    };
    int max_book_borrow();
};

#endif // ACCOUT_H
