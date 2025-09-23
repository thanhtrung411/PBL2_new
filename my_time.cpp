#include "my_time.h"
#include <iostream>
#include <QDate>
using namespace std;
 int  month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
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
my_time operator + (const my_time&t1, int ngay){
        my_time rest = t1;
        // int  month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        while(ngay > 0){
            month[2]=(rest.nam % 400 == 0 || rest.nam % 4 == 0 && rest.nam %100 != 0 ) ? 29 : 28;
        int daysInMonth = month[rest.thang];
        
        int remain = daysInMonth - rest.ngay;

        if(ngay <= remain){
            rest.ngay+= ngay;
            ngay=0;
        }else{
            ngay-=(remain + 1);
            rest.ngay=1;
            rest.thang++;
            if(rest.thang > 12){
                rest.thang=1;
                rest.nam++;
            }
        }
    }
    return rest;
    }
my_time my_time :: extend_date(const my_time &t1,int ngay){
    return t1+ngay;
}
int my_time :: diff(const my_time &t1,const my_time&t2){
    int ngays=0;
    my_time temp=t1;
    if(t2.nam < t1.nam || t1.nam == t2.nam && t2.thang < t1.thang || t1.nam == t2.nam && t1.thang == t2.thang && t2.ngay < t1.ngay){
        return ngays;
    }
    while(temp.ngay != t2.ngay && temp.thang != t2.thang && temp.nam != t2.nam){
        ngays++;
        temp.ngay++;
        if(temp.ngay > month [temp.thang] || temp.nam % 4 == 0 && temp.thang == 2 && temp.ngay > 29 ){
            temp.ngay=1;
            temp.thang++;

        }
        if(temp.thang > 12){
                temp.thang=1;
                temp.nam++;
            }
    }
    return ngays;
}

// void my_time :: set_time_muon(int ngay,int thang,int nam){
//     month[2]=(nam % 400 == 0 || nam % 4 == 0 && nam %100 != 0 ) ? 29 : 28;
//     if(ngay < month[thang] && thang <=12 && nam > 0){
//         this->ngay=ngay;
//         this->thang=thang;
//         this->nam=nam;
//     }else{
//         cout<<"Ngay muon khong hop le";
//     }
// }
bool my_time :: is_leap_year(int year) const{
    return (year % 400 == 0 || year % 4 == 0 && year % 100 != 0) ? 1 : 0;
}
bool my_time :: is_valid_day(int ngay,int thang , int nam_) const{
    if(ngay <1 || nam <1 || thang <1 || thang >12) return false;
    if(is_leap_year(9)){
        if(ngay > 29) return false;
    }else if( ngay > month[thang] ) return false;
    return true;
}

my_time my_time :: set_ngay_muon(int days){
    my_time ngay_muon;
    ngay_muon.set_time_now();
    ngay_muon = ngay_muon + days;
    return ngay_muon;
}
my_time my_time :: ngay_tra(int days){
    my_time ngay_muon;
    ngay_muon.set_ngay_muon(6);
    my_time ngay_tra = ngay_muon + days;
    return ngay_tra;
}
my_time& my_time :: operator = (const my_time &t){
    if(this != &t ){
        this->ngay = t.ngay;
        this->thang = t.thang;
        this->nam = t.nam;
    }
    return *this;
}
