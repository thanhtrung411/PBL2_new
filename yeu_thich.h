#ifndef YEU_THICH_H
#define YEU_THICH_H
#include "my_time.h"
#include <QDir>
#include <QFileInfo>
#include <QCoreApplication>

class yeu_thich
{
private:
    my_time date_favorited;
    long long book_id;
    long long user_id;
    QString getDataFilePath(string link);
public:
    yeu_thich();
    yeu_thich(long long book_id, long long user_id, const my_time& date_favorited);
    ~yeu_thich();
    void set_book_id(long long book_id);
    void set_user_id(long long user_id);
    void set_date_favorited(const my_time& date_favorited);
    long long get_book_id() const;
    long long get_user_id() const;
    my_time get_date_favorited() const;

};
#endif // YEU_THICH_H
