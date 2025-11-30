#include "pbl2.h"
#include "./ui_pbl2.h"
#include "admin_show.h"
#include "info.h"
#include "library.h"
#include "ui_admin_show.h"
#include "dang_ky_dialog.h"
#include "card.h"
#include "card_muon.h"
#include "global.h"
#include "history.h"
#include "my_file.h"
#include "my_string.h"
#include "the_loai_chuyen_nganh.h"
#include "settings_file.h"
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
#include <chrono>

Library lib;
history his;

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
template<typename Tree>
void pbl2::Reload(Tree &book_data_){
    clear_layout(ui->sach_moi_layout_2);
    clear_layout(ui->sach_goi_y_layout);
    set_up_card_moi(book_data_,ui->sach_moi_layout_2);
    set_up_card_goi_y(book_data_,ui->sach_goi_y_layout);
}

pbl2::pbl2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pbl2)
{
    ui->setupUi(this);
    
    random_seed = std::chrono::system_clock::now().time_since_epoch().count();
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
    ui->dang_tim_kiem_layout->setVisible(false);
    ui->trich_dan_tom_tat_stack->setCurrentIndex(0);
    //ui->dang_nhap_button->setIcon(QIcon(":/icons/icons_/user-interface.png"));
    set_up(book_data);
    connect(ui->muon_button, &QPushButton::clicked, this, [this](){
        if (current_selected_book.get_ID() == 0) return;
        qDebug() << "Muon sach " << current_selected_book.get_ID();
        switch (lib.dat_sach(current_selected_book.get_ID(), acc_sign_in.get_ID(), my_time::now(), current_selected_book.get_limit_borrow(), acc_sign_in.get_score())){
            case 0:
                his.log_action(acc_sign_in.get_ten_dang_nhap(),ActionType::RESERVE_BOOK , current_selected_book.get_ID(),"");
                box_thong_bao("Đặt sách thành công! Vui lòng đến thư viện trong vòng 3 ngày để mượn sách.");
                break;
            case 1:
                box_thong_bao("Lỗi đặt sách. Vui lòng thử lại sau.\nKhông tìm thấy sách");
                break;
            case 2:
                box_thong_bao("Tài khoản không hợp lệ, có thể bạn đã bị khóa.");
                break;
            case 3:
                box_thong_bao("Bạn đã đặt quá số lượng sách cho phép.");
                break;
            case 4:
                box_thong_bao("Toàn bộ sách đã được đặt/mượn.");
                break;
            case 5:
                box_thong_bao("Bạn đã đặt/mượn cuốn sách này rồi.");
                break;
            case 6:
                box_thong_bao("Bạn đang có sách quá hạn chưa trả !\nVui lòng trả sách trước khi đặt sách mới.");
                break;
            default:
                break;
        }
    });

    connect(ui->doc_onliine_button, &QPushButton::clicked, this, [this](){
        if (current_selected_book.get_ID() == 0) return;
        if (is_sign_in) his.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::READ_ONLINE, current_selected_book.get_ID(), "");
        qDebug() << "Doc online " << current_selected_book.get_ID();
    });

    connect(ui->download_button, &QPushButton::clicked, this, [this](){
        if (current_selected_book.get_ID() == 0) return;
        if (is_sign_in) his.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::DOWNLOAD_BOOK, current_selected_book.get_ID(), "");
        qDebug() << "Download " << current_selected_book.get_ID();
    });

    connect(ui->return_home_button, &QPushButton::clicked, this, [this](){
        ui->noi_dung_layout->setCurrentIndex(0);
        QLayoutItem *child;
        // while ((child = ui->muon_sach_layout->takeAt(0)) != nullptr) {
        //     if (child->widget()) {
        //         child->widget()->deleteLater();
        //     }
        //     delete child;
        // }

        current_selected_book = book();
    });
}

pbl2::~pbl2()
{
    delete ui;
}

