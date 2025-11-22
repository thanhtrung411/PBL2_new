#include "info.h"
#include "ui_info.h"
#include "admin_show.h"
#include "admin.h"

info::info(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::info)
{
    ui->setupUi(this);
    // connect(ui-> pushButton_8 , &QPushButton::clicked, [=](){
    //     ui->stackedWidget->setCurrentIndex(0);
    // });

    // connect(ui->pushButton_9, &QPushButton::clicked, [=](){
    //     ui->stackedWidget->setCurrentIndex(1);
    // });

    // connect(ui->pushButton_10, &QPushButton::clicked, [=](){
    //     ui->stackedWidget->setCurrentIndex(2);
    // });

}

info::~info()
{
    delete ui;
}

void info::on_quyen_quan_tri_clicked()
{
    auto win = new admin(this);
    win->setAttribute(Qt::WA_DeleteOnClose, true);
    win->show();
    this->hide();
    // Khi cửa sổ đăng ký đóng, hiển thị lại Pbl2
    /*connect(win, &dang_ky_dialog::registered, this, [this, win](const accout& user) {
        acc_sign_in = user;
        //ui->info->setCurrentIndex(1);
        //ui->user_name_layout->setText(
        //    QString::fromStdString("Xin chào " + giai_ma_str_(acc_sign_in.getAccout_Name()) + ","));
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
    });*/
}
void info::closeEvent(QCloseEvent *event)
{
    QWidget *parentWin = this->parentWidget();
    if (parentWin) {
        parentWin->show();
    }
    this->deleteLater();
    event->accept();
}



void info::on_tu_sach_cua_toi_clicked()
{
    ui->vung_hien_thi->setCurrentIndex(0);
}


void info::on_lich_su_hoat_dong_clicked()
{
    ui->vung_hien_thi->setCurrentIndex(1);
}


void info::on_ho_so_ca_nhan_clicked()
{
    ui->vung_hien_thi->setCurrentIndex(2);
}

