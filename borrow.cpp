#include "borrow.h"
#include <iostream>
#include "my_string.h"
using namespace std;
string borrow::get_borrow_id() const{
    return id;
}
string borrow::get_id_book() const{
    return id_book;
}
string borrow::get_id_user() const{
    return id_user;
}
string borrow::get_id_admin() const{
    return id_admin;
}
string borrow::get_booking_date() const{
    return booking_date;
}
string borrow::get_borrow_date() const{
    return borrow_date;
}
string borrow::get_pay_date() const{
    return pay_date;
}
string borrow::get_status() const{
    return status;
}
string borrow::get_return_date() const{
    return return_date;
}
string borrow::get_tien_phat() const{
    return tien_phat;
}
borrow::borrow(){
    id = "";
    id_book = "";
    id_user = "";
    id_admin = "NULL";
    booking_date = "NULL";
    borrow_date = "NULL";
    pay_date = "NULL";
    status = "NULL";
    return_date = "NULL";
    tien_phat = "0";
}
borrow::borrow(const string& borrow_id_, const string& id_book_, const string& id_user_, const string& id_admin_, const string& booking_date_, const string& borrow_date_, const string& pay_date_, const string& status_, const string& return_date_, const string& tien_phat_){
    id = borrow_id_;
    id_book = id_book_;
    id_user = id_user_;
    id_admin = id_admin_;
    booking_date = booking_date_;
    borrow_date = borrow_date_;
    pay_date = pay_date_;
    status = status_;
    return_date = return_date_;
    tien_phat = tien_phat_;
}
void borrow::set_borrow_id(const string& borrow_id_){
    id = borrow_id_;
}
void borrow::set_id_book(const string& id_book_){
    id_book = id_book_;
}
void borrow::set_id_user(const string& id_user_){
    id_user = id_user_;
}
void borrow::set_id_admin(const string& id_admin_){
    id_admin = id_admin_;
}
void borrow::set_booking_date(const string& booking_date_){
    booking_date = booking_date_;
}
void borrow::set_borrow_date(const string& borrow_date_){
    borrow_date = borrow_date_;
}
void borrow::set_pay_date(const string& pay_date_){
    pay_date = pay_date_;
}
void borrow::set_status(const string& status_){
    status = status_;
}
void borrow::set_return_date(const string& return_date_){
    return_date = return_date_;
}
void borrow::set_tien_phat(const string& tien_phat_){
    tien_phat = tien_phat_;
}
