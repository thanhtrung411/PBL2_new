#ifndef DANG_KY_DIALOG_H
#define DANG_KY_DIALOG_H

#include <QMainWindow>
#include "accout.h"
namespace Ui {
class dang_ky_dialog;
}

class dang_ky_dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit dang_ky_dialog(QWidget *parent = nullptr);
    ~dang_ky_dialog();

private slots:
    void on_dang_ky_2_button_clicked();

    void on_return_home_clicked();

    void on_sign_in_button_clicked();

    void on_sign_up_button_clicked();

    void on_dang_nhap_button_clicked();

    void on_dang_ky_button_clicked();

    void on_forget_button_clicked();

    void on_forget_button_2_clicked();

    void on_dang_ky_2_button_2_clicked();

    void on_ten_dang_nhap_2_input_textChanged(const QString &arg1);

    void on_email_2_input_textEdited(const QString &arg1);

    void on_so_dien_thoai_2_input_textEdited(const QString &arg1);

    void on_so_dien_thoai_2_input_textChanged(const QString &arg1);

    void on_lay_lai_mat_khau_button_clicked();

private:
    Ui::dang_ky_dialog *ui_2;
signals:
    void registered(const accout& user);
    void returned();
};

#endif // DANG_KY_DIALOG_H
