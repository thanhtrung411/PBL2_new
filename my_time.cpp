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
    my_time temp1=t1;
    my_time temp2=t2;
    if(temp2.nam < temp1.nam || temp1.nam == temp2.nam && temp2.thang < temp1.thang || temp1.nam == temp2.nam && temp1.thang == temp2.thang && temp2.ngay < temp1.ngay){
        return ngays;
    }
    while(temp1.ngay != temp2.ngay && temp1.thang != temp2.thang && temp1.nam != temp2.nam){
        ngays++;
        temp1.ngay++;
        if(temp1.ngay > month [temp1.thang] || temp1.nam % 4 == 0 && temp1.thang == 2 && temp1.ngay > 29 ){
            temp1.ngay=1;
            temp1.thang++;

        }
        if(temp1.thang > 12){
                temp1.thang=1;
                temp1.nam++;
            }
    }
    return ngays;
}

my_time operator ++(const my_time&t){
    return t+1;
}
long long my_time::operator-(const my_time &d)
{
    my_time x;
    x.ngay=ngay;
    x.thang=thang;
    x.nam=nam;
    long long a=x.ngay;
    do{
        switch(x.thang)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            a+=31;
            x.thang--;
            if(x.thang==0)
            {
                x.nam--;
                x.thang=12;
            }
            break;
        case 4: case 6: case 9: case 11:
            a+=30;
            x.thang--;
            break;
        case 2:
            if(x.nam%400==0 || (x.nam%4==0 && x.nam%100!=0))
            {
                a+=29;
                x.thang--;
            }
            else
            {
                a+=28;
                x.thang--;
            }
        }
    }while(x.nam>0);

    x.ngay=d.ngay;
    x.thang=d.thang;
    x.nam=d.nam;
    long long b=x.ngay;
    do{
        switch(x.thang)
        {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            b+=31;
            x.thang--;
            if(x.thang==0)
            {
                x.nam--;
                x.thang=12;
            }
            break;
        case 4: case 6: case 9: case 11:
            b+=30;
            x.thang--;
            break;
        case 2:
            if(x.nam%400==0 || (x.nam%4==0 && x.nam%100!=0))
            {
                b+=29;
                x.thang--;
            }
            else
            {
                b+=28;
                x.thang--;
            }
        }
    }while(x.nam>0);
    return a-b;
}
void my_time :: set_time_muon(int ngay,int thang,int nam){
    month[2]=(nam % 400 == 0 || nam % 4 == 0 && nam %100 != 0 ) ? 29 : 28;
    if(ngay < month[thang] && thang <=12 && nam > 0){
        this->ngay=ngay;
        this->thang=thang;
        this->nam=nam;
    }else{
        cout<<"Ngay muon khong hop le"
    }
}
bool my_time :: is_leap_year(int year){
    return (year % 400 == 0 || year % 4 == 0 && year % 100 != 0) ? 1 : 0;
}
bool my_time :: is_valid_day(int ngay,int thang , int nam) const{
    if(ngay <1 || nam <1 || thang <1 || thang >12) return false;
    if(is_leap_year(nam)){
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
    my_time ngay_tra = ngay_muon + days;
    return ngay_tra;
}
my_time& my_time :: operator = (const my_time &t){
    if(*this != t ){
        this->ngay = t.ngay;
        this->thang = t.thang;
        this->nam = t.nam;
    }
    return *this;
}
