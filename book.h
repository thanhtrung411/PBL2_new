#ifndef BOOK_H
#define BOOK_H
#include "description.h"
#include <iostream>

using namespace std;
class book
{
    private:
        string id_book;
        string ten_sach;
        string tac_gia;
        string the_loai;
        string nha_xuat_ban;
        string nam_xuat_ban;
        string so_trang;
        string ISBN;
        string ngon_ngu;
        string tu_khoa;
        string chuyen_nganh;
        string don_gia;
        string tom_tat;
        string link_png;
        string link_pdf;
        string type_book;
        string tinh_trang;
        string date_created;
        string admin_created;
    public:
        book();
        book(string id_book, string ten_sach, string tac_gia, string the_loai, string nha_xuat_ban, string nam_xuat_ban, string so_trang, string ISBN, string ngon_ngu, string tu_khoa, string chuyen_nganh, string don_gia, string tom_tat, string link_png, string link_pdf, string type_book, string tinh_trang, string date_created, string admin_created);
        ~book();
        void set_id_book(string id_book);
        void set_name_book(string ten_sach);
        void set_tac_gia(string tac_gia);
        void set_the_loai(string the_loai);
        void set_nha_xuat_ban(string nha_xuat_ban);
        void set_nam_xuat_ban(string nam_xuat_ban);
        void set_so_trang(string so_trang);
        void set_ISBN(string ISBN);
        void set_ngon_ngu(string ngon_ngu);
        void set_tu_khoa(string tu_khoa);
        void set_chuyen_nganh(string chuyen_nganh);
        void set_don_gia(string don_gia);
        void set_tom_tat(string tom_tat);
        void set_type_book(string type_book);
        void set_tinh_trang(string tinh_trang);
        void set_link_png(string link_png);
        void set_link_pdf(string link_pdf);
        void set_date_created(string date_created);
        void set_admin_created(string admin_created);
        string get_id_book();
        string get_name_book();
        string get_tac_gia();
        string get_the_loai();
        string get_nha_xuat_ban();
        string get_nam_xuat_ban();
        string get_so_trang();
        string get_ISBN();
        string get_ngon_ngu();
        string get_tu_khoa();
        string get_chuyen_nganh();
        string get_don_gia();
        string get_tom_tat();
        string get_type_book();
        string get_tinh_trang();
        string get_link_png();
        string get_link_pdf();
        string get_date_created();
        string get_admin_created();
        string get_id_book() const;
        string get_name_book() const;
        string get_tac_gia() const;
        string get_the_loai() const;
        string get_nha_xuat_ban() const;
        string get_nam_xuat_ban() const;
        string get_so_trang() const;
        string get_ISBN() const;
        string get_ngon_ngu() const;
        string get_tu_khoa() const;
        string get_chuyen_nganh() const;
        string get_don_gia() const;
        string get_tom_tat() const;
        string get_type_book() const;
        string get_tinh_trang() const;
        string get_link_png() const;
        string get_link_pdf() const;
        string get_date_created() const;
        string get_admin_created() const;

};


#endif // BOOK_H
