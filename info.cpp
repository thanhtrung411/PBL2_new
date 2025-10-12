#include "info.h"
#include "ui_info.h"

info::info(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::info)
{
    ui->setupUi(this);
}

info::~info()
{
    delete ui;
}