void pbl2::set_up(BST_Book& book_data_){
    //setup page the loai
    the_loai_data.traverse_ascending([this](The_loai &a){
        ui->the_loai_list_layout->addItem(QString::fromStdString(a.get_name()));
        ui->the_loai_find_layout->addItem(QString::fromStdString(a.get_name()));
    });
    //setup page chuyen nganh
    chuyen_nganh_data.traverse_ascending([this](Chuyen_nganh &a){
        ui->chuyen_nganh_list_layout->addItem(QString::fromStdString(a.get_name()));
    });
    //setup page sach moi
    BST_Book_by_DateCreated_10 date_created_book_data;
    book_data_.traverse_ascending([&date_created_book_data](book &a){
        date_created_book_data.insert(a);
    });
    set_up_card_moi(date_created_book_data,ui->sach_moi_layout_2);
    //setup page sach goi y
    set_up_card_goi_y(book_data_,ui->sach_goi_y_layout);
    //setup_sach_doc_nhieu_nhat
    //setup sach muon nhieu nhat
    long long id_doc_nhieu_nhat = -1;
    int so_luot_xem_max = -1;
    long long id_muon_nhieu_nhat = -1;
    int so_luot_muon_max = -1;
    book_data_.traverse_ascending([&](book &a){
        if (a.get_luot_xem() > so_luot_xem_max){
            so_luot_xem_max = a.get_luot_xem();
            id_doc_nhieu_nhat = a.get_ID();
        }
        if (a.get_luot_muon() > so_luot_muon_max){
            so_luot_muon_max = a.get_luot_muon();
            id_muon_nhieu_nhat = a.get_ID();
        }
    });
    if (id_muon_nhieu_nhat != -1){
        book b;
        if (book_data_.find(id_muon_nhieu_nhat, b)){
            // ui->yeu_thich_name->setText(QString::fromStdString(b.get_Name()));
            // ui->yeu_thich_author->setText(QString::fromStdString(b.get_Author()));
            // ui->yeu_thich_luot_Xem->setText(QString::number(b.get_luot_xem()));
            // ui->yeu_thich_back->setFixedSize(225, 250);
            // ui->yeu_thich_back->setAlignment(Qt::AlignCenter);
            // QString imgPath =QString::fromUtf8(b.get_Link_png().c_str());
            // ui->yeu_thich_back->setPixmap(loadScaled(imgPath, ui->yeu_thich_back->size()));
        }
    }
    if (id_doc_nhieu_nhat != -1){
        book b;
        if (book_data_.find(id_doc_nhieu_nhat, b)){
            // ui->doc_nhieu_name->setText(QString::fromStdString(b.get_Name()));
            // ui->doc_nhieu_author->setText(QString::fromStdString(b.get_Author()));
            // ui->doc_nhieu_so_luong->setText(QString::number(b.get_luot_xem()));
            // ui->doc_nhieu_back->setFixedSize(225, 250);
            // ui->doc_nhieu_back->setAlignment(Qt::AlignCenter);
            // QString imgPath =QString::fromUtf8(b.get_Link_png().c_str());
            // ui->doc_nhieu_back->setPixmap(loadScaled(imgPath, ui->doc_nhieu_back->size()));
        }
    }
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
            borrow_data.info_user(acc_sign_in.get_ID(), borrow_user_data);
            QString name_ = QString::fromStdString(acc_sign_in.get_ten_tai_khoan());
            Reload(book_data);
            
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
    p->setWidgetResizable(true);
    QWidget* container = new QWidget;
    p->setWidget(container);
    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(10);
    container->setMinimumWidth(width);
}

template<typename Tree>
void pbl2::set_up_card_moi(Tree &b,QGridLayout* path_link){
    //path_link->setContentsMargins(0,0,0,0);
    path_link->setHorizontalSpacing(10);
    path_link->setVerticalSpacing(0);
    const int k = settings_file::getInstance()->get_so_sach_moi();
    qDebug() << QDir::currentPath();

    int n = b.count_data();
    int show = std::min(k, n);
    if (!show) return;
    ui->scroll_moi->setMinimumWidth( 15 + (180 + 12) * show);
    b.traverse_ascending([this, &show, &path_link](book &a){
        if (show == 0) return;
        auto card = new ProductCard(a);
        static int i = 0;
        path_link->addWidget(card, 0, i++);
        connect(card, &ProductCard::clicked, this, [this](book bk){
            page_previous = 0;
            if (is_sign_in) his.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::VIEW_BOOK, bk.get_ID(), "");
            show_info_sach(bk);
        });
        --show;
    });
    //setCentralWidget(gridHost);
}

