#ifndef BOOK_H
#define BOOK_H
#include "description.h"
#include <iostream>

using namespace std;
class book
{
    private:
        description desc;
        string name_book;//ten sach
        string author;//tac gia
        string category;//the loai sach
        string publisher;// nha xuat ban
        string year;// nam xuat ban
        string quantity;// so luong sach co
        string state;// tinh trang sach (co san-da bi muon)
        string id_book;
        string link_image;// link anh bia sach
        string link_pdf;// link file pdf sach
        string don_gia;
        string page_number;
    public:
        book();
        book(description desc,string name_book, string author, string category, string publisher, string year, string quantity, string state,string id_book,string link_image,string link_pdf,string don_gia,string page_number);
        ~book();
        void set_name_book(string name_book);
        void set_author(string author);
        void set_category(string category);
        void set_publisher(string publisher);
        void set_year(string year);
        void set_quantity(string quantity);
        void set_state(string state);
        void set_id_book(string id_book);
        void set_link_image(string link_image);
        void set_link_pdf(string link_pdf);
        void set_don_gia(string don_gia);
        void set_page_number(string page_number);
        void set_book(string name_book, string author, string category, string publisher, string year, string quantity, string state,string id_book,string link_image,string link_pdf,string don_gia,string page_number);
        void set_book(book &b); 
        description get_description();
        void set_description(const description& d);
        string get_id_book();
        string get_link_image();
        string get_link_pdf();
        string get_name_book();
        string get_author();
        string get_category();
        string get_publisher();
        string get_year();
        string get_quantity();
        string get_state();
        string get_don_gia();
        string get_page_number();
        string get_book();


};


#endif // BOOK_H
