#include "book_copies.h"
#include <iostream>
using namespace std;
Book_copies::Book_copies() {
    ID = 0;
    Book_id = 0;
    Status = "0";
    ghi_chu = "";
}

Book_copies::Book_copies(long long ID,long long Book_id, string Status, string ghi_chu) {
    this->ID = ID;
    this->Book_id = Book_id;
    this->Status = Status;
    this->ghi_chu = ghi_chu;
}

Book_copies::~Book_copies() {}

void Book_copies::set_id(long long id) {
    this->ID = id;
}
void Book_copies::set_id_book(long long id_book) {
    this->Book_id = id_book;
}
void Book_copies::set_status(string Status) {
    this->Status = Status;
}
void Book_copies::set_ghi_chu(string ghi_chu) {
    this->ghi_chu = ghi_chu;
}
long long Book_copies::get_id() const {
    return ID;
}
long long Book_copies::get_id_book() const {
    return Book_id;
}
string Book_copies::get_status() const {
    return Status;
}
string Book_copies::get_ghi_chu() const {
    return ghi_chu;
}
