#include "info.h"
#include "ui_info.h"
#include "admin_show.h"

info::info(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::info)
{
    ui->setupUi(this);
}

info::~info()
{
    delete ui;
}

void info::on_quyen_quan_tri_clicked()
{
    auto win = new admin_show(this);
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

