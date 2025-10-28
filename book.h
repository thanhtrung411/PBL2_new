#ifndef BOOK_H
#define BOOK_H
#include "description.h"
#include "my_time.h"
#include <iostream>

using namespace std;
class book {
private:
    long long ID;
    string Name;
    string Author;
    string NXB;
    string NamXB;
    int So_trang;
    string ISBN;
    string Language;
    string Tom_tat;
    string Link_png;
    string Link_pdf;
    int The_loai_ID;
    int Chuyen_nganh_ID;
    bool is_Read_online;
    bool is_Download;
    bool is_Borrow;
    int limit_borrow;
    int luot_xem;
    int luot_muon;
    int luot_tai;
    my_time Date_created;
    string Created_by;
public:
    book();
    book(long long ID, string Name, string Author, string NXB, string NamXB, int So_trang, string ISBN, string Language, string Tom_tat, string Link_png, string Link_pdf, int The_loai_ID, int Chuyen_nganh_ID, bool is_Read_online, bool is_Download, bool is_Borrow, int limit_borrow, int luot_xem, int luot_muon, int luot_tai, my_time Date_created, string Created_by);
    ~book();
    void set_ID(long long ID);
    void set_Name(string Name);
    void set_Author(string Author);
    void set_NXB(string NXB);
    void set_NamXB(string NamXB);
    void set_So_trang(int So_trang);
    void set_ISBN(string ISBN);
    void set_Language(string Language);
    void set_Tom_tat(string Tom_tat);
    void set_Link_png(string Link_png);
    void set_Link_pdf(string Link_pdf);
    void set_The_loai_ID(int The_loai_ID);
    void set_Chuyen_nganh_ID(int Chuyen_nganh_ID);
    void set_is_Read_online(bool is_Read_online);
    void set_is_Download(bool is_Download);
    void set_is_Borrow(bool is_Borrow);
    void set_limit_borrow(int limit_borrow);
    void set_luot_xem(int luot_xem);
    void set_luot_muon(int luot_muon);
    void set_luot_tai(int luot_tai);
    void set_Date_created(my_time Date_created);
    void set_Created_by(string Created_by);

    long long get_ID() const;
    string get_Name() const;
    string get_Author() const;
    string get_NXB() const;
    string get_NamXB() const;
    int get_So_trang() const;
    string get_ISBN() const;
    string get_Language() const;
    string get_Tom_tat() const;
    string get_Link_png() const;
    string get_Link_pdf() const;
    int get_The_loai_ID() const;
    int get_Chuyen_nganh_ID() const;
    bool get_is_Read_online() const;
    bool get_is_Download() const;
    bool get_is_Borrow() const;
    int get_limit_borrow() const;
    int get_luot_xem() const;
    int get_luot_muon() const;
    int get_luot_tai() const;
    my_time get_Date_created() const;
    string get_Created_by() const;
};

#endif // BOOK_H
