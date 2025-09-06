#include "dang_ky_dialog.h"
#include "ui_dang_ky_dialog.h"

dang_ky_dialog::dang_ky_dialog(QWidget *parent)
    : QMainWindow(parent)
    , ui_2(new Ui::dang_ky_dialog)
{
    ui_2->setupUi(this);
    ui_2->return_home->setIcon(QIcon(":/icons/icons_/home.png"));

}

dang_ky_dialog::~dang_ky_dialog()
{
    delete ui_2;
}

