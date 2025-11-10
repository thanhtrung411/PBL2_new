#include "library.h"
#include <iostream>

Library::Library() :
    books(KeyGetters::getBookID),
    book_copies(KeyGetters::getBookCopiesID),
    authors(KeyGetters::getAuthorID),
    chuyen_nganhs(KeyGetters::getChuyenNganhID),
    the_loais(KeyGetters::getTheLoaiID),
    borrows(KeyGetters::getBorrowID),
    accouts(KeyGetters::getAccoutID) {}

Library::~Library() {}

bool Library::add_book(const book& b) {
    return books.insert(b);
}
bool Library::add_author(const Author& a) {
    return authors.insert(a);
}
bool Library::add_accout(const accout& a) {
    return accouts.insert(a);
}
bool Library::add_book_copy(const Book_copies& bc) {
    return book_copies.insert(bc);
}
bool Library::add_chuyen_nganh(const Chuyen_nganh& cn) {
    return chuyen_nganhs.insert(cn);
}
bool Library::add_the_loai(const The_loai& tl) {
    return the_loais.insert(tl);
}
bool Library::add_borrow(const borrow& br) {
    return borrows.insert(br);
}
bool Library::remove_book(long long book_id) {
    return books.remove_by_Key(book_id);
}
bool Library::remove_author(int author_id) {
    return authors.remove_by_Key(author_id);
}
bool Library::remove_accout(int id) {
    return accouts.remove_by_Key(id);
}
bool Library::remove_book_copy(long long book_copy_id) {
    return book_copies.remove_by_Key(book_copy_id);
}
bool Library::remove_chuyen_nganh(int chuyen_nganh_id) {
    return chuyen_nganhs.remove_by_Key(chuyen_nganh_id);
}
bool Library::remove_the_loai(int the_loai_id) {
    return the_loais.remove_by_Key(the_loai_id);
    return false;
}
bool Library::remove_borrow(long long borrow_id) {
    return borrows.remove_by_Key(borrow_id);
}
int Library::get_total_books() const {
    return books.count_data();
}
int Library::get_total_authors() const {
    return authors.count_data();
}
int Library::get_total_accouts() const {
    return accouts.count_data();
}
int Library::get_total_book_copies() const {
    return book_copies.count_data();
}
int Library::get_total_chuyen_nganhs() const {
    return chuyen_nganhs.count_data();
}
int Library::get_total_the_loais() const {
    return the_loais.count_data();
}
int Library::get_total_borrows() const {
    return borrows.count_data();
}
