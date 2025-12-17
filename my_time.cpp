#include "my_time.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>

using namespace std;

// --- CÁC HÀM HỖ TRỢ (HELPER FUNCTIONS) ---

bool kiem_tra_nam_nhuan(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int get_days_in_month(int year, int month) {
    static const int days_per_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2) {
        return kiem_tra_nam_nhuan(year) ? 29 : 28;
    }
    if (month >= 1 && month <= 12) {
        return days_per_month[month];
    }
    return 0;
}

// --- CONSTRUCTOR & DESTRUCTOR ---

my_time::my_time() : year(1970), month(1), day(1), hour(0), minute(0), second(0) {}

my_time::my_time(int y, int mo, int d, int h, int mi, int s)
    : year(y), month(mo), day(d), hour(h), minute(mi), second(s) {}

my_time::my_time(string date) {
    set_time_date(date);
}

my_time::~my_time() {}

// --- SETTERS ---

void my_time::set_time(int y, int mo, int d, int h, int mi, int s) {
    year = y; month = mo; day = d;
    hour = h; minute = mi; second = s;
}

void my_time::set_time_date(const string& date) {
    // Định dạng dd/MM/yyyy
    sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
    hour = 0; minute = 0; second = 0;
}

void my_time::set_time_datetime(const string& datetime) {
    // Định dạng dd/MM/yyyy HH:mm:ss
    sscanf(datetime.c_str(), "%d/%d/%d %d:%d:%d", &day, &month, &year, &hour, &minute, &second);
}

void my_time::set_year(int y) { year = y; }
void my_time::set_month(int mo) { month = mo; }
void my_time::set_day(int d) { day = d; }
void my_time::set_hour(int h) { hour = h; }
void my_time::set_minute(int mi) { minute = mi; }
void my_time::set_second(int s) { second = s; }

// --- GETTERS ---

int my_time::get_year() const { return year; }
int my_time::get_month() const { return month; }
int my_time::get_day() const { return day; }
int my_time::get_hour() const { return hour; }
int my_time::get_minute() const { return minute; }
int my_time::get_second() const { return second; }

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

// --- STATIC METHODS ---

my_time my_time::now() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return my_time(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
                   now->tm_hour, now->tm_min, now->tm_sec);
}

// --- LOGIC TÍNH TOÁN ---

// Hàm này giữ lại để dùng cho phép trừ (operator-)
long long my_time::day_to_seconds() const {
    long long total_days = 0;
    for (int y = 1970; y < year; ++y) {
        total_days += kiem_tra_nam_nhuan(y) ? 366 : 365;
    }
    
    for (int m = 1; m < month; ++m) {
        total_days += get_days_in_month(year, m);
    }
    total_days += day - 1;

    return total_days * 86400LL + hour * 3600LL + minute * 60LL + second;
}

my_time my_time::add_time(const my_time& t) const {
    my_time result = *this;
    // Cộng giây
    result.second += t.second;
    result.minute += t.minute + result.second / 60;
    result.second %= 60;

    // Cộng phút
    result.hour += t.hour + result.minute / 60;
    result.minute %= 60;

    // Cộng giờ
    result.day += t.day + result.hour / 24;
    result.hour %= 24;

    // Cộng ngày tháng năm
    result.month += t.month;
    result.year += t.year;

    // Chuẩn hóa ngày (xử lý tràn ngày trong tháng)
    while (result.day > get_days_in_month(result.year, result.month)) {
        result.day -= get_days_in_month(result.year, result.month);
        result.month++;
        if (result.month > 12) {
            result.month = 1;
            result.year++;
        }
    }
    return result;
}

my_time my_time::operator+(const my_time& t) const {
    return add_time(t);
}

my_time my_time::operator-(const my_time& t) const {
    long long seconds1 = this->day_to_seconds();
    long long seconds2 = t.day_to_seconds();
    long long diff = seconds1 - seconds2;

    // Logic chuyển lại từ giây sang my_time (giữ nguyên logic cũ của ông)
    my_time result;
    result.second = diff % 60; diff /= 60;
    result.minute = diff % 60; diff /= 60;
    result.hour = diff % 24; diff /= 24;

    int y = 1970;
    while (true) {
        int days_in_year = kiem_tra_nam_nhuan(y) ? 366 : 365;
        if (diff >= days_in_year) {
            diff -= days_in_year;
            y++;
        } else break;
    }
    result.year = y;

    int m = 1;
    while (true) {
        int days_in_month = get_days_in_month(result.year, m);
        if (diff >= days_in_month) {
            diff -= days_in_month;
            m++;
        } else break;
    }
    result.month = m;
    result.day = diff + 1;

    return result;
}

my_time my_time::operator+(int days_to_add) const {
    my_time t1 = *this;
    for (int i = 0; i < days_to_add; ++i) {
        int days_in_current_month = get_days_in_month(t1.year, t1.month);
        t1.day++;
        if (t1.day > days_in_current_month) {
            t1.day = 1;
            t1.month++;
            if (t1.month > 12) {
                t1.month = 1;
                t1.year++;
            }
        }
    }
    return t1;
}

my_time my_time::extend_date(int day) const {
    return *this + day;
}

my_time& my_time::operator=(const my_time& t) {
    if (this != &t) {
        year = t.year; month = t.month; day = t.day;
        hour = t.hour; minute = t.minute; second = t.second;
    }
    return *this;
}

// --- QUAN TRỌNG: OPERATORS SO SÁNH ĐÃ ĐƯỢC TỐI ƯU ---
// So sánh theo thứ tự từ điển (Năm -> Tháng -> Ngày...) thay vì quy đổi giây

bool my_time::operator<(const my_time& t) const {
    if (year != t.year) return year < t.year;
    if (month != t.month) return month < t.month;
    if (day != t.day) return day < t.day;
    if (hour != t.hour) return hour < t.hour;
    if (minute != t.minute) return minute < t.minute;
    return second < t.second;
}

bool my_time::operator==(const my_time& t) const {
    return (year == t.year) && (month == t.month) && (day == t.day) &&
           (hour == t.hour) && (minute == t.minute) && (second == t.second);
}

// Các operator còn lại dựa trên < và ==
bool my_time::operator!=(const my_time& t) const {
    return !(*this == t);
}

bool my_time::operator<=(const my_time& t) const {
    return (*this < t) || (*this == t);
}

bool my_time::operator>(const my_time& t) const {
    return !(*this <= t);
}

bool my_time::operator>=(const my_time& t) const {
    return !(*this < t);
}

// Helper function bên ngoài
bool diff(const my_time &t1, const my_time &t2){
    return t1 != t2;
}

int return_day_in_month(int year, int month);