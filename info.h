#ifndef INFO_H
#define INFO_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class info;
}

class info : public QMainWindow
{
    Q_OBJECT

public:
    explicit info(QWidget *parent = nullptr);
    ~info();

private slots:

    void on_quyen_quan_tri_clicked();

    void on_tu_sach_cua_toi_clicked();

    void on_lich_su_hoat_dong_clicked();

    void on_ho_so_ca_nhan_clicked();

private:
    Ui::info *ui;
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // INFO_H
