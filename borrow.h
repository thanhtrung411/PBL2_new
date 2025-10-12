#ifndef BORROW_H
#define BORROW_H
#include <iostream>
#include "my_string.h"
using namespace std;

class borrow{
private:
    string id;
    string id_book;
    string id_user;
    string id_admin;
    string booking_date;
    string borrow_date;
    string pay_date;
    string status;
    string return_date;
    string tien_phat;
public:
    borrow();
    borrow(const string& id_, const string& id_book_, const string& id_user_, const string& id_admin_, const string& booking_date_, const string& borrow_date_, const string& pay_date_, const string& status_, const string& return_date_, const string& tien_phat_);
    string get_borrow_id() const;
    string get_id_book() const;
    string get_id_user() const;
    string get_id_admin() const;
    string get_booking_date() const;
    string get_borrow_date() const;
    string get_pay_date() const;
    string get_status() const;
    string get_return_date() const;
    string get_tien_phat() const;
    void set_borrow_id(const string& borrow_id_);
    void set_id_book(const string& id_book_);
    void set_id_user(const string& id_user_);
    void set_id_admin(const string& id_admin_);
    void set_booking_date(const string& booking_date_);
    void set_borrow_date(const string& borrow_date_);
    void set_pay_date(const string& pay_date_);
    void set_status(const string& status_);
    void set_return_date(const string& return_date_);
    void set_tien_phat(const string& tien_phat_);
};

#endif // BORROW_H
