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
};



#endif // MY_TIME_H
