#include "yeu_thich.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

yeu_thich::yeu_thich() {
    book_id = 0;
    user_id = 0;
    date_favorited = my_time();
}
yeu_thich::yeu_thich(long long book_id, long long user_id, const my_time& date_favorited) {
    this->book_id = book_id;
    this->user_id = user_id;
    this->date_favorited = date_favorited;
}
yeu_thich::~yeu_thich() {}
void yeu_thich::set_book_id(long long book_id) {
    this->book_id = book_id;
}
void yeu_thich::set_user_id(long long user_id) {
    this->user_id = user_id;
}
void yeu_thich::set_date_favorited(const my_time& date_favorited) {
    this->date_favorited = date_favorited;
}
long long yeu_thich::get_book_id() const {
    return book_id;
}
long long yeu_thich::get_user_id() const {
    return user_id;
}
my_time yeu_thich::get_date_favorited() const {
    return date_favorited;
}

