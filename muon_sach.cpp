#include "muon_sach.h"
#include "ui_muon_sach.h"
#include "global.h"
#include "my_time.h"
#include <QMessageBox>
#include <QLineEdit>

muon_sach::muon_sach(borrow &borrow_inf,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::muon_sach)
    , borrow_info(borrow_inf)
{
    ui->setupUi(this);
    them_doc_gia_muon();
    them_sach();

    connect(ui->doc_gia->lineEdit(), &QLineEdit::editingFinished, this, [this](){
        QString text = ui->doc_gia->currentText();
        if (!text.isEmpty() && ui->doc_gia->findText(text) == -1) {
            ui->doc_gia->setCurrentIndex(-1);
            ui->doc_gia->setEditText("");
            ui->doc_gia->setToolTip("Bạn đã nhập sai tên độc giả!");
        } else {
            ui->doc_gia->setToolTip("");
        }
    });

    connect(ui->ten_sach->lineEdit(), &QLineEdit::editingFinished, this, [this](){
        QString text = ui->ten_sach->currentText();
        if (!text.isEmpty() && ui->ten_sach->findText(text) == -1) {
            ui->ten_sach->setCurrentIndex(-1);
            ui->ten_sach->setEditText("");
            ui->ban_sao->clear();
        }
    });

    them_ngay_muon_ngay_tra();
    if (borrow_info.get_id() != 0){
        set_thong_tin();
    }
    this->setMaximumHeight(0);
}

muon_sach::~muon_sach()
{
    delete ui;
}

void muon_sach::them_doc_gia_muon(){
    ui->doc_gia->clear();
    accout_data.traverse_ascending([this](accout& a){
        QString text = QString::fromStdString(a.get_phone_number() + " - " + a.get_ten_tai_khoan());
        ui->doc_gia->addItem(text, QVariant::fromValue(a.get_ID()));
    });
}

void muon_sach::them_sach(){
    ui->ten_sach->clear();
    book_data.traverse_ascending([this](book& b){
        QString text = QString::fromStdString(std::to_string(b.get_ID()) + " - " + b.get_Name());
        ui->ten_sach->addItem(text, QVariant::fromValue(b.get_ID()));
    });
}

void muon_sach::them_ban_sao(long long book_id){
    ui->ban_sao->clear();
    book_copy_data.traverse_ascending([this, book_id](Book_copies& bc){
        if (bc.get_id_book() == book_id && bc.get_status() == "available"){
            QString text = QString::fromStdString("BS-" + std::to_string(bc.get_id()));
            ui->ban_sao->addItem(text, QVariant::fromValue(bc.get_id()));
        }
    });
}

void muon_sach::them_ngay_muon_ngay_tra(){
    my_time ngay_muon = my_time::now();
    my_time ngay_phai_tra = ngay_muon.add_time(my_time(0,0,14,0,0,0));
    ui->ngay_muon->setDate(QDate(ngay_muon.get_year(), ngay_muon.get_month(), ngay_muon.get_day()));
    ui->ngay_tra->setDate(QDate(ngay_phai_tra.get_year(), ngay_phai_tra.get_month(), ngay_phai_tra.get_day()));
}
void muon_sach::on_doc_gia_currentTextChanged(const QString &arg1)
{   
}


void muon_sach::on_ten_sach_currentTextChanged(const QString &arg1)
{
    long long book_id = ui->ten_sach->currentData().toLongLong();
    them_ban_sao(book_id);
}

