#include "show.h"
#include "ui_show.h"

show::show(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::show)
{
    ui->setupUi(this);
}

show::~show()
{
    delete ui;
}
