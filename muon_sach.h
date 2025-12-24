#ifndef MUON_SACH_H
#define MUON_SACH_H

#include <QMainWindow>
#include "borrow.h"
#include "my_time.h"


namespace Ui {
class muon_sach;
}

class muon_sach : public QMainWindow
{
    bool is_show_ban_sao = false;
    bool is_show_xu_ly_muon_sach = false;
    Q_OBJECT

public:
    explicit muon_sach(borrow &borrow_inf,QWidget *parent = nullptr);
    ~muon_sach();
    void set_up_borrow_info();
    void set_up_xu_ly_muon_sach();
    my_time get_ngay_muon();
    my_time get_ngay_phai_tra();

private slots:
    void on_doc_gia_currentTextChanged(const QString &arg1);

    void on_ten_sach_currentTextChanged(const QString &arg1);

    void on_muon_sach_button_clicked();

    void on_doc_gia_activated(int index);

signals:
    void muon_sach_thanh_cong();

private:
    Ui::muon_sach *ui;
    borrow borrow_info;
    void them_doc_gia_muon();
    void them_sach();
    void them_ban_sao(long long book_id);
    void them_ngay_muon_ngay_tra();
    void set_thong_tin();
};

#endif // MUON_SACH_H
