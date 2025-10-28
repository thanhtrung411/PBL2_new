#ifndef BORROW_H
#define BORROW_H
#include <iostream>
#include "my_time.h"
#include "my_string.h"
using namespace std;

class borrow{
private:
    long long ID;
    long long Book_copy_id;
    long long User_id;
    long long Admin_id;
    my_time Booking_date;
    my_time Borrow_date;
    my_time Due_date;
    my_time Return_date;
    string Status;
    int Tien_phat;
public:
    borrow();
    borrow(long long ID, const long long& Book_copy_id, const long long& User_id, const long long& Admin_id,
           const my_time& Booking_date, const my_time& Borrow_date, const my_time& Due_date, const my_time& Return_date,
           const string& Status, int Tien_phat);
    ~borrow();

    void set_id(long long ID);
    void set_book_copy_id(const long long& Book_copy_id);
    void set_id_user(const long long& User_id);
    void set_id_admin(const long long& Admin_id);
    void set_booking_date(const my_time& Booking_date);
    void set_borrow_date(const my_time& Borrow_date);
    void set_due_date(const my_time& Due_date);
    void set_return_date(const my_time& Return_date);
    void set_status(const string& Status);
    void set_tien_phat(int Tien_phat);

    long long get_id() const;
    long long get_book_copy_id() const;
    long long get_id_user() const;
    long long get_id_admin() const;
    my_time get_booking_date() const;
    my_time get_borrow_date() const;
    my_time get_due_date() const;
    my_time get_return_date() const;
    string get_status() const;
    int get_tien_phat() const;
};

#endif // BORROW_H
