#include "iostream"
#include "fstream"
#include "pbl2.h"
#include "./ui_pbl2.h"
#include "dang_ky_dialog.h"
#include "ui_dang_ky_dialog.h"
#include "Account.h"
#include "tree.h"
#include "my_string.h"
#include "my_file.h"
#include "my_time.h"
#include "global.h"
#include "library.h"
#include "history.h"
#include "settings_file.h"
#include <QApplication>
#include <QMessageBox>
#include <QStyleFactory>
using namespace std;

////////////////////////////
Library lib;
BST_History record;
FILE *peoples;
// BST_Account account_data;
// BST_Book book_data;
// BST_book_copy book_copy_data;
// BST_Borrow borrow_data;
// BST_Borrow borrow_user_data;
// BST_The_loai the_loai_data;
// BST_Chuyen_nganh chuyen_nganh_data;
// BST_string string_data;
// BST_History record;
// BST_Yeu_thich yeu_thich_data;
Account acc_sign_in;
int is_sign_in = 0;

////////////////////////////
void box_thong_bao(string s){
    QMessageBox box;
    box.setWindowTitle("Thông báo");
    box.setText(QString::fromStdString(s));
    //box.setIconPixmap(QPixmap(":/icons/icons_/error.png").scaled(16,16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    box.setStyleSheet(R"(
    QMessageBox { background: rgb(243,246,255); }
    QMessageBox QLabel { color:#0868ad; }
    QMessageBox QPushButton {
    background:#fff; color:#0868ad;
    border:1px solid #d0d0d0; border-radius:8px; padding:6px 12px;
    }
    QMessageBox QPushButton:hover  { background:#f5f5f5; }
    QMessageBox QPushButton:default{ border-color:#0078d7; }
    )");
    box.exec();
}

static void applyFusionDark(QApplication& app) {
    app.setStyle(QStyleFactory::create("Fusion"));

    QPalette p;
    p.setColor(QPalette::Window,        QColor(243,246,255));
    p.setColor(QPalette::WindowText,    Qt::white);
    p.setColor(QPalette::Base,          Qt::white);
    //p.setColor(QPalette::AlternateBase, QColor(45,45,48));
    p.setColor(QPalette::Text,          QColor(8, 104, 100));
    p.setColor(QPalette::Button,        QColor(8, 104, 100));
    p.setColor(QPalette::ButtonText,    Qt::white);
    //p.setColor(QPalette::ToolTipBase,   QColor(60,60,60));
    //p.setColor(QPalette::ToolTipText,   Qt::white);
    p.setColor(QPalette::BrightText,    QColor(255,85,85));
    p.setColor(QPalette::Highlight,     QColor(0,120,215));   // “accent” khi chọn/hover
    p.setColor(QPalette::HighlightedText, Qt::white);
    p.setColor(QPalette::PlaceholderText, QColor(255,255,255));
    app.setPalette(p);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    string s = giai_ma_str_("242A2D5C2A0D5F310138654052");

    settings_file::getInstance()->doc_file_settings();




    BST_Book_by_Author author_book_data;
    lib.get_book_data().traverse_ascending([&author_book_data](book &a){
        author_book_data.insert(a);
    });
    BST_Book_by_DateCreated date_created_book_data;
    lib.get_book_data().traverse_ascending([&date_created_book_data](book &a){
        date_created_book_data.insert(a);
    });

    //cout << borrow_data.find_new_id_borrow();
    //applyFusionDark(a);   
    qDebug() << xoa_dau_lower("Như bác ơi đó");
    qDebug() << tim_kiem_co_chua("Như bác ơi đó","Như có Bác Hồ trong Như hrhr Như ơi");
    qDebug() << tim_kiem_chinh_xac("Như bác ơi đó","Như có Bác Hồ trong Như hrhr Như ơi");
    qDebug() << tim_kiem_chinh_xac("Một hai ba","một hai ba");
    qDebug() << tim_kiem_bat_dau_bang("Như bác ơi đó","Như bác ơi đó có Bác Hồ trong Như hrhr Như ơi");

    pbl2 w;
    w.show();

    int exitCode = a.exec();

    // Lưu dữ liệu trước khi thoát

    return exitCode;
}

void pbl2::on_dang_ky_button_clicked()
{
    auto win = new dang_ky_dialog(this);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    // Khi cửa sổ đăng ký đóng, hiển thị lại Pbl2
    connect(win, &dang_ky_dialog::registered, this, [this, win](const Account& user) {
        acc_sign_in = user;
        //ui->info->setCurrentIndex(1);
        //ui->user_name_layout->setText(
        //    QString::fromStdString("Xin chào " + giai_ma_str_(acc_sign_in.getAccount_Name()) + ","));
        //ui->score_layout->setText("Admin");
        this->show();
        this->raise();
        this->activateWindow();
        win->deleteLater();
    });
    connect(win, &dang_ky_dialog::returned, this, [this,win](){
        this->show();
        this->raise();
        this->activateWindow();
    });
    win->show();
    this->hide(); // Ẩn cửa sổ chính
}
