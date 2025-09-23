#include "pbl2.h"
#include "./ui_pbl2.h"
#include "admin_show.h"
#include "ui_admin_show.h"
#include "card.h"
#include "global.h"
#include <QDir>
pbl2::pbl2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pbl2)
{
    ui->setupUi(this);
    auto actSearch = ui->search_input->addAction(
        QIcon(":/icons/icons_/search.png"),QLineEdit::LeadingPosition);
    ui->search_input->setTextMargins(6, 0, 28, 0);
    ui->info->setCurrentIndex(0);
    set_up_card(book_data,ui->sach_moi_layout_2);
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

void pbl2::set_scroll(QScrollArea* p, int width){

}

void pbl2::set_up_card(BST_Book& b,QGridLayout* path_link){
    path_link->setContentsMargins(0,0,0,0);
    path_link->setHorizontalSpacing(5);
    path_link->setVerticalSpacing(5);
    const int k = 8;
    qDebug() << QDir::currentPath();

    for (int i = 0; i < k ; i++){
        auto card = new ProductCard(b[i]);
        path_link->addWidget(card, 0, i);
        connect(card, &ProductCard::clicked, this, [](book set_book){
        qDebug() << "Bạn đã bấm card số" << set_book.get_id_book().c_str();
        });
    }
    //setCentralWidget(gridHost);
}

