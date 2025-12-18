#ifndef ADD_BOOK_COPY_H
#define ADD_BOOK_COPY_H

#include <QMainWindow>
#include "tree.h"

namespace Ui {
class add_book_copy;
}

class add_book_copy : public QMainWindow
{
    Q_OBJECT

public:
    explicit add_book_copy(QWidget *parent = nullptr);
    ~add_book_copy();
    void set_up();

private slots:
    void on_so_ban_sao_valueChanged(int arg1);

    void on_ten_dau_sach_activated(int index);

    void on_them_button_clicked();

private:
    Ui::add_book_copy *ui;
    BST_book_copy bc;
};

#endif // ADD_BOOK_COPY_H
