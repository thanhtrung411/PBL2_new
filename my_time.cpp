#include "my_time.h"
#include <iostream>
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
    // days_per_month[2] = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
    // if(days_per_month [2] == 29) return true;
    // return false;

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
    }
    return *this;
}
bool diff(const my_time &t1, const my_time &t2){
    if(t1 == t2) return false;
    return true;
}

my_time my_time :: operator+(int day)const{
    my_time t1= *this;
    while(day > 0){
        if(t1.day <= days_per_month[t1.get_month()]){
            t1.day++;
        }else{
            t1.day= 1;
            t1.month++;
            if(t1.month == 12){
                t1.month = 1;
                t1.year++;
            }
        }
    }
    return t1;
}
my_time my_time :: extend_date(int day)const{
    my_time t= *this;
    return t+day;
}
