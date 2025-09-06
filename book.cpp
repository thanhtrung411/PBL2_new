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
book::book(string name_book, string author, string category, string publisher, string year, string quantity, string state,string id_book,string link_image,string link_pdf )
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


