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
    long long id;
    string id_book = ui_3->ID_Sach_input->text().trimmed().toUtf8().toStdString();
    string ten_sach = ui_3->ten_sach_input->text().trimmed().toUtf8().toStdString();
    string tac_gia = ui_3->tac_gia_input->text().trimmed().toUtf8().toStdString();
    string nha_xuat_ban = ui_3->nha_xuat_ban_input->text().trimmed().toUtf8().toStdString();
    int nam_xuat_ban = ui_3->nam_xuat_ban_input->text().trimmed().toUtf8().toInt();
    int so_trang = ui_3->so_trang_input->text().trimmed().toUtf8().toInt();
    string ISBN = ui_3->ISBN_input->text().trimmed().toUtf8().toStdString();
    string ngon_ngu = ui_3->language_input->text().trimmed().toUtf8().toStdString();
    string tom_tat = ui_3->tom_tat_input->toPlainText().trimmed().toUtf8().toStdString();
    string link_png_ = ui_3->link_png_layout->text().trimmed().toUtf8().toStdString();
    string link_pdf_ = ui_3->link_pdf_layout->text().trimmed().toUtf8().toStdString();
    string the_loai = ui_3->the_loai_sach_input->currentText().trimmed().toStdString();
    string chuyen_nganh = ui_3->chuyen_nganh_input->currentText().trimmed().toStdString();
    bool is_read = ui_3->is_read_online_check->isChecked() ? true : false;
    bool is_borrow = ui_3->is_borrow_check->isChecked() ? true : false;
    bool is_download = ui_3->is_download_check->isChecked() ? true : false;
    int limit_borrow = ui_3->so_ngay_muon_input->value();
    int number_of_book = ui_3->number_of_book->value();
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
    if (nam_xuat_ban <= 0){
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
        b.set_ID(to_long_long(id_book));
        b.set_Name(ten_sach);
        b.set_Author(tac_gia);
        int the_loai_id;
        the_loai_data.return_id(the_loai, the_loai_id);
        b.set_The_loai_ID(the_loai_id);
        b.set_NXB(nha_xuat_ban);
        b.set_NamXB(nam_xuat_ban);
        b.set_So_trang(so_trang);
        b.set_ISBN(ISBN);
        b.set_Language(ngon_ngu);
        int chuyen_nganh_id;
        chuyen_nganh_data.return_id(chuyen_nganh, chuyen_nganh_id);
        b.set_Chuyen_nganh_ID(chuyen_nganh_id);
        b.set_Tom_tat(tom_tat);
        my_time d = my_time::now();
        b.set_is_Borrow(is_borrow);
        b.set_is_Download(is_download);
        b.set_is_Read_online(is_read);
        b.set_tong_sach(number_of_book);
        b.set_limit_borrow(limit_borrow);
        b.set_tong_sach_ranh(number_of_book);
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
            Book_copies bc;
            long long id_copy = book_copy_data.find_max_id() + 1;
            bc.set_id(id_copy);
            bc.set_id_book(b.get_ID());
            if (is_read){
                bc.set_status("available");
            }
            else {
                bc.set_status("not available");
            }
            book_copy_data.insert(bc);
        }
        //ghi_copy_book(book_copy_data);
        //ghi_book(book_data);
        QMessageBox box(this);
        box.setWindowTitle("Thông báo");
        box.setText("Thêm sách thành công !");
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
    int The_loai_ID;
    the_loai_data.return_id(the_loai_,The_loai_ID);
    int Chuyen_nganh_ID;
    chuyen_nganh_data.return_id(chuyen_nganh_, Chuyen_nganh_ID);
    if (chuyen_nganh_ == "Khác..."){
        Chuyen_nganh_ID = 99;
    }
    my_time now = my_time::now();
    long long ID_CN_temp;
    if (Chuyen_nganh_ID < 10){
        ID_CN_temp = Chuyen_nganh_ID *1000000;
    }
    else {
        ID_CN_temp = Chuyen_nganh_ID *1000000;
    }
    if (the_loai_ == "Khác..."){
        The_loai_ID = 8;
        BST_Book b;
        book_data.tong_hop_sach_TL_CN(The_loai_ID, Chuyen_nganh_ID, b,book_data);
        long long max_id = b.find_max_id();
        if ((max_id - 99999 & 100000) == 0 && max_id > 0){
            The_loai_ID = 9;
            BST_Book b_;
            book_data.tong_hop_sach_TL_CN(The_loai_ID, Chuyen_nganh_ID, b_,book_data);
            long long max_id_ = b_.find_max_id();
            if ((max_id_ - 99999 & 100000) == 0 && max_id_ > 0){
                ui_3->ID_Sach_input->clear();
                ui_3->ID_Sach_input->setPlaceholderText("Hết mã ID cho chuyên ngành này");
                return;
            }
            else{
                long long ID_temp = (long long)now.get_year() * 100000000LL + ID_CN_temp + The_loai_ID * 100000 + 1;
                if (max_id_ < ID_temp -1){
                    ui_3->ID_Sach_input->setText(QString::fromStdString(to_stringll_(ID_temp)));
                    return;
                }
                else {
                    long long new_id = max_id_ + 1;
                    ui_3->ID_Sach_input->setText(QString::fromStdString(to_stringll_(new_id)));
                    return;
                }
            }
        }
        else{
            long long ID_temp = (long long)now.get_year() * 100000000LL + ID_CN_temp + The_loai_ID * 100000 + 1;
            if (max_id < ID_temp -1){
                ui_3->ID_Sach_input->setText(QString::fromStdString(to_stringll_(ID_temp)));
                return;
            }
            else {
                long long new_id = max_id + 1;
                ui_3->ID_Sach_input->setText(QString::fromStdString(to_stringll_(new_id)));
                return;
            }
        }
    }
    else{
        BST_Book b;
        book_data.tong_hop_sach_TL_CN(The_loai_ID, Chuyen_nganh_ID, b,book_data);
        long long max_id = b.find_max_id();
        if ((max_id - 99999 & 100000) == 0 && max_id > 0){
            ui_3->ID_Sach_input->clear();
            ui_3->ID_Sach_input->setPlaceholderText("Hết mã ID cho chuyên ngành này");
            return;
        }
        else{
            long long ID_temp = (long long)now.get_year() * 100000000LL + ID_CN_temp + The_loai_ID * 100000 + 1;
            if (max_id < ID_temp -1){
                ui_3->ID_Sach_input->setText(QString::fromStdString(to_string(ID_temp)));
                return;
            }
            else {
                long long new_id = max_id + 1;
                ui_3->ID_Sach_input->setText(QString::fromStdString(to_string(new_id)));
                return;
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
