#ifndef TIME_H
#define TIME_H
#include <iostream>
using namespace std;

class time
{
    private:
        int ngay;
        int thang;
        int nam;
    public:
        time();
        time(int ngay, int thang, int nam);
        ~time();
        void set_ngay(int ngay);
        void set_thang(int thang);
        void set_nam(int nam);
        void set_time(int ngay, int thang, int nam);
        int get_ngay();
        int get_thang();
        int get_nam();
        string get_time();
};
        




#endif // TIME_H