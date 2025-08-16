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

private:
    Ui::dang_ky_dialog *ui;
};

#endif // DANG_KY_DIALOG_H
