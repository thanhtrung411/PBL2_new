#ifndef INFO_H
#define INFO_H
#include "tree.h"
#include "history.h"
#include "global.h"
#include "settings_file.h"
#include "my_string.h"
#include "library.h"
#include "borrow.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QTableWidget>

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

    void onXoaDatSachClicked();

    void onGiaHanMuonSachClicked();

    void on_luu_thong_tin_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_dang_xuat_clicked();

private:
    Library library_;
    Ui::info *ui;
    void set_anh_dai_dien();
    void tim_sach_yeu_thich(BST_Book &b);
    void remove_table(QTableWidget *table);
    void resize_bang();
    void set_bang_dat_sach();
    void set_muon_sach_clicked();
    void reload_muon_sach_table();
    void set_tra_sach_clicked();
    void reload_tra_sach_table();
    void set_yeu_thich_clicked();
    void lay_sach_yeu_thich();
    void reload_yeu_thich_table();
    void hien_thi_sach(book b);
    void reload_lich_su_hoat_dong_table();
    void set_thong_tin_ca_nhan();
    QPixmap load_image_pro(const QString &path, const QSize &targetSize, int radius = 0, bool cropToFill = true);
    QWidget* createTenSachWidget(const long long &id,const string &ten_sach, const string &tac_gia);
    QWidget* createTinhTrangWidget(StatusType trang_thai, int days);
    QWidget* createNutXoaWidget(long long id_book, long long id_borrow);
    QWidget* createNutGiaHanWidget(long long id_book, long long id_borrow);
    QWidget* createTinhTrangTraSachWidget(TinhTrangsach tinh_trang, long long id);
    QWidget* createActionLichSuWidget(ActionType action_type);

protected:
    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // INFO_H
