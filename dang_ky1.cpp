#include "dang_ky1.h"
#include "ui_dang_ky1.h"

dang_ky1::dang_ky1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dang_ky1)
{
    ui->setupUi(this);
}

dang_ky1::~dang_ky1()
{
    delete ui;
}
