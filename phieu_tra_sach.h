#ifndef PHIEU_TRA_SACH_H
#define PHIEU_TRA_SACH_H

#include <QMainWindow>
#include "tree.h"

namespace Ui {
class phieu_tra_sach;
}

class phieu_tra_sach : public QMainWindow
{
    Q_OBJECT
protected slots:
    void closeEvent(QCloseEvent *event) override;
public:
    explicit phieu_tra_sach(QWidget *parent = nullptr);
    ~phieu_tra_sach();
signals:
    void tra_sach_thanh_cong();
private slots:
    void on_xac_nhan_clicked();
    void on_tinh_trang_sach_currentIndexChanged(int index);
    void on_phieu_muon_currentIndexChanged(int index);

private:
    BST_Borrow borrow_can_tra;
    long long tien_phat_1 = 0;
    long long tien_phat_2 = 0;
    Ui::phieu_tra_sach *ui;
    void load_borrow_can_tra();
    void hien_thi_borrow_can_tra();
    void tinh_tong_tien_phat();
};

#endif // PHIEU_TRA_SACH_H
