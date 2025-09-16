#include "admin_show.h"
#include "ui_admin_show.h"
#include "book.h"
#include "my_file.h"
#include "my_string.h"
#include "tree.h"
#include "global.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>

static void markError(QLineEdit* w, const QString& msg) {
    w->clear();
    w->setPlaceholderText(msg);
    w->setStyleSheet("QLineEdit{border:2px solid #e53935;border-radius: 6px;}");
    QPalette pal = w->palette();
    pal.setColor(QPalette::PlaceholderText, QColor("#e53935"));
    w->setPalette(pal);
    w->setFocus();
}

static void clearError(QLineEdit* w) {
    w->setStyleSheet("QLineEdit{background: rgb(243, 246, 255); color: rgb(8, 104, 173); border: 2px solid rgb(69, 104, 173); border-radius: 6px;}");
    w->setPalette(QPalette());
}

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

void admin_show::on_them_button_clicked()
{
    string id_book = ui_3->ID_Sach_input->text().toUtf8().toStdString();
    string ten_sach = ui_3->ten_sach_input->text().toUtf8().toStdString();
    string tac_gia = ui_3->tac_gia_input->text().toUtf8().toStdString();
    string nam_xuat_ban = ui_3->nam_xuat_ban_input->text().toUtf8().toStdString();
    string nha_xuat_ban = ui_3->nha_xuat_ban_input->text().toUtf8().toStdString();
    string so_trang = ui_3->so_trang_input->text().toUtf8().toStdString();
    string ISBN = ui_3->ISBN_input->text().toUtf8().toStdString();
    string ngon_ngu = ui_3->language_input->text().toUtf8().toStdString();
    string tu_khoa = ui_3->chu_de_input->text().toUtf8().toStdString();
    string chuyen_nganh = ui_3->chuyen_nganh_input->text().toUtf8().toStdString();
    string don_gia = ui_3->don_gia_input->text().toUtf8().toStdString();
    string tom_tat = ui_3->tom_tat_input->toPlainText().toUtf8().toStdString();
    string link_png = ui_3->link_png_input->text().toUtf8().toStdString();
    string link_pdf = ui_3->link_pdf_input->text().toUtf8().toStdString();
    string type_book = "null";
    string tinh_trang = "null";
    if (id_book.empty()){
        markError(ui_3->ID_Sach_input,"Vui lòng nhập ID sách");
        return;
    }
    else clearError(ui_3->ID_Sach_input);
    if (ten_sach.empty()){
        markError(ui_3->ten_sach_input,"Vui lòng nhập tên sách");
        return;
    }
    else clearError(ui_3->ten_sach_input);
    if (tac_gia.empty()){
        markError(ui_3->tac_gia_input,"Vui lòng nhập tác giả");
        return;
    }
    else clearError(ui_3->tac_gia_input);
    if (nam_xuat_ban.empty()){
        markError(ui_3->nam_xuat_ban_input,"Vui lòng nhập năm xuất bản");
        return;
    }
    else clearError(ui_3->nam_xuat_ban_input);
    if (nha_xuat_ban.empty()){
        markError(ui_3->nha_xuat_ban_input,"Vui lòng nhập nhà xuất bản");
        return;
    }
    else clearError(ui_3->nha_xuat_ban_input);
    if (so_trang.empty()){
        markError(ui_3->so_trang_input,"Vui lòng nhập số trang");
        return;
    }
    else clearError(ui_3->so_trang_input);
    if (ISBN.empty()){
        markError(ui_3->ISBN_input,"Vui lòng nhập ISBN");
        return;
    }
    else clearError(ui_3->ISBN_input);
    if (ngon_ngu.empty()){
        markError(ui_3->language_input,"Vui lòng nhập ngôn ngữ");
        return;
    }
    else clearError(ui_3->language_input);
    if (tu_khoa.empty()){
        markError(ui_3->chu_de_input,"Vui lòng nhập từ khóa");
        return;
    }
    else clearError(ui_3->chu_de_input);
    if (chuyen_nganh.empty()){
        markError(ui_3->chuyen_nganh_input,"Vui lòng nhập chuyên ngành");
        return;
    }
    else clearError(ui_3->chuyen_nganh_input);
    if (don_gia.empty()){
        markError(ui_3->don_gia_input,"Vui lòng nhập đơn giá");
        return;
    }
    else clearError(ui_3->don_gia_input);
    if (link_png.empty()){
        markError(ui_3->link_png_input,"Vui lòng nhập link ảnh");
        return;
    }
    else clearError(ui_3->link_png_input);
    if (link_pdf.empty()){
        markError(ui_3->link_pdf_input,"Vui lòng nhập link pdf");
        return;
    }
    else clearError(ui_3->link_pdf_input);
    book b;
    b.set_id_book(id_book);
    b.set_name_book(ten_sach);
    b.set_tac_gia(tac_gia);
    b.set_nha_xuat_ban(nha_xuat_ban);
    b.set_nam_xuat_ban(nam_xuat_ban);
    b.set_so_trang(so_trang);
    b.set_ISBN(ISBN);
    b.set_ngon_ngu(ngon_ngu);
    b.set_tu_khoa(tu_khoa);
    b.set_chuyen_nganh(chuyen_nganh);
    b.set_don_gia(don_gia);
    b.set_tom_tat(tom_tat);
    b.set_link_png(link_png);
    b.set_link_pdf(link_pdf);
    b.set_type_book(type_book);
    b.set_tinh_trang(tinh_trang);
    book_data.insert_Book(b);
    ghi_book(book_data);
    box_thong_bao("Thêm sách thành công");
}

//string user_nguoi_dung = ui_2->user_input->text().trimmed().toUtf8().toStdString();
