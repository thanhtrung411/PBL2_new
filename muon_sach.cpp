#include "muon_sach.h"
#include "ui_muon_sach.h"
#include "global.h"
#include "exception.h"
#include "my_time.h"
#include "library.h"
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
    lib.get_account_data().traverse_ascending([this](Account& a){
        QString text = QString::fromStdString(a.get_phone_number() + " - " + a.get_ten_tai_khoan());
        ui->doc_gia->addItem(text, QVariant::fromValue(a.get_ID()));
    });
}

void muon_sach::them_sach(){
    ui->ten_sach->clear();
    lib.get_book_data().traverse_ascending([this](book& b){
        QString text = QString::fromStdString(std::to_string(b.get_ID()) + " - " + b.get_Name());
        ui->ten_sach->addItem(text, QVariant::fromValue(b.get_ID()));
    });
}

void muon_sach::them_ban_sao(long long book_id){
    ui->ban_sao->clear();
    lib.get_book_copy_data().traverse_ascending([this, book_id](Book_copies& bc){
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
    QDate qdate_ngay_muon =  ui->ngay_muon->date();
    QDate qdate_ngay_tra =  ui->ngay_tra->date();
    my_time ngay_muon(qdate_ngay_muon.year(), qdate_ngay_muon.month(), qdate_ngay_muon.day(),0,0,0);
    my_time ngay_tra(qdate_ngay_tra.year(), qdate_ngay_tra.month(), qdate_ngay_tra.day(),0,0,0);

    try {
        lib.muon_sach(borrow_info,book_id, user_id, copy_id, ngay_muon, ngay_tra, is_show_xu_ly_muon_sach);
    }
    catch (const AppException& e) {
        QMessageBox::warning(this, QString::fromStdString(e.getTitle()), QString::fromStdString(e.what()));
        return;
    }

    emit muon_sach_thanh_cong();
    this->close();
}

void muon_sach::set_up_borrow_info(){
    ui->doc_gia->setEnabled(false);
    ui->ten_sach->setEnabled(false);
    ui->ten_sach->setEditText(QString::fromStdString(borrow_info.get_book_name()));
    ui->ban_sao->setEnabled(false);
    ui->ban_sao->setEditText(QString::fromStdString("BS-" + std::to_string(borrow_info.get_book_copy_id())));
    ui->ngay_muon->setReadOnly(true);
    ui->ngay_tra->setReadOnly(true);
    ui->muon_sach_button->setVisible(false);
    ui->ngay_muon->setDate(QDate(borrow_info.get_ngay_muon().get_year(),
                            borrow_info.get_ngay_muon().get_month(),
                            borrow_info.get_ngay_muon().get_day()));
    ui->ngay_tra->setDate(QDate(borrow_info.get_ngay_phai_tra().get_year(),
                            borrow_info.get_ngay_phai_tra().get_month(),
                            borrow_info.get_ngay_phai_tra().get_day()));
}
void muon_sach::set_up_xu_ly_muon_sach(){
    ui->doc_gia->setEnabled(false);
    ui->ten_sach->setEnabled(false);
    is_show_xu_ly_muon_sach = true;
}



void muon_sach::on_doc_gia_activated(int index)
{

}

my_time muon_sach::get_ngay_muon()
{
    QDate qdate_ngay_muon =  ui->ngay_muon->date();
    my_time ngay_muon(qdate_ngay_muon.year(), qdate_ngay_muon.month(), qdate_ngay_muon.day(),0,0,0);
    return ngay_muon;
}
my_time muon_sach::get_ngay_phai_tra()
{
    QDate qdate_ngay_tra =  ui->ngay_tra->date();
    my_time ngay_tra(qdate_ngay_tra.year(), qdate_ngay_tra.month(), qdate_ngay_tra.day(),0,0,0);
    return ngay_tra;
}
