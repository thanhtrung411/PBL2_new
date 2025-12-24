#ifndef INFO_USER_H
#define INFO_USER_H
#include "Account.h"

#include <QMainWindow>

namespace Ui {
class info_user;
}

class info_user : public QMainWindow
{   
    Account acc_info;
    Q_OBJECT

public:
    explicit info_user(Account ac, QWidget *parent = nullptr);
    ~info_user();

private slots:
    void on_luu_thong_tin_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_khoa_tai_khoan_clicked();

    void on_mo_khoa_tai_khoan_clicked();

    void on_khoi_phuc_diem_clicked();

private:
    Ui::info_user *ui;
    void set_info_user();
    void set_anh_dai_dien();
    void set_locker();
    QPixmap load_image_pro(const QString &path, const QSize &targetSize, int radius, bool cropToFill);
};

#endif // INFO_USER_H
