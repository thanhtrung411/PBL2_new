#include "pbl2.h"
#include "./ui_pbl2.h"
#include "admin_show.h"
#include "info.h"
#include "ui_admin_show.h"
#include "dang_ky_dialog.h"
#include "card.h"
#include "card_muon.h"
#include "global.h"
#include "my_file.h"
#include "my_string.h"
#include "the_loai_chuyen_nganh.h"
#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QStyle>
#include <QMouseEvent>
#include <QEvent>
#include <QCursor>
#include <QPainter>
#include <QPainterPath>
#include <QLabel>
#include <QFontMetrics>
#include <iostream>

QPixmap pbl2::loadScaled(const QString& path, const QSize& toSize) const
{
    QPixmap pm(path);
    if (pm.isNull()) {
        // placeholder nếu không tìm thấy ảnh
        QPixmap ph(toSize);
        ph.fill(Qt::lightGray);
        return ph;
    }
    return pm.scaled(toSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void pbl2::Reload(){
    set_up_card(book_data,ui->sach_moi_layout_2);
}

pbl2::pbl2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pbl2)
{
    ui->setupUi(this);
    Qt::WindowFlags f = Qt::Window
                        | Qt::WindowTitleHint
                        | Qt::WindowSystemMenuHint
                        | Qt::WindowMinMaxButtonsHint
                        | Qt::WindowCloseButtonHint;
    setWindowFlags(f);
    auto actSearch = ui->search_input->addAction(
        QIcon(":/icons/icons_/search.png"),QLineEdit::LeadingPosition);
    ui->search_input->setTextMargins(6, 0, 28, 0);
    //ui->info->setCurrentIndex(0);
    ui->noi_dung_layout->setCurrentIndex(0);
    ui->trich_dan_tom_tat_stack->setCurrentIndex(0);
    ui->dang_nhap_button->setIcon(QIcon(":/icons/icons_/user-interface.png"));
    set_up_card(book_data,ui->sach_moi_layout_2);
}

pbl2::~pbl2()
{
    delete ui;
}

void pbl2::on_dang_nhap_button_clicked()
{
    if (!is_sign_in){
        auto win = new dang_ky_dialog(this);
        win->setAttribute(Qt::WA_DeleteOnClose, true);
        win->show();
        connect(win, &dang_ky_dialog::registered, this, [this, win](const accout& user) {
            acc_sign_in = user;
            is_sign_in = 1;
            acc_sign_in.giai_ma_();
            QString name_ = QString::fromStdString(acc_sign_in.get_ten_tai_khoan());
            Reload();
            ui->dang_nhap_button->setText(name_);
            this->show();
            this->raise();
            this->activateWindow();
            win->deleteLater();
        });
    }
    else {
        auto win = new info(this);
        win->setAttribute(Qt::WA_DeleteOnClose, true);
        win->show();
        this->hide();

    }
}

void pbl2::sign_in() {
    //ui->info->setCurrentIndex(1);
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
        connect(card, &ProductCard::clicked, this, [this](book set_book){
        qDebug() << "Bạn đã bấm card số" << set_book.get_ID();
            show_info_sach(set_book);
        });
    }
    //setCentralWidget(gridHost);
}

