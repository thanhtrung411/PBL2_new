#ifndef BOOK_COPIES_H
#define BOOK_COPIES_H
#include <iostream>
using namespace std;

class Book_copies{
private:
    long long ID;
    long long Book_id;
    string Status;
    string ghi_chu;
public:
    Book_copies();
    Book_copies(long long ID,long long Book_id, string Status, string ghi_chu);
    ~Book_copies();
    void set_id(long long id);
    void set_id_book(long long id_book);
    void set_status(string Status);
    void set_ghi_chu(string ghi_chu);

    long long get_id() const;
    long long get_id_book() const;
    string get_status() const;
    string get_ghi_chu() const;
};

#endif // BOOK_COPIES_H
