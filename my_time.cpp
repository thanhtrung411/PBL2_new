#include "my_time.h"
#include <iostream>
<<<<<<< HEAD
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
=======
using namespace std;

int days_per_month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

bool kiem_tra_nam_nhuan(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        days_per_month[2] = 29;
        return true;
    } else {
        days_per_month[2] = 28;
        return false;
    }
}

my_time::my_time() : year(1970), month(1), day(1), hour(0), minute(0), second(0) {}
my_time::my_time(int y, int mo, int d, int h, int mi, int s)
    : year(y), month(mo), day(d), hour(h), minute(mi), second(s) {}
my_time::my_time(string date) {
    set_time_date(date);
}
my_time::~my_time() {}
void my_time::set_time(int y, int mo, int d, int h, int mi, int s) {
    year = y;
    month = mo;
    day = d;
    hour = h;
    minute = mi;
    second = s;
}
void my_time::set_time_date(const string& date) {
    sscanf(date.c_str(), "%d/%d/%d", &year, &month, &day);
    hour = 0;
    minute = 0;
    second = 0;
}
void my_time::set_time_datetime(const string& datetime) {
    sscanf(datetime.c_str(), "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
}
string my_time::get_time() const {
    char buffer[9];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hour, minute, second);
    return string(buffer);
}
string my_time::get_date() const {
    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d", day, month, year);
    return string(buffer);
}
string my_time::get_datetime() const {
    return get_date() + " " + get_time();
}
void my_time::set_year(int y) { year = y; }
void my_time::set_month(int mo) { month = mo; }
void my_time::set_day(int d) { day = d; }
void my_time::set_hour(int h) { hour = h; }
void my_time::set_minute(int mi) { minute = mi; }
void my_time::set_second(int s) { second = s; }
int my_time::get_year() const { return year; }
int my_time::get_month() const { return month; }
int my_time::get_day() const { return day; }
int my_time::get_hour() const { return hour; }
int my_time::get_minute() const { return minute; }
int my_time::get_second() const { return second; }

my_time my_time::add_time(const my_time& t) const {
    my_time result = *this;
    result.second += t.second;
    result.minute += t.minute + result.second / 60;
    result.hour += t.hour + result.minute / 60;
    result.day += t.day + result.hour / 24;
    result.month += t.month;
    result.year += t.year;

    result.second %= 60;
    result.minute %= 60;
    result.hour %= 24;

    while (true) {
        kiem_tra_nam_nhuan(result.year);
        if (result.day > days_per_month[result.month]) {
            result.day -= days_per_month[result.month];
            result.month++;
            if (result.month > 12) {
                result.month = 1;
                result.year++;
            }
        } else {
            break;
        }
    }

    return result;
}
my_time my_time::now() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return my_time(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
                   now->tm_hour, now->tm_min, now->tm_sec);
}
long long my_time::day_to_seconds() const {
    long long total_days = 0;
    for (int y = 1970; y < year; ++y) {
        total_days += kiem_tra_nam_nhuan(y) ? 366 : 365;
    }
    kiem_tra_nam_nhuan(year);
    for (int m = 1; m < month; ++m) {
        total_days += days_per_month[m];
    }
    total_days += day - 1;
    return total_days * 86400 + hour * 3600 + minute * 60 + second;
}
my_time my_time::operator+(const my_time& t) const {
    return add_time(t);
}
my_time my_time::operator-(const my_time& t) const {
    long long seconds1 = this->day_to_seconds();
    long long seconds2 = t.day_to_seconds();
    long long diff = seconds1 - seconds2;

    my_time result;
    result.second = diff % 60;
    diff /= 60;
    result.minute = diff % 60;
    diff /= 60;
    result.hour = diff % 24;
    diff /= 24;

    int y = 1970;
    while (true) {
        int days_in_year = kiem_tra_nam_nhuan(y) ? 366 : 365;
        if (diff >= days_in_year) {
            diff -= days_in_year;
            y++;
        } else {
            break;
        }
    }
    result.year = y;

    kiem_tra_nam_nhuan(result.year);
    int m = 1;
    while (true) {
        if (diff >= days_per_month[m]) {
            diff -= days_per_month[m];
            m++;
        } else {
            break;
        }
    }
    result.month = m;
    result.day = diff + 1;

    return result;
}
bool my_time::operator==(const my_time& t) const {
    return this->day_to_seconds() == t.day_to_seconds();
}
bool my_time::operator!=(const my_time& t) const {
    return !(*this == t);
}
bool my_time::operator<(const my_time& t) const {
    return this->day_to_seconds() < t.day_to_seconds();
}
bool my_time::operator<=(const my_time& t) const {
    return *this < t || *this == t;
}
bool my_time::operator>(const my_time& t) const {
    return !(*this <= t);
}
bool my_time::operator>=(const my_time& t) const {
    return !(*this < t);
}
my_time& my_time::operator=(const my_time& t) {
    if (this != &t) {
        year = t.year;
        month = t.month;
        day = t.day;
        hour = t.hour;
        minute = t.minute;
        second = t.second;
>>>>>>> 8d0139e240f15b69e354092b928091dea7d7134f
    }
    return *this;
}
