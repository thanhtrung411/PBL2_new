#ifndef INFO_USER_H
#define INFO_USER_H
#include "accout.h"

#include <QMainWindow>

namespace Ui {
class info_user;
}

class info_user : public QMainWindow
{   
    accout acc_info;
    Q_OBJECT

public:
    explicit info_user(accout ac, QWidget *parent = nullptr);
    ~info_user();

private slots:
    void on_luu_thong_tin_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::info_user *ui;
    void set_info_user();
    void set_anh_dai_dien();
    QPixmap load_image_pro(const QString &path, const QSize &targetSize, int radius, bool cropToFill);
};

#endif // INFO_USER_H