void muon_sach::set_thong_tin(){
    long long user_id = borrow_info.get_user_id();
    int index_doc_gia = ui->doc_gia->findData(QVariant::fromValue(user_id));
    if (index_doc_gia != -1) {
        ui->doc_gia->setCurrentIndex(index_doc_gia);
    }
    int index_ten_sach = ui->ten_sach->findData(QVariant::fromValue(borrow_info.get_book_id()));;
    if (index_ten_sach != -1) {
        ui->ten_sach->setCurrentIndex(index_ten_sach);
    }
    long long copy_id = borrow_info.get_book_copy_id();
    int index_ban_sao = ui->ban_sao->findData(QVariant::fromValue(copy_id));;
    if (index_ban_sao != -1) {
        ui->ban_sao->setCurrentIndex(index_ban_sao);
    }

    //my_time ngay_muon = borrow_info.get_ngay_muon();
    //my_time ngay_tra = borrow_info.get_ngay_tra();
    //ui->ngay_muon->setDate(QDate(ngay_muon.get_year(), ngay_muon.get_month(), ngay_muon.get_day()));
    //ui->ngay_tra->setDate(QDate(ngay_tra.get_year(), ngay_tra.get_month(), ngay_tra.get_day()));
}
void muon_sach::on_muon_sach_button_clicked()
{
    long long user_id = ui->doc_gia->currentData().toLongLong();
    long long book_id = ui->ten_sach->currentData().toLongLong();
    long long copy_id = ui->ban_sao->currentData().toLongLong();

    if (user_id == 0) {
        QMessageBox::warning(this, "Thông báo", "Tên độc giả không tồn tại trong hệ thống!\nVui lòng chọn từ danh sách gợi ý.");
        ui->doc_gia->setFocus(); // Đưa con trỏ chuột về lại ô này để sửa
        return; // Dừng hàm, không chạy đoạn dưới nữa
    }
    if (book_id == 0) {
        QMessageBox::warning(this, "Thông báo", "Tên sách không tồn tại!\nVui lòng chọn từ danh sách gợi ý.");
        ui->ten_sach->setFocus();
        return;
    }
    if (copy_id == 0) {
        QMessageBox::warning(this, "Thông báo", "Vui lòng chọn bản sao sách hợp lệ!");
        ui->ban_sao->setFocus();
        return;
    }

    QDate qdate_ngay_muon =  ui->ngay_muon->date();
    QDate qdate_ngay_tra =  ui->ngay_tra->date();
    my_time ngay_muon(qdate_ngay_muon.year(), qdate_ngay_muon.month(), qdate_ngay_muon.day(),0,0,0);
    my_time ngay_tra(qdate_ngay_tra.year(), qdate_ngay_tra.month(), qdate_ngay_tra.day(),0,0,0);

    borrow_info.set_user_id(user_id);
    borrow_info.set_book_id(book_id);
    borrow_info.set_book_copy_id(copy_id);
    borrow_info.set_ngay_muon(ngay_muon);
    borrow_info.set_ngay_phai_tra(ngay_tra);
    borrow_info.set_status(StatusType::DANG_MUON);
    if (borrow_info.get_id() == 0){
        borrow_info.set_id(borrow_data.find_new_id_borrow());
        borrow_data.insert(borrow_info);
    }
    else {
        borrow_data.update(borrow_info, borrow_info);
    }
    Book_copies bc;
    if (book_copy_data.find(copy_id, bc)){
        bc.set_status("borrowed");
        book_copy_data.update(bc, bc);
    }
    ghi_copy_book(book_copy_data);
    emit muon_sach_thanh_cong();
    this->close();
}

void muon_sach::set_up_borrow_info(){
    ui->doc_gia->setEnabled(false);
    ui->ten_sach->setEnabled(false);
    ui->ten_sach->setEditText(QString::fromStdString(borrow_info.get_book_name()));
    ui->ban_sao->setEnabled(false);
    ui->ban_sao->setEditText(QString::fromStdString("BS-" + std::to_string(borrow_info.get_book_copy_id())));
    ui->ngay_muon->setEnabled(false);
    ui->ngay_tra->setEnabled(false);
    ui->muon_sach_button->setVisible(false);
}
void muon_sach::set_up_xu_ly_muon_sach(){
    ui->doc_gia->setEnabled(false);
    ui->ten_sach->setEnabled(false);
}



void muon_sach::on_doc_gia_activated(int index)
{

}

