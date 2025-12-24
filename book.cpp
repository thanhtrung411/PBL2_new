#include "book.h"
#include "tree.h"
#include "global.h"
#include "library.h"
#include <iostream>
using namespace std;
book::book(){
    ID = 0;
    Name = "";
    Author = "";
    NXB = "";
    NamXB = 1900;
    So_trang = 0;
    ISBN = "NULL";
    Language = "";
    Tom_tat = "";
    Link_png = "NULL";
    Link_pdf = "NULL";
    The_loai_ID = 0;
    Chuyen_nganh_ID = 0;
    is_Read_online = false;
    is_Download = false;
    is_Borrow = false;
    limit_borrow = 0;
    luot_xem = 0;
    luot_muon = 0;
    luot_tai = 0;
    tong_sach = 0;
    tong_sach_dang_muon = 0;
    tong_sach_dang_dat = 0;
    tong_sach_ranh = 0;
    Date_created = my_time();
    Created_by = "NULL";
    do_chinh_xac = 0;
}
book::book(long long ID, string Name, string Author, string NXB, int NamXB, int So_trang, string ISBN, string Language, string Tom_tat, string Link_png, string Link_pdf, int The_loai_ID, int Chuyen_nganh_ID, bool is_Read_online, bool is_Download, bool is_Borrow, int limit_borrow, int luot_xem, int luot_muon, int luot_tai,int tong_sach, int tong_sach_dang_muon, int tong_sach_dang_dat, int tong_sach_ranh, my_time Date_created, string Created_by){
    this->ID = ID;
    this->Name = Name;
    this->Author = Author;
    this->NXB = NXB;
    this->NamXB = NamXB;
    this->So_trang = So_trang;
    this->ISBN = ISBN;
    this->Language = Language;
    this->Tom_tat = Tom_tat;
    this->Link_png = Link_png;
    this->Link_pdf = Link_pdf;
    this ->The_loai_ID = The_loai_ID;
    this ->Chuyen_nganh_ID = Chuyen_nganh_ID;
    this->is_Read_online = is_Read_online;
    this->is_Download = is_Download;
    this->is_Borrow = is_Borrow;
    this->limit_borrow = limit_borrow;
    this->luot_xem = luot_xem;
    this->luot_muon = luot_muon;
    this->luot_tai = luot_tai;
    this->tong_sach = tong_sach;
    this->tong_sach_dang_muon = tong_sach_dang_muon;
    this->tong_sach_dang_dat = tong_sach_dang_dat;
    this->tong_sach_ranh = tong_sach_ranh;
    this->Date_created = Date_created;
    this->Created_by = Created_by;
    this->do_chinh_xac = 0;
}
book::~book(){}
void book::set_ID(long long ID){
    this->ID = ID;
}
void book::set_Name(string Name){
    this->Name = Name;
}
void book::set_Author(string Author){
    this->Author = Author;
}
void book::set_NXB(string NXB){
    this->NXB = NXB;
}
void book::set_NamXB(int NamXB){
    this->NamXB = NamXB;
}
void book::set_So_trang(int So_trang){
    this->So_trang = So_trang;
}
void book::set_ISBN(string ISBN){
    this->ISBN = ISBN;
}
void book::set_Language(string Language){
    this->Language = Language;
}
void book::set_Tom_tat(string Tom_tat){
    this->Tom_tat = Tom_tat;
}
void book::set_Link_png(string Link_png){
    this->Link_png = Link_png;
}
void book::set_Link_pdf(string Link_pdf){
    this->Link_pdf = Link_pdf;
}
// void book::set_The_loai_ID(int The_loai_ID){
//     this->the_loai = lib.get_the_loai_data().get_the_loai_by_id(The_loai_ID);
// }
// void book::set_Chuyen_nganh_ID(int Chuyen_nganh_ID){
//     this->chuyen_nganh = lib.get_chuyen_nganh_data().get_chuyen_nganh_by_id(Chuyen_nganh_ID);
// }
// string book::get_The_loai_name() const{
//     return the_loai.get_name();
// }
// string book::get_Chuyen_nganh_name() const{
//     return chuyen_nganh.get_name();
// }
void book::set_is_Read_online(bool is_Read_online){
    this->is_Read_online = is_Read_online;
}
void book::set_is_Download(bool is_Download){
    this->is_Download = is_Download;
}
void book::set_is_Borrow(bool is_Borrow){
    this->is_Borrow = is_Borrow;
}
void book::set_limit_borrow(int limit_borrow){
    this->limit_borrow = limit_borrow;
}
void book::set_luot_xem(int luot_xem){
    this->luot_xem = luot_xem;
}
void book::set_luot_muon(int luot_muon){
    this->luot_muon = luot_muon;
}
void book::set_luot_tai(int luot_tai){
    this->luot_tai = luot_tai;
}
void book::set_tong_sach(int tong_sach){
    this->tong_sach = tong_sach;
}
void book::set_tong_sach_dang_muon(int tong_sach_dang_muon){
    this->tong_sach_dang_muon = tong_sach_dang_muon;
}
void book::set_tong_sach_dang_dat(int tong_sach_dang_dat){
    this->tong_sach_dang_dat = tong_sach_dang_dat;
}
void book::set_tong_sach_ranh(int tong_sach_ranh){
    this->tong_sach_ranh = tong_sach_ranh;
}
void book::set_Date_created(my_time Date_created){
    this->Date_created = Date_created;
}
void book::set_Created_by(string Created_by){
    this->Created_by = Created_by;
}
void book::set_do_chinh_xac(int dcx){
    this->do_chinh_xac = dcx;
}
void book::set_Chuyen_nganh_ID(int Chuyen_nganh_ID){
    this->Chuyen_nganh_ID = Chuyen_nganh_ID;
}
void book::set_The_loai_ID(int The_loai_ID){
    this->The_loai_ID = The_loai_ID;
}

