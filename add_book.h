#ifndef ADD_BOOK_H
#define ADD_BOOK_H
#include "tree.h"
#include <QMainWindow>

namespace Ui {
class add_book;
}

class add_book : public QMainWindow
{
    Q_OBJECT

public:
    BST_Book book_add;
    book book_chinh_sua;
    int STT = 0;
    explicit add_book(QWidget *parent = nullptr);
    void set_up_file_mode();
    void set_up_chinh_sua_mode(book b);
    ~add_book();

private slots:
    void on_the_loai_sach_input_activated(int index);
    void on_them_button_clicked();
    void on_chuyen_nganh_input_textActivated(const QString &arg1);
    void on_the_loai_sach_input_textActivated(const QString &arg1);
    void on_link_png_button_clicked();
    void on_link_pdf_button_clicked();


    void on_file_mau_csv_clicked();

    void on_nhap_file_clicked();

    void on_xoa_button_clicked();

private:
    Ui::add_book *ui_3;

    bool is_file_mode = false;
    bool is_chinh_sua_mode = false;

    void set_ID_book();

    void set_the_loai_chuyen_nganh();

    void hien_thi_sach_theo_file(book b);

    void return_null_all();

};

#endif // ADD_BOOK_H
