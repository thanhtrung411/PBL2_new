#include "my_time.h"
#include <iostream>
#include <QDate>
using namespace std;
my_time::my_time()
{
    ngay=1;
    thang=1;
    nam=2000;
}
my_time::my_time(int ngay, int thang, int nam)
{
    this->ngay=ngay;
    this->thang=thang;
    this->nam=nam;
}
my_time::~my_time()
{
}
void my_time::set_ngay(int ngay)
{
    this->ngay=ngay;
}
void my_time::set_thang(int thang)
{
    this->thang=thang;
}
void my_time::set_nam(int nam)
{
    this->nam=nam;
}
void my_time::set_time(int ngay, int thang, int nam)
{
    this->ngay=ngay;
    this->thang=thang;
    this->nam=nam;
}
int my_time::get_ngay()
{
    return ngay;
}
int my_time::get_thang()
{
    return thang;
}
int my_time::get_nam()
{
    return nam;
}
string my_time::get_time()
{
    return to_string(ngay)+"/"+to_string(thang)+"/"+to_string(nam);
}
void my_time::set_time_now(){
    QDate today = QDate::currentDate();
    ngay = today.day();
    thang = today.month();
    nam = today.year();
}
