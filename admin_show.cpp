#include "admin_show.h"
#include "ui_admin_show.h"
#include "book.h"
#include "my_file.h"
#include "my_time.h"
#include "my_string.h"
#include "tree.h"
#include "global.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QDebug>
#include <QPalette>

static const QString png_background = QCoreApplication::applicationDirPath() + "/png";

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
    set_the_loai_chuyen_nganh();
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
    string the_loai = ui_3->the_loai_sach_input->currentText().toStdString();
    string nam_xuat_ban = ui_3->nam_xuat_ban_input->text().toUtf8().toStdString();
    string nha_xuat_ban = ui_3->nha_xuat_ban_input->text().toUtf8().toStdString();
    string so_trang = ui_3->so_trang_input->text().toUtf8().toStdString();
    string ISBN = ui_3->ISBN_input->text().toUtf8().toStdString();
    string ngon_ngu = ui_3->language_input->text().toUtf8().toStdString();
    string tu_khoa = ui_3->chu_de_input->text().toUtf8().toStdString();
    string chuyen_nganh = ui_3->chuyen_nganh_input->currentText().toStdString();
    string don_gia = ui_3->don_gia_input->text().toUtf8().toStdString();
    string tom_tat = ui_3->tom_tat_input->toPlainText().toUtf8().toStdString();
    string type_book = "null";
    string tinh_trang = "null";
    string link_png_ = ui_3->link_png_layout->text().toUtf8().toStdString();
    string link_pdf_ = ui_3->link_pdf_layout->text().toUtf8().toStdString();
    string date_created;
    string user_created;
    int check = 1;
    if (ten_sach.empty()){
        markError(ui_3->ten_sach_input,"Vui lòng nhập tên sách");
        check = 0;
    }
    else clearError(ui_3->ten_sach_input);
    if (tac_gia.empty()){
        markError(ui_3->tac_gia_input,"Vui lòng nhập tác giả");
        check = 0;
    }
    else clearError(ui_3->tac_gia_input);
    if (nam_xuat_ban.empty()){
        markError(ui_3->nam_xuat_ban_input,"Vui lòng nhập năm xuất bản");
        check = 0;
    }
    else clearError(ui_3->nam_xuat_ban_input);
    if (ui_3->the_loai_sach_input->currentIndex() == 0){
        check = 0;
    }
    else;
    if (ui_3->chuyen_nganh_input->currentIndex() == 0){
        check = 0;
    }
    else;
    if (nha_xuat_ban.empty()){
        markError(ui_3->nha_xuat_ban_input,"Vui lòng nhập nhà xuất bản");
        check = 0;
    }
    else clearError(ui_3->nha_xuat_ban_input);
    if (so_trang.empty()){
        markError(ui_3->so_trang_input,"Vui lòng nhập số trang");
        check = 0;
    }
    else clearError(ui_3->so_trang_input);
    if (ngon_ngu.empty()){
        markError(ui_3->language_input,"Vui lòng nhập ngôn ngữ");
        check = 0;
    }
    else clearError(ui_3->language_input);
    if (tu_khoa.empty()){
        markError(ui_3->chu_de_input,"Vui lòng nhập từ khóa");
        check = 0;
    }
    else clearError(ui_3->chu_de_input);
    if (don_gia.empty()){
        markError(ui_3->don_gia_input,"Vui lòng nhập đơn giá");
        check = 0;
    }
    else clearError(ui_3->don_gia_input);
    if (tom_tat.empty()){
        check = 0;
    }
    else;
    if (check){
        book b;
        b.set_id_book(id_book);
        b.set_name_book(ten_sach);
        b.set_tac_gia(tac_gia);
        b.set_the_loai(the_loai);
        b.set_nha_xuat_ban(nha_xuat_ban);
        b.set_nam_xuat_ban(nam_xuat_ban);
        b.set_so_trang(so_trang);
        b.set_ISBN(ISBN);
        b.set_ngon_ngu(ngon_ngu);
        b.set_tu_khoa(tu_khoa);
        b.set_chuyen_nganh(chuyen_nganh);
        b.set_don_gia(don_gia);
        b.set_tom_tat(tom_tat);
        b.set_type_book(type_book);
        b.set_tinh_trang(tinh_trang);
        my_time d;
        d.set_time_now();
        b.set_date_created(d.get_time());
        b.set_admin_created(acc_sign_in.getAccout_id());
        QString path = getDataFilePath("png_background\\");
        copy_file(link_png_,path.toStdString() + b.get_id_book() + ".png");
        QString rel = QDir::current().relativeFilePath(path);
        qDebug() << rel;
        b.set_link_png(rel.toStdString()+ "/" + b.get_id_book() + ".png");
        path = getDataFilePath("pdf_book\\");
        copy_file(link_pdf_,path.toStdString() + b.get_id_book() + ".pdf");
        rel = QDir::current().relativeFilePath(path);
        b.set_link_pdf(rel.toStdString() +"/"+ b.get_id_book() + ".pdf");
        book_data.insert_Book(b);
        ghi_book(book_data);
        box_thong_bao("Thêm sách thành công");
    }
    else {
        return;
    }
}

