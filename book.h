#ifndef BOOK_H
#define BOOK_H
#include <iostream>

using namespace std;
class book
{
    private:
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
    public:
        book();
        book(string name_book, string author, string category, string publisher, string year, string quantity, string state,string id_book,string link_image,string link_pdf );
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

};


#endif // BOOK_H
