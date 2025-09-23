#ifndef ADD_BOOK_H
#define ADD_BOOK_H

#include <QMainWindow>

namespace Ui {
class add_book;
}

class add_book : public QMainWindow
{
    Q_OBJECT

public:
    explicit add_book(QWidget *parent = nullptr);
    ~add_book();

private:
    Ui::add_book *ui;
};

#endif // ADD_BOOK_H
