#include "phieu_tra_sach.h"
#include "ui_phieu_tra_sach.h"
#include "my_string.h"
#include "borrow.h"
#include "tree.h"
#include "global.h"
#include "settings_file.h"
#include "my_time.h"
#include "my_file.h"
#include "library.h"
#include "exception.h"

#include <QMessageBox>

phieu_tra_sach::phieu_tra_sach(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::phieu_tra_sach)
{
    ui->setupUi(this);
    load_borrow_can_tra();
    hien_thi_borrow_can_tra();
    this->setMaximumHeight(0);
}

phieu_tra_sach::~phieu_tra_sach()
{
    delete ui;
}

void phieu_tra_sach::load_borrow_can_tra(){
    borrow_can_tra.clear();
    ui->phieu_muon->clear();
    lib.get_borrow_data().tim_sach_muon_thu_thu(borrow_can_tra);
}

void phieu_tra_sach::hien_thi_borrow_can_tra(){
    borrow_can_tra.traverse_ascending([this](borrow& br){
        Account p;
        lib.get_account_data().find(br.get_user_id(),p);
        string phieu_muon_str = p.get_phone_number() + " - " + p.get_ten_tai_khoan() + " - BS-" + to_string(br.get_book_copy_id()) + " - " + br.get_book_name();
        ui->phieu_muon->addItem(QString::fromStdString(phieu_muon_str), QVariant::fromValue(br.get_id()));
    });
}


void phieu_tra_sach::on_phieu_muon_currentIndexChanged(int index)
{
    if (index < 0) return;
    long long borrow_id = ui->phieu_muon->currentData().toLongLong();
    borrow br;
    if (borrow_can_tra.find_Borrow(borrow_id, br)) {
        ui->ngay_muon_date->setText(QString::fromStdString(br.get_ngay_muon().get_date()));
        ui->han_tra_date->setText(QString::fromStdString(br.get_ngay_phai_tra().get_date()));
        my_time today = my_time::now();
        ui->tra_thuc_te_date->setText(QString::fromStdString(today.get_date()));
        if (today > br.get_ngay_phai_tra()) {
            ui->qua_han_muon->setVisible(true);
            int so_ngay_muon_tra = (today - br.get_ngay_phai_tra()).get_day();
            ui->qua_han_muon_2->setText("Quá hạn mượn " + QString::number(so_ngay_muon_tra) + " ngày");
            long long tien_phat = so_ngay_muon_tra;
            tien_phat_1 = tien_phat * settings_file::getInstance()->get_phi_phat_moi_ngay();
            ui->tien_phat->setText("Tổng tiền phạt: " + QString::fromStdString(tien_te_vnd(tien_phat_1)) + " VND");
            tinh_tong_tien_phat();
        } else {
            ui->qua_han_muon->setVisible(false);
            tien_phat_1 = 0;
            tinh_tong_tien_phat();
        }
    }
}


void phieu_tra_sach::on_xac_nhan_clicked()
{
    int tinh_trang_index = ui->tinh_trang_sach->currentIndex();
    long long borrow_id = ui->phieu_muon->currentData().toLongLong();
    borrow br;
    try{
        lib.tra_sach(borrow_id, tinh_trang_index, tien_phat_1, tien_phat_2, "");
        QMessageBox::information(this, "Thông báo", "Xác nhận trả sách thành công!");
        load_borrow_can_tra();
        hien_thi_borrow_can_tra();
        ui->phieu_muon->setCurrentIndex(-1);
        ui->ngay_muon_date->setText("");
        ui->han_tra_date->setText("");
        ui->tra_thuc_te_date->setText("");
        ui->tinh_trang_sach->setCurrentIndex(-1);
        ui->tong_phi_phat->setText("0 VND");
    } catch (const AppException& e) {
        QMessageBox::warning(this, QString::fromStdString(e.getTitle()), QString::fromStdString(e.what()));
        return;
    }
    catch (...){
        QMessageBox::warning(this, "Lỗi", "Đã xảy ra lỗi khi xử lý trả sách.");
        return;
    }
}


void phieu_tra_sach::on_tinh_trang_sach_currentIndexChanged(int index)
{
    long long tong_tien_phat = 0;
    switch (index) {
    case 0: { // tot
        tien_phat_2 = 0;
        tinh_tong_tien_phat();
        break;
    }
    case 1: { //binh thuong
        tien_phat_2 = 0;
        tinh_tong_tien_phat();
        break;
    }
    case 2: { //hu hong
        tien_phat_2 = settings_file::getInstance()->get_tien_phat_hu_hong();
        tinh_tong_tien_phat();
        break;
    }
    case 3: { //mat sach
        tien_phat_2 = settings_file::getInstance()->get_tien_phat_mat();
        tinh_tong_tien_phat();
        break;
    }
    default: {
        break;
    }
    }
}

void phieu_tra_sach::tinh_tong_tien_phat(){
    long long tong_tien_phat = tien_phat_1 + tien_phat_2;
    ui->tong_phi_phat->setText(QString::fromStdString(tien_te_vnd(tong_tien_phat)) + " VND");
}

void phieu_tra_sach::closeEvent(QCloseEvent *event){
    emit tra_sach_thanh_cong();
    QMainWindow::closeEvent(event);
}