void pbl2::Reload_show_info(book& b){
    for (int i = 0 ; i <= 2 ; i++){
        auto* row = new card_muon(to_string(b.get_ID()),b.get_Name(),"HEHE","  Mượn",this);
        ui->muon_sach_layout->addWidget(row);
    }
    qDebug() << is_sign_in << "\nis sign in \n";
    auto* canh_bao_label = new QLabel("Vui lòng đăng nhập để mượn sách !", this);
    canh_bao_label->setFixedSize(999,32);
    canh_bao_label->setStyleSheet(R"(
    background-color: rgb(170, 0, 0);
    color: rgb(255, 255, 255);
    )");
    ui->muon_sach_layout->addWidget(canh_bao_label);
    canh_bao_label->setVisible(false);
    if (!is_sign_in){
        canh_bao_label->setVisible(true);
    }
    else{
        canh_bao_label->setVisible(false);
    }
    connect(ui->return_home_button, &QPushButton::clicked, this, [this, b](){
        ui->noi_dung_layout->setCurrentIndex(0);
        QLayoutItem *child;
        while ((child = ui->muon_sach_layout->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }
    });
}

void pbl2::show_info_sach(book& b){
    ui->muon_button->setIcon(QIcon(":/icons/icons_/borrow.png"));
    ui->doc_onliine_button->setIcon(QIcon(":/icons/icons_/read.png"));
    ui->download_button->setIcon(QIcon(":/icons/icons_/download.png"));
    ui->noi_dung_layout->setCurrentIndex(1);
    ui->TEN_SACH->setText(b.get_Name().c_str());
    ui->TAC_GIA->setText(b.get_Author().c_str());
    ui->NHA_XUAT_BAN->setText(b.get_NXB().c_str());
    ui->NAM_XUAT_BAN->setText(b.get_NamXB().c_str());
    ui->CHUYEN_NGANH->setText(chuyen_nganh_data.return_name(b.get_Chuyen_nganh_ID()).c_str());
    ui->THE_LOAI->setText(the_loai_data.return_name(b.get_The_loai_ID()).c_str());
    ui->NHAN_DE->setText(b.get_Name().c_str());
    ui->TOM_TAT->setText(b.get_Tom_tat().c_str());
    ui->THONG_TIN_BAN_QUYEN->setText(b.get_NXB().c_str());
    ui->NGON_NGU->setText(b.get_Language().c_str());
    ui->SO_TRANG->setText(to_string(b.get_So_trang()).c_str());
    ui->ISBN->setText(b.get_ISBN().c_str());
    ui->VI_TRI_LUU_TRU->setText(to_string(b.get_ID()).c_str());
    QString png_path = QString::fromUtf8(b.get_Link_png());
    ui->PNG_BOOK->setFixedSize(200, 250);
    ui->PNG_BOOK->setAlignment(Qt::AlignCenter);
    ui->PNG_BOOK->setPixmap(loadScaled(png_path, ui->PNG_BOOK->size()));
    //
    //
    connect(ui->muon_button, &QPushButton::clicked, this, [this,b](){
        qDebug() << "Muon sach " << b.get_ID();
    });
    connect(ui->doc_onliine_button, &QPushButton::clicked, this, [this,b](){
        qDebug() << "Doc online " << b.get_ID();
    });
    connect(ui->download_button, &QPushButton::clicked, this, [this,b](){
        qDebug() << "Download " << b.get_ID();
    });
    BST_Book show_book;
    /*
    string _id_ = lay_n_chu_dau(b.get_ID(),12);
    show_book.find_some_id_book(_id_,book_data);
    qDebug() << show_book.count_book();
    for (int i = 0 ; i < show_book.count_book() ; i++){
        auto* row = new card_muon(show_book[i].get_ID(),show_book[i].get_Name(), "HEEH","  Mượn",this);
        ui->muon_sach_layout->addWidget(row);
    }
    */
    qDebug() << is_sign_in << "\nis sign in \n";
    auto* canh_bao_label = new QLabel("Vui lòng đăng nhập để mượn sách !", this);
    canh_bao_label->setFixedSize(999,32);
    canh_bao_label->setStyleSheet(R"(
    background-color: rgb(170, 0, 0);
    color: rgb(255, 255, 255);
    )");
    ui->muon_sach_layout->addWidget(canh_bao_label);
    canh_bao_label->setVisible(false);
    if (!is_sign_in){
        canh_bao_label->setVisible(true);
    }
    else{
        canh_bao_label->setVisible(false);
    }
    connect(ui->return_home_button, &QPushButton::clicked, this, [this, b](){
        ui->noi_dung_layout->setCurrentIndex(0);
        QLayoutItem *child;
        while ((child = ui->muon_sach_layout->takeAt(0)) != nullptr) {
            if (child->widget()) {
                child->widget()->deleteLater();
            }
            delete child;
        }
    });
}

void pbl2::on_pushButton_clicked()
{
    qDebug() << "Muon sach";
}


void pbl2::on_chi_tiet_button_clicked()
{
    ui->chi_tiet_button->setStyleSheet(R"(
        QPushButton{background-color: rgb(243, 246, 255);
        color: rgb(69, 104, 173);
          border: 2px solid rgb(69, 104, 173);
          border-radius: 4px;
          selection-color: rgb(13, 13, 13);
        }
        QPushButton:hover   { background: #e9ecf5; border-color: #3e5e9c; }
        QPushButton:pressed { background: #d6d8e0; border-color: #37538a; }
        QPushButton:disabled{
          background: #f1f3f9; color: #9aa0a6; border-color: #e0e2eb;
        }
    )");
    ui->trich_dan_button->setStyleSheet(R"(
        QPushButton{background-color: rgb(69, 104, 173);
        color: rgb(243, 246, 255);
          border: 2px solid rgb(69, 104, 173);
          border-radius: 4px;
          selection-color: rgb(13, 13, 13);
        }
        QPushButton:hover   { background: rgb(60, 91, 149); border-color: #3e5e9c; }
        QPushButton:pressed { background: rgb(48, 74, 121); border-color: #37538a; }
        QPushButton:disabled{
          background: #f1f3f9; color: #9aa0a6; border-color: #e0e2eb;
        }
    )");
    ui->trich_dan_tom_tat_stack->setCurrentIndex(0);

}


void pbl2::on_trich_dan_button_clicked()
{
    ui->chi_tiet_button->setStyleSheet(R"(
        QPushButton{background-color: rgb(69, 104, 173);
        color: rgb(243, 246, 255);
          border: 2px solid rgb(69, 104, 173);
          border-radius: 4px;
          selection-color: rgb(13, 13, 13);
        }
        QPushButton:hover   { background: rgb(60, 91, 149); border-color: #3e5e9c; }
        QPushButton:pressed { background: rgb(48, 74, 121); border-color: #37538a; }
        QPushButton:disabled{
          background: #f1f3f9; color: #9aa0a6; border-color: #e0e2eb;
        }
    )");
    ui->trich_dan_button->setStyleSheet(R"(
        QPushButton{background-color: rgb(243, 246, 255);
        color: rgb(69, 104, 173);
          border: 2px solid rgb(69, 104, 173);
          border-radius: 4px;
          selection-color: rgb(13, 13, 13);
        }
        QPushButton:hover   { background: #e9ecf5; border-color: #3e5e9c; }
        QPushButton:pressed { background: #d6d8e0; border-color: #37538a; }
        QPushButton:disabled{
          background: #f1f3f9; color: #9aa0a6; border-color: #e0e2eb;
        }
    )");
    ui->trich_dan_tom_tat_stack->setCurrentIndex(1);
}

