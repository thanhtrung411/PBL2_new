#ifndef MY_TIME_H
#define MY_TIME_H

#include <iostream>
using namespace std;

class my_time
{
private:
    int ngay;
    int thang;
    int nam;
public:
    my_time();
    my_time(int ngay, int thang, int nam);
    ~my_time();
    void set_ngay(int ngay);
    void set_thang(int thang);
    void set_nam(int nam);
    void set_time(int ngay, int thang, int nam);
    int get_ngay();
    int get_thang();
    int get_nam();
    string get_time();
    void set_time_now();
    friend my_time operator + (const my_time&t1, int ngay);
    friend my_time operator ++ (const my_time&t);
    my_time extend_date(const my_time &t1, int ngay);
    int diff(const my_time& t1,const my_time &t2);
    long long my_time::operator-(const my_time &d);
    bool is_leap_year(int year);
    bool is_valid_day(int day,int thang, int nam) const;
    my_time set_ngay_muon(int days);
    my_time ngay_tra(int days = 30 );
    my_time& operator = (const my_time &t);
};





#endif // MY_TIME_H
