#ifndef ADMIN_SHOW_H
#define ADMIN_SHOW_H

#include <QMainWindow>
#include "tree.h"
namespace Ui {
class admin_show;
}

class admin_show : public QMainWindow , BST_Book
{
    Q_OBJECT

public:
    explicit admin_show(QWidget *parent = nullptr);
    ~admin_show();

private slots:
    void on_them_button_clicked();

    void set_ID_book();

    void set_the_loai_chuyen_nganh();

    void on_chuyen_nganh_input_textActivated(const QString &arg1);

    void on_the_loai_sach_input_textActivated(const QString &arg1);

    void on_link_png_button_clicked();

    void on_link_pdf_button_clicked();

private:
    Ui::admin_show *ui_3;
};
#endif // ADMIN_SHOW_H
