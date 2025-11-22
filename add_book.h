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

private slots:
    void on_the_loai_sach_input_activated(int index);
    void on_them_button_clicked();
    void on_chuyen_nganh_input_textActivated(const QString &arg1);
    void on_the_loai_sach_input_textActivated(const QString &arg1);
    void on_link_png_button_clicked();
    void on_link_pdf_button_clicked();


private:
    Ui::add_book *ui_3;

    void set_ID_book();

    void set_the_loai_chuyen_nganh();

    void return_null_all();

};

#endif // ADD_BOOK_H