template void pbl2::set_up_card_moi<BST_Book>(BST_Book &b, QGridLayout* path_link);
template void pbl2::set_up_card_moi<BST_Book_by_DateCreated_10>(BST_Book_by_DateCreated_10 &b, QGridLayout* path_link);
template void pbl2::set_up_card_moi<BST_Book_by_Name>(BST_Book_by_Name &b, QGridLayout* path_link);
template void pbl2::set_up_card_moi<BST_Book_by_Author>(BST_Book_by_Author &b, QGridLayout* path_link);
template void pbl2::set_up_card_moi<BST_Book_by_Chuyen_Nganh>(BST_Book_by_Chuyen_Nganh &b, QGridLayout* path_link);
template void pbl2::set_up_card_moi<BST_Book_by_The_loai>(BST_Book_by_The_loai &b, QGridLayout* path_link);

template<typename Tree>
void pbl2::set_up_card_goi_y(Tree &b,QGridLayout* path_link){
    //path_link->setContentsMargins(0,0,0,0);
    path_link->setHorizontalSpacing(10);
    path_link->setVerticalSpacing(0);
    const int k = settings_file::getInstance()->get_so_sach_goi_y();
    qDebug() << QDir::currentPath();

    int n = b.count_data();
    int show = std::min(k, n);
    if (!show) return;
    std::set<int> random_indices;
    ui->scroll_goi_y->setMinimumWidth( 15 + (180 + 12) * show);
    while (random_indices.size() < show) {
        unsigned int rand_index = get_next_random(random_seed) % n;
        random_indices.insert(rand_index);
    }
    int i = 0;
    for (int index : random_indices) {
        auto card = new ProductCard(b[index]);
        path_link->addWidget(card, 0, i++);
        connect(card, &ProductCard::clicked, this, [this](book bk){
            page_previous = 0;
            if (is_sign_in) his.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::VIEW_BOOK, bk.get_ID(), "");
            show_info_sach(bk);
        });
    }
    //setCentralWidget(gridHost);
}

void pbl2::clear_layout(QLayout* layout) {
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }
}

void pbl2::Reload_show_info(book& b){
    qDebug() << is_sign_in << "\nis sign in \n";
    // auto* canh_bao_label = new QLabel("Vui lòng đăng nhập để mượn sách !", this);
    // canh_bao_label->setFixedSize(999,32);
    // canh_bao_label->setStyleSheet(R"(
    // background-color: rgb(170, 0, 0);
    // color: rgb(255, 255, 255);
    // )");
    // //ui->muon_sach_layout->addWidget(canh_bao_label);
    // canh_bao_label->setVisible(false);
    // if (!is_sign_in){
    //     canh_bao_label->setVisible(true);
    // }
    // else{
    //     canh_bao_label->setVisible(false);
    // }
    connect(ui->return_home_button, &QPushButton::clicked, this, [this, b](){
        ui->noi_dung_layout->setCurrentIndex(0);
        QLayoutItem *child;
        // while ((child = ui->muon_sach_layout->takeAt(0)) != nullptr) {
        //     if (child->widget()) {
        //         child->widget()->deleteLater();
        //     }
        //     delete child;
        // }
    });
}

