#ifndef DANG_KY_DIALOG_H
#define DANG_KY_DIALOG_H

#include <QMainWindow>

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

private:
    Ui::dang_ky_dialog *ui_2;
};

#endif // DANG_KY_DIALOG_H