//string user_nguoi_dung = ui_2->user_input->text().trimmed().toUtf8().toStdString();

void admin_show::on_chuyen_nganh_input_textActivated(const QString &arg1){
    set_ID_book();
}


void admin_show::on_the_loai_sach_input_textActivated(const QString &arg1){
    set_ID_book();
}

void admin_show::set_ID_book(){
    string chuyen_nganh_ = ui_3->chuyen_nganh_input->currentText().toStdString();
    string the_loai_ = ui_3->the_loai_sach_input->currentText().toStdString();
    if (ui_3->chuyen_nganh_input->currentIndex() == 0) return;
    if (ui_3->the_loai_sach_input->currentIndex() == 0) return;
    string vt_chuyen_nganh_[15] = {"A","B","C","D","E","F","G","X"};
    int set_chuyen_nganh_1 = ui_3->chuyen_nganh_input->currentIndex();
    int the_loai_min = 0;
    int the_loai_max = 0;
    switch (ui_3->the_loai_sach_input->currentIndex())
    {
    case 1:
        the_loai_min = 0;
        the_loai_max = 200;
        break;
    case 2:
        the_loai_min = 200;
        the_loai_max = 400;
        break;
    case 3:
        the_loai_min = 400;
        the_loai_max = 500;
        break;
    case 4:
        the_loai_min = 500;
        the_loai_max = 600;
        break;
    case 5:
        the_loai_min = 600;
        the_loai_max = 700;
        break;
    case 6:
        the_loai_min = 700;
        the_loai_max = 800;
        break;
    case 7:
        the_loai_min = 800;
        the_loai_max = 900;
        break;
    case 8:
        the_loai_min = 900;
        the_loai_max = 999;
        break;
    
    default:
        break;
    }
    BST_Book b_set;
    tong_hop_sach_chung(the_loai_, chuyen_nganh_, book_data, b_set);
    qDebug() << b_set.count_book();
    int set_chuyen_nganh_2 = 1;
    int set_the_loai = the_loai_min;
    for (int i = 0 ; i < b_set.count_book() ; i++){
        string chuyen_nganh_str = b_set[i].get_id_book().substr(6,2);
        string the_loai_str = b_set[i].get_id_book().substr(9,3);
        if (set_chuyen_nganh_2 < to_int(chuyen_nganh_str)){
            set_chuyen_nganh_2 = to_int(chuyen_nganh_str);
            set_the_loai = the_loai_min;
        }
        else{
            if (set_the_loai < to_int(the_loai_str)){
                set_the_loai = to_int(the_loai_str);
            }
        }
    }
    if (set_the_loai == the_loai_max){
        set_chuyen_nganh_2++;
        set_the_loai = the_loai_min;
    }
    else set_the_loai++;
    string id_book = "PBL2-" + vt_chuyen_nganh_[set_chuyen_nganh_1 - 1] + toFixedString(set_chuyen_nganh_2,2) + "-" + toFixedString(set_the_loai,3);
    ui_3->ID_Sach_input->setText(id_book.c_str());
}

void admin_show::set_the_loai_chuyen_nganh(){
    ui_3->the_loai_sach_input->clear();
    ui_3->chuyen_nganh_input->clear();
    ui_3->the_loai_sach_input->addItem("Vui lòng chọn thể loại sách...");
    ui_3->chuyen_nganh_input->addItem("Vui lòng chọn chuyên ngành...");
    for (int i = 0 ; i < the_loai_.count_string() ; i++){
        ui_3->the_loai_sach_input->addItem(the_loai_[i].c_str());
        qDebug() << the_loai_[i].c_str() << i;
    }
    for (int i = 0 ; i < chuyen_nganh_.count_string() ; i++){
        ui_3->chuyen_nganh_input->addItem(chuyen_nganh_[i].c_str());
        qDebug() << chuyen_nganh_[i].c_str();
    }
    ui_3->the_loai_sach_input->addItem("Khác...");
    ui_3->chuyen_nganh_input->addItem("Khác...");
    ui_3->the_loai_sach_input->setCurrentIndex(0);
    ui_3->chuyen_nganh_input->setCurrentIndex(0);

}
void admin_show::on_link_png_button_clicked()
{
    QString fn = QFileDialog::getOpenFileName(
        this,
        tr("Chọn ảnh"),
        QDir::homePath(),                                 // thư mục mở đầu
        tr("Ảnh (*.png *.jpg *.jpeg *.bmp *.gif);;Tất cả (*)")
        );
    if (fn.isEmpty()) return;

    // (tuỳ) lưu đường dẫn tương đối so với thư mục làm việc
    QString rel = QDir::current().relativeFilePath(fn);
    ui_3->link_png_layout->setText(rel);
}


void admin_show::on_link_pdf_button_clicked()
{
    QString fn = QFileDialog::getOpenFileName(
        this,
        tr("Chọn file"),
        QDir::homePath(),
        tr("PDF (*.pdf);;Tất cả (*)")
        );
    if (fn.isEmpty()) return;
    QString rel = QDir::current().relativeFilePath(fn);
    ui_3->link_pdf_layout->setText(rel);
}
