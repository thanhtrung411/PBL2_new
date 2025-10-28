#ifndef BOOK_COPIES_H
#define BOOK_COPIES_H
#include <iostream>
using namespace std;

class Book_copies{
private:
    long long ID;
    long long Book_id;
    string Status;
public:
    Book_copies();
    Book_copies(long long ID,long long Book_id, string Status);
    ~Book_copies();
    void set_id(long long id);
    void set_id_book(long long id_book);
    void set_status(string Status);

    long long get_id() const;
    long long get_id_book() const;
    string get_status() const;
};

#endif // BOOK_COPIES_H
