#include"TIME.H"

time::time()
{
    ngay=0;
    thang=0;
    nam=0;
}
time::time(int ngay, int thang, int nam)
{
    this->ngay=ngay;
    this->thang=thang;
    this->nam=nam;
}
time::~time()
{
}
void time::set_ngay(int ngay)
{
    this->ngay=ngay;
}
void time::set_thang(int thang)
{
    this->thang=thang;
}
void time::set_nam(int nam)
{
    this->nam=nam;
}
void time::set_time(int ngay, int thang, int nam)
{
    this->ngay=ngay;
    this->thang=thang;
    this->nam=nam;
}
int time::get_ngay()
{
    return ngay;
}
int time::get_thang()
{
    return thang;
}
int time::get_nam()
{
    return nam;
}
string time::get_time()
{
    return to_string(ngay)+"/"+to_string(thang)+"/"+to_string(nam);
}