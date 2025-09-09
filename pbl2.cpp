#include "pbl2.h"
#include "./ui_pbl2.h"
#include "admin_show.h"
#include "ui_admin_show.h"
pbl2::pbl2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pbl2)
{
    ui->setupUi(this);
    auto actSearch = ui->search_input->addAction(
        QIcon(":/icons/icons_/search.png"),QLineEdit::LeadingPosition);
    ui->search_input->setTextMargins(6, 0, 28, 0);
    ui->info->setCurrentIndex(0);
    ui->vung_hien_thi->setCurrentIndex(0);
}

pbl2::~pbl2()
{
    delete ui;
}

void pbl2::sign_in() {
    ui->info->setCurrentIndex(1);
}

void pbl2::on_quyen_quan_tri_clicked()
{
    auto win = new admin_show(this);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
}

