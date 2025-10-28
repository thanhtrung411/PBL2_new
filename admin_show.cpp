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

void admin_show::return_null_all(){
    ui_3->ID_Sach_input->clear();
    ui_3->ten_sach_input->clear();
    ui_3->tac_gia_input->clear();
    ui_3->nha_xuat_ban_input->clear();
    ui_3->nam_xuat_ban_input->clear();
    ui_3->so_trang_input->clear();
    ui_3->ISBN_input->clear();
    ui_3->language_input->clear();
    ui_3->tom_tat_input->clear();
    ui_3->link_png_layout->clear();
    ui_3->link_pdf_layout->clear();
    ui_3->the_loai_sach_input->setCurrentIndex(0);
    ui_3->chuyen_nganh_input->setCurrentIndex(0);
    ui_3->is_read_online_check->setChecked(false);
    ui_3->is_borrow_check->setChecked(false);
    ui_3->is_download_check->setChecked(false);

}

void admin_show::on_them_button_clicked()
{
    int id;
    string id_book = ui_3->ID_Sach_input->text().trimmed().toUtf8().toStdString();
    string ten_sach = ui_3->ten_sach_input->text().trimmed().toUtf8().toStdString();
    string tac_gia = ui_3->tac_gia_input->text().trimmed().toUtf8().toStdString();
    string nha_xuat_ban = ui_3->nha_xuat_ban_input->text().trimmed().toUtf8().toStdString();
    string nam_xuat_ban = ui_3->nam_xuat_ban_input->text().trimmed().toUtf8().toStdString();
    int so_trang = ui_3->so_trang_input->text().trimmed().toUtf8().toInt();
    string ISBN = ui_3->ISBN_input->text().trimmed().toUtf8().toStdString();
    string ngon_ngu = ui_3->language_input->text().trimmed().toUtf8().toStdString();
    string tom_tat = ui_3->tom_tat_input->toPlainText().trimmed().toUtf8().toStdString();
    string link_png_ = ui_3->link_png_layout->text().trimmed().toUtf8().toStdString();
    string link_pdf_ = ui_3->link_pdf_layout->text().trimmed().toUtf8().toStdString();
    string the_loai = ui_3->the_loai_sach_input->currentText().trimmed().toStdString();
    string chuyen_nganh = ui_3->chuyen_nganh_input->currentText().trimmed().toStdString();
    bool is_read = ui_3->is_read_online_check->isCheckable() ? true : false;
    bool is_borrow = ui_3->is_borrow_check->isCheckable() ? true : false;
    bool is_download = ui_3->is_download_check->isCheckable() ? true : false;
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
    if (so_trang <= 0){
        markError(ui_3->so_trang_input,"Vui lòng nhập số trang");
        check = 0;
    }
    else clearError(ui_3->so_trang_input);
    if (ngon_ngu.empty()){
        markError(ui_3->language_input,"Vui lòng nhập ngôn ngữ");
        check = 0;
    }
    else clearError(ui_3->language_input);
    if (tom_tat.empty()){
        check = 0;
    }
    else;
    if (check){
        book b;
        b.set_ID(to_int(id_book));
        b.set_Name(ten_sach);
        b.set_Author(tac_gia);
        //b.set_The_loai_ID(the_loai_data.return_id(the_loai));
        b.set_NXB(nha_xuat_ban);
        b.set_NamXB(nam_xuat_ban);
        b.set_So_trang(so_trang);
        b.set_ISBN(ISBN);
        b.set_Language(ngon_ngu);
        //b.set_Chuyen_nganh_ID(chuyen_nganh_data.return_id(chuyen_nganh));
        b.set_Tom_tat(tom_tat);
        my_time d;
        d.now();
        b.set_is_Borrow(is_borrow);
        b.set_is_Download(is_download);
        b.set_is_Read_online(is_read);
        b.set_Date_created(d);
        b.set_Created_by(acc_sign_in.get_ten_dang_nhap());
        QString path = getDataFilePath("png_background\\");
        copy_file(link_png_,path.toStdString() + to_string(b.get_ID()) + ".png");
        QString rel = QDir::current().relativeFilePath(path);
        qDebug() << rel;
        b.set_Link_png(rel.toStdString()+ "/" + to_string(b.get_ID()) + ".png");
        path = getDataFilePath("pdf_book\\");
        copy_file(link_pdf_,path.toStdString() + to_string(b.get_ID()) + ".pdf");
        rel = QDir::current().relativeFilePath(path);
        b.set_Link_pdf(rel.toStdString() +"/"+ to_string(b.get_ID()) + ".pdf");
        book_data.insert(b);
        for (int i = 0 ; i < ui_3->number_of_book->value();i++){
            /*
            Book_copies bc;
            bc.set_id_book(b.get_ID());
            string id_ = id_book +"." + toFixedString(i+1,3);
            bc.set_id(id_);
            qDebug() << id_;
            if (i == 0) bc.set_status("Chỉ đọc");
            else if (to_int(b.get_is_Borrow())){
                bc.set_status("Có sẵn");
            }
            else bc.set_status("Chỉ đọc");
            book_copy_data.insert_book_copy(bc);
            */
        }
        ghi_copy_book(book_copy_data);
        ghi_book(book_data);
        box_thong_bao("Thêm sách thành công");
        return_null_all();

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
    int The_loai_ID = the_loai_data.return_id(the_loai_);
    int Chuyen_nganh_ID = chuyen_nganh_data.return_id(chuyen_nganh_);
    if (chuyen_nganh_ == "Khác..."){
        Chuyen_nganh_ID = 99;
    }
    my_time now = my_time::now();
    int ID_CN_temp;
    if (Chuyen_nganh_ID < 10){
        ID_CN_temp = Chuyen_nganh_ID *1000000;
    }
    else {
        ID_CN_temp = Chuyen_nganh_ID *100000;
    }
    if (the_loai_ == "Khác..."){
        The_loai_ID = 8;
        long long ID_temp = (long long)now.get_year()*100000000 + ID_CN_temp + The_loai_ID*100000 + 1;
        BST_Book b;
        book_data.tong_hop_sach_TL_CN(The_loai_ID, Chuyen_nganh_ID, b, book_data);
        long long max_id = b.find_max_id();
        if (!(max_id - 99999) % 100000){
            The_loai_ID += 1;
            ID_temp = (long long)now.get_year()*100000000 + ID_CN_temp + The_loai_ID*100000 + 1;
            BST_Book b;
            book_data.tong_hop_sach_TL_CN(The_loai_ID, Chuyen_nganh_ID, b, book_data);
            max_id = b.find_max_id();
            if (!(max_id - 99999) % 100000){
                box_thong_bao("Số lượng thể loại sách đã đạt giới hạn!");
                return;
            }
            else{
                if ()
            }

        }
    }
}

void admin_show::set_the_loai_chuyen_nganh(){
    ui_3->the_loai_sach_input->clear();
    ui_3->chuyen_nganh_input->clear();
    ui_3->the_loai_sach_input->addItem("Vui lòng chọn thể loại sách...");
    ui_3->chuyen_nganh_input->addItem("Vui lòng chọn chuyên ngành...");
    for (int i = 0 ; i < the_loai_data.count_data() ; i++){
        ui_3->the_loai_sach_input->addItem(the_loai_data[i].get_name().c_str());
    }
    for (int i = 0 ; i < chuyen_nganh_data.count_data() ; i++){
        ui_3->chuyen_nganh_input->addItem(chuyen_nganh_data[i].get_name().c_str());
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

void admin_show::closeEvent(QCloseEvent *event)
{
    QWidget *parentWin = this->parentWidget();
    if (parentWin) {
        parentWin->show();
    }
    this->deleteLater();
    event->accept();
}
