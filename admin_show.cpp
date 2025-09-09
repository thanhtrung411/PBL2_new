#include "admin_show.h"
#include "ui_admin_show.h"

admin_show::admin_show(QWidget *parent)
    : QMainWindow(parent)
    , ui_3(new Ui::admin_show)
{
    ui_3->setupUi(this);
}

admin_show::~admin_show()
{
    delete ui_3;
}