long long book::get_ID() const{
    return ID;
}
string book::get_Name() const{
    return Name;
}
string book::get_Author() const{
    return Author;
}
string book::get_NXB() const{
    return NXB;
}
int book::get_NamXB() const{
    return NamXB;
}
int book::get_So_trang() const{
    return So_trang;
}
string book::get_ISBN() const{
    return ISBN;
}
string book::get_Language() const{
    return Language;
}
string book::get_Tom_tat() const{
    return Tom_tat;
}
string book::get_Link_png() const{
    return Link_png;
}
string book::get_Link_pdf() const{
    return Link_pdf;
}
int book::get_The_loai_ID() const{
     return The_loai_ID;
}
int book::get_Chuyen_nganh_ID() const{
     return Chuyen_nganh_ID;
 }
string book::get_The_loai_name() const{
    return lib.get_the_loai_data().get_the_loai_by_id(The_loai_ID).get_name();
}
string book::get_Chuyen_nganh_name() const{
    return lib.get_chuyen_nganh_data().get_chuyen_nganh_by_id(Chuyen_nganh_ID).get_name();
}
bool book::get_is_Read_online() const{
    return is_Read_online;
}
bool book::get_is_Download() const{
    return is_Download;
}
bool book::get_is_Borrow() const{
    return is_Borrow;
}
int book::get_limit_borrow() const{
    return limit_borrow;
}
int book::get_luot_xem() const{
    return luot_xem;
}
int book::get_luot_muon() const{
    return luot_muon;
}
int book::get_luot_tai() const{
    return luot_tai;
}
int book::get_tong_sach() const{
    return tong_sach;
}
int book::get_tong_sach_dang_muon() const{
    return tong_sach_dang_muon;
}
int book::get_tong_sach_dang_dat() const{
    return tong_sach_dang_dat;
}
int book::get_tong_sach_ranh() const{
    return tong_sach_ranh;
}
my_time book::get_Date_created() const{
    return Date_created;
}
string book::get_Created_by() const{
    return Created_by;
}
int book::get_do_chinh_xac() const{
    return do_chinh_xac;
}

// Relationship
// bool book::fetch_The_loai(The_loai& out) const{
//     return lib.get_the_loai_data().find(this->the_loai.get_id(), out);
// }
// bool book::fetch_Chuyen_nganh(Chuyen_nganh& out) const{
//     return lib.get_chuyen_nganh_data().find(this->chuyen_nganh.get_id(), out);
// }
// void book::related_copies(BST_book_copy& out) const{
//     out.clear();
//     lib.get_book_copy_data().copies_of_book(this->ID, out);
// }
// void book::related_borrows(BST_Borrow& out) const{
//     out.clear();
//     lib.get_borrow_data().traverse_ascending([&](borrow &br){
//         if (br.get_book_id() == this->ID){
//             out.insert(br);
//         }
//     });
// }
// void book::related_favorites(BST_Yeu_thich& out) const{
//     out.clear();
//     lib.get_yeu_thich_data().traverse_ascending([&](yeu_thich &yt){
//         if (yt.get_book_id() == this->ID){
//             out.insert(yt);
//         }
//     });
// }
