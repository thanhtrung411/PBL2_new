#include "borrow.h"
#include <iostream>
#include "my_string.h"
using namespace std;
borrow::borrow(){
    ID = 0;
    Book_copy_id = 0;
    User_id = 0;
    Admin_id = 0;
    Booking_date = my_time();
    Borrow_date = my_time();
    Due_date = my_time();
    Return_date = my_time();
    Status = "NULL";
    Tien_phat = 0;
}
borrow::borrow(long long ID, const long long& Book_copy_id, const long long& User_id, const long long& Admin_id,
               const my_time& Booking_date, const my_time& Borrow_date, const my_time& Due_date, const my_time& Return_date,
               const string& Status, int Tien_phat){
    this->ID = ID;
    this->Book_copy_id = Book_copy_id;
    this->User_id = User_id;
    this->Admin_id = Admin_id;
    this->Booking_date = Booking_date;
    this->Borrow_date = Borrow_date;
    this->Due_date = Due_date;
    this->Return_date = Return_date;
    this->Status = Status;
    this->Tien_phat = Tien_phat;
}
borrow::~borrow(){}

void borrow::set_id(long long ID){
    this->ID = ID;
}
void borrow::set_book_copy_id(const long long& Book_copy_id){
    this->Book_copy_id = Book_copy_id;
}
void borrow::set_id_user(const long long& User_id){
    this->User_id = User_id;
}
void borrow::set_id_admin(const long long& Admin_id){
    this->Admin_id = Admin_id;
}
void borrow::set_booking_date(const my_time& Booking_date){
    this->Booking_date = Booking_date;
}
void borrow::set_borrow_date(const my_time& Borrow_date){
    this->Borrow_date = Borrow_date;
}
void borrow::set_due_date(const my_time& Due_date){
    this->Due_date = Due_date;
}
void borrow::set_return_date(const my_time& Return_date){
    this->Return_date = Return_date;
}
void borrow::set_status(const string& Status){
    this->Status = Status;
}
void borrow::set_tien_phat(int Tien_phat){
    this->Tien_phat = Tien_phat;
}
long long borrow::get_id() const{
    return ID;
}

long long borrow::get_book_copy_id() const{
    return Book_copy_id;
}
long long borrow::get_id_user() const{
    return User_id;
}
long long borrow::get_id_admin() const{
    return Admin_id;
}
my_time borrow::get_booking_date() const{
    return Booking_date;
}
my_time borrow::get_borrow_date() const{
    return Borrow_date;
}
my_time borrow::get_due_date() const{
    return Due_date;
}
my_time borrow::get_return_date() const{
    return Return_date;
}
string borrow::get_status() const{
    return Status;
}
int borrow::get_tien_phat() const{
    return Tien_phat;
}
