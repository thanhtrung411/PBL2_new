#include "book.h"


book::book()
{
    name_book="";
    author="";
    category="";
    publisher="";
    year="";
    quantity="";
    state="";
    id_book="";
    link_image="";
    link_pdf="";
}
book::book(string name_book, string author, string category, string publisher, string year, string quantity, string state,string id_book,string link_image,string link_pdf,string don_gia,string page_number)
{   
    this->name_book=name_book;
    this->author=author;
    this->category=category;
    this->publisher=publisher;
    this->year=year;
    this->quantity=quantity;
    this->state=state;
    this->id_book=id_book;
    this->link_image=link_image;
    this->link_pdf=link_pdf;
    this->don_gia=don_gia;
    this->page_number=page_number;
}
book::~book()
{
}
void book::set_name_book(string name_book)
{
    this->name_book=name_book;
}
void book::set_author(string author)
{
    this->author=author;
}
void book::set_category(string category)
{
    this->category=category;
}
void book::set_publisher(string publisher)
{
    this->publisher=publisher;
}
void book::set_year(string year)
{
    this->year=year;
}
void book::set_quantity(string quantity)
{
    this->quantity=quantity;
}
void book::set_state(string state)
{
    this->state=state;
}
void book::set_id_book(string id_book)
{
    this->id_book=id_book;
}
void book::set_link_image(string link_image)
{
    this->link_image=link_image;
}
void book::set_link_pdf(string link_pdf)
{
    this->link_pdf=link_pdf;
}
void book::set_don_gia(string don_gia)
{
    this->don_gia=don_gia;
}
void book::set_page_number(string page_number)
{
    this->page_number=page_number;
}
void book::set_book(string name_book, string author, string category, string publisher, string year, string quantity, string state,string id_book,string link_image,string link_pdf,string don_gia,string page_number)
{
    this->name_book=name_book;
    this->author=author;
    this->category=category;
    this->publisher=publisher;
    this->year=year;
    this->quantity=quantity;
    this->state=state;
    this->id_book=id_book;
    this->link_image=link_image;
    this->link_pdf=link_pdf;
    this->don_gia=don_gia;
    this->page_number=page_number;
}
void book::set_book(book &b)
{
    this->name_book=b.name_book;
    this->author=b.author;
    this->category=b.category;
    this->publisher=b.publisher;
    this->year=b.year;
    this->quantity=b.quantity;
    this->state=b.state;
    this->id_book=b.id_book;
    this->link_image=b.link_image;
    this->link_pdf=b.link_pdf;
    this->don_gia=b.don_gia;
    this->page_number=b.page_number;
}
string book::get_id_book()
{
    return id_book;
}
string book::get_link_image()
{
    return link_image;
}
string book::get_link_pdf()
{
    return link_pdf;
}
string book::get_name_book()
{
    return name_book;
}
string book::get_author()
{
    return author;
}
string book::get_category()
{
    return category;
}
string book::get_publisher()
{
    return publisher;
}
string book::get_year()
{
    return year;
}
string book::get_quantity()
{
    return quantity;
}
string book::get_state()
{
    return state;
}
string book::get_don_gia()
{
    return don_gia;
}
string book::get_page_number()
{
    return page_number;
}
string book::get_book()
{
    return name_book + ", " + author + ", " + category + ", " + publisher + ", " + year + ", " + quantity + ", " + state + ", " + id_book + ", " + link_image + ", " + link_pdf + ", " + don_gia + ", " + page_number;
}

description book::get_description() {
    return desc;
}
void book::set_description(const description& d) {
    desc = d;
}

