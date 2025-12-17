#ifndef MY_TIME_H
#define MY_TIME_H

#include <iostream>
using namespace std;

class my_time{
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
public:
    my_time();
    my_time(int y, int mo, int d, int h, int mi, int s);
    my_time(string date);
    ~my_time();
    void set_time(int y, int mo, int d, int h, int mi, int s);
    void set_time_date(const string& date);
    void set_time_datetime(const string& datetime);
    string get_time() const;
    string get_date() const;
    string get_datetime() const;

    void set_year(int y);
    void set_month(int mo);
    void set_day(int d);
    void set_hour(int h);
    void set_minute(int mi);
    void set_second(int s);
    int get_year() const;
    int get_month() const;
    int get_day() const;
    int get_hour() const;
    int get_minute() const;
    int get_second() const;
    my_time add_time(const my_time& t) const;
    static my_time now();
    
    long long day_to_seconds() const;
    my_time operator+(const my_time& t) const;
    my_time operator-(const my_time& t) const;
    bool operator==(const my_time& t) const;
    bool operator!=(const my_time& t) const;
    bool operator<(const my_time& t) const;
    bool operator<=(const my_time& t) const;
    bool operator>(const my_time& t) const;
    bool operator>=(const my_time& t) const;
    my_time& operator = (const my_time& t);
    my_time operator+(int day) const;
    my_time extend_date(int day) const;


};

int get_days_in_month(int year, int month);

#endif // MY_TIME_H
