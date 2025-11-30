#ifndef LIBRARY_H
#define LIBRARY_H


#include "tree.h"
#include "book.h"
#include "book_copies.h"
#include "author.h"
#include "the_loai_chuyen_nganh.h"
#include "borrow.h"
#include "accout.h"

using namespace std;

class Library {
private:
    BST<book, long long> books;
    BST<Book_copies, long long> book_copies;
    BST<Author, int> authors;
    BST<Chuyen_nganh, int> chuyen_nganhs;
    BST<The_loai, int> the_loais;
    BST<borrow, long long> borrows;
    BST<accout, int> accouts;
public:
    Library();
    ~Library();
    bool add_book(const book& b);
    bool add_author(const Author& a);
    bool add_accout(const accout& a);
    bool add_book_copy(const Book_copies& bc);
    bool add_chuyen_nganh(const Chuyen_nganh& cn);
    bool add_the_loai(const The_loai& tl);
    bool add_borrow(const borrow& br);

    bool remove_book(long long book_id);
    bool remove_author(int author_id);
    bool remove_accout(int id);
    bool remove_book_copy(long long book_copy_id);
    bool remove_chuyen_nganh(int chuyen_nganh_id);
    bool remove_the_loai(int the_loai_id);
    bool remove_borrow(long long borrow_id);

    int get_total_books() const;
    int get_total_authors() const;
    int get_total_accouts() const;
    int get_total_book_copies() const;
    int get_total_chuyen_nganhs() const;
    int get_total_the_loais() const;
    int get_total_borrows() const;

    void sort_books_by_name(BST_Book& books_data, BST_Book_by_Name books_sorted, int asc = 1);
    void sort_books_by_author(BST_Book& books_data, BST_Book_by_Author books_sorted, int asc = 1);
    void sort_books_by_the_loai(BST_Book& books_data, BST_Book books_sorted, int asc = 1);
    void sort_books_by_chuyen_nganh(BST_Book& books_data, BST_Book_by_Chuyen_Nganh books_sorted, int asc = 1);

    // BST<Book_copies, long long>& copies_of_book(long long book_id);
    // BST<Author, int>& authors_of_book(long long book_id);
    // BST<Chuyen_nganh, int>& chuyen_nganhs_of_book(long long book_id);
    // BST<The_loai, int>& the_loais_of_book(long long book_id);
    // BST<borrow, long long>& borrows_of_book(long long book_id);

    int dat_sach(long long id_book_, int id_user_, my_time booking_date, int limit_borrow, int score_user);
};

#endif // LIBRARY_H