void pbl2::show_info_sach(book& b){
    current_selected_book = b;
    ui->muon_button->setIcon(QIcon(":/icons/icons_/borrow.png"));
    ui->doc_onliine_button->setIcon(QIcon(":/icons/icons_/read.png"));
    ui->download_button->setIcon(QIcon(":/icons/icons_/download.png"));
    ui->noi_dung_layout->setCurrentIndex(1);
    ui->TEN_SACH->setText(b.get_Name().c_str());
    ui->TAC_GIA->setText(b.get_Author().c_str());
    ui->NHA_XUAT_BAN->setText(b.get_NXB().c_str());
    ui->NAM_XUAT_BAN->setText(to_string_(b.get_NamXB()).c_str());
    ui->CHUYEN_NGANH->setText(b.get_Chuyen_nganh_name().c_str());
    ui->THE_LOAI->setText(b.get_The_loai_name().c_str());
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
    //202501100001
    //
    qDebug() << is_sign_in << "\nis sign in \n";
    // auto* canh_bao_label = new QLabel("Vui lòng đăng nhập để mượn sách !", this);
    // canh_bao_label->setFixedSize(999,32);
    // canh_bao_label->setStyleSheet(R"(
    // background-color: rgb(170, 0, 0);
    // color: rgb(255, 255, 255);
    // )");
    // // ui->muon_sach_layout->addWidget(canh_bao_label);
    // canh_bao_label->setVisible(false);
    // if (!is_sign_in){
    //     canh_bao_label->setVisible(true);
    // }
    // else{
    //     canh_bao_label->setVisible(false);
    // }
    connect(ui->return_home_button, &QPushButton::clicked, this, [this, b](){
        ui->noi_dung_layout->setCurrentIndex(page_previous);
        QLayoutItem *child;
        // while ((child = ui->muon_sach_layout->takeAt(0)) != nullptr) {
        //     if (child->widget()) {
        //         child->widget()->deleteLater();
        //     }
        //     delete child;
        // }
        current_selected_book = book();
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


void pbl2::on_the_loai_list_layout_currentIndexChanged(int index)
{
    int id_the_loai = index;
    qDebug() << "The loai index changed to " << id_the_loai;
    if (id_the_loai == 0){
        Reload(book_data);
        return;
    }
    BST_Book book_the_loai;
    book_data.the_loai_of_book(id_the_loai, book_the_loai);
    Reload(book_the_loai);
}


void pbl2::on_chuyen_nganh_list_layout_currentIndexChanged(int index)
{
    int id_chuyen_nganh = index ;
    qDebug() << "Chuyen nganh index changed to " << id_chuyen_nganh;
    if (id_chuyen_nganh == 0){
        Reload(book_data);
        return;
    }
    BST_Book book_chuyen_nganh;
    book_data.chuyen_nganh_of_book(id_chuyen_nganh, book_chuyen_nganh);
    Reload(book_chuyen_nganh);
}


void pbl2::on_tim_kiem_button_clicked()
{
    ui->dang_tim_kiem_layout->setVisible(true);
    QLayoutItem *child;
    while ((child = ui->tim_kiem_grid->takeAt(0)) != nullptr) {
        if (child->widget()) child->widget()->deleteLater();
        delete child;
    }

    string key = ui->search_input->text().toStdString();
    int type_the_loai = ui->the_loai_find_layout->currentIndex();
    int type_tim_kiem = ui->tim_kiem_find_layout->currentIndex();
    int truong_tim_kiem = ui->truong_find_layout->currentIndex();

    BST_Book ket_qua;
    book_data.search(type_the_loai, type_tim_kiem, truong_tim_kiem, key, book_data, ket_qua);

    QGridLayout *path_link = ui->tim_kiem_grid;

    path_link->setSpacing(10);

    path_link->setContentsMargins(10, 10, 10, 10);


    int i = 0;
    const int MAX_COL = 5;

    ket_qua.traverse_ascending([this, path_link, &i, MAX_COL](book &a){
        auto card = new ProductCard(a);
        int row = i / MAX_COL;
        int col = i % MAX_COL;
        path_link->addWidget(card, row, col, Qt::AlignTop | Qt::AlignLeft);

        connect(card, &ProductCard::clicked, this, [this](book bk){
            page_previous = 2;
            if (is_sign_in) his.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::VIEW_BOOK, bk.get_ID(), "");
            show_info_sach(bk);
        });

        i++;
    });

    int next_row = (i / MAX_COL) + 1;
    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    path_link->addItem(verticalSpacer, next_row, 0);
    QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    path_link->addItem(horizontalSpacer, 0, MAX_COL);
    path_link->setRowStretch(next_row, 1);
    path_link->setColumnStretch(MAX_COL, 1);
    ui->dang_tim_kiem_layout->setVisible(false);
    ui->noi_dung_layout->setCurrentIndex(2);
}
