#include "pbl2.h"
#include "./ui_pbl2.h"
#include "admin_show.h"
#include "ui_admin_show.h"
#include "card.h"
pbl2::pbl2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pbl2)
{
    ui->setupUi(this);
    auto actSearch = ui->search_input->addAction(
        QIcon(":/icons/icons_/search.png"),QLineEdit::LeadingPosition);
    ui->search_input->setTextMargins(6, 0, 28, 0);
    ui->info->setCurrentIndex(0);
    set_up_card();
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

void pbl2::set_up_card(){
    auto gridHost = new QWidget(this);
    ui->sach_moi_layout_2->setContentsMargins(0,0,0,0);
    ui->sach_moi_layout_2->setHorizontalSpacing(5);
    ui->sach_moi_layout_2->setVerticalSpacing(5);

    const int k = 4;
    for (int i = 0; i < k ; i++){
        auto card = new ProductCard(":/images/images_/book.png", "C++ Programming Language");
        ui->sach_moi_layout_2->addWidget(card, 0, i);
    }
    //setCentralWidget(gridHost);
}

