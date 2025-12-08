#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QWidget>
#include <QTableWidget>
#include <QToolTip>
#include <QPoint>
#include <QComboBox>
#include <QPixmap>
#include <QImageReader>
#include <QPainter>
#include <QPainterPath>
#include <QHeaderView>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>

#include "book.h"
#include "tree.h"
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui { class admin; }
QT_END_NAMESPACE

// Không dùng QtCharts:: trong header để tránh lỗi moc / namespace
class admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

private slots:
    void on_them_sach_button_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_sach_table_cellClicked(int row, int column);
    void on_sach_table_customContextMenuRequested(const QPoint &pos);

    void showBarToolTip(bool status, int index, QBarSet *barSet);

    void on_thong_ke_button_clicked();
    void on_dau_sach_button_clicked();
    void on_ban_sao_button_clicked();
    void on_doc_gia_button_clicked();
    void on_thu_thu_button_clicked();
    void closeEvent(QCloseEvent *event);

    void on_muon_tra_button_clicked();

    void onXuLyClicked();
    void onXacNhanClicked();
    void onXoaDatSachClicked();
    void onXemChiTietMuonClicked();
    void onGiaHanSachClicked();
    void onXemChiTietTraClicked();

    void on_dat_sach_button_clicked();

    void on_muon_sach_button_clicked();

    void on_tra_sach_button_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_tim_kiem_dat_textChanged(const QString &arg1);

    void on_nhan_tra_clicked();

    void on_phieu_tra_sach_button_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_trang_thai_tra_activated(int index);

    void on_tim_kiem_muon_textChanged(const QString &arg1);

    void on_tim_kiem_tra_textChanged(const QString &arg1);

    void on_dau_sach_currentIndexChanged(int index);

    void onXoaBanSaoClicked();

    void on_them_doc_gia_clicked();

    void on_them_thu_thu_clicked();

    void on_nhap_tu_file_clicked();

    void on_tao_phieu_muon_sach_clicked();

    void onXemThongTinUserClicked();
    
    void onXoaUserClicked();

    void on_the_loai_combo_activated(int index);

    void on_chuyen_nganh_combo_activated(int index);

    void on_tao_ban_sao_button_clicked();

    void on_user_lich_su_activated(int index);

    void on_ngay_lich_su_activated(int index);

    void on_thang_lich_su_activated(int index);

    void on_nam_lich_su_activated(int index);

    void on_lich_su_button_clicked();


    void on_cai_dat_button_clicked();

    void on_cap_nhat_cai_dat_clicked();

    void on_xuat_csv_sach_clicked();

    void on_xuat_csv_ban_sao_clicked();

    void on_xuat_csv_muon_tra_clicked();

    void on_xuat_csv_lich_su_clicked();

private:
    Ui::admin *ui;
    void reset_side_buttons_style();
    void set_anh_dai_dien();
    void set_thong_ke();
    void set_up_top_muon_nhieu_nhat();
    void set_up_top_doc_nhieu_nhat();
    void hien_thi_thong_ke();
    void cau_hinh_dat_sach();
    void cau_hinh_muon_sach();
    void cau_hinh_tra_sach();
    void cau_hinh_ban_sao();
    void cau_hinh_thu_thu();
    void cau_hinh_doc_gia();
    void cau_hinh_cai_dat();

    void hien_thi_sach_dat(BST_Borrow &b);
    void hien_thi_sach_muon(BST_Borrow &b);
    void hien_thi_sach_tra(BST_Borrow &b);
    void hien_thi_ban_sao(BST_book_copy &b);
    void hien_thi_thu_thu(BST_Accout &b);
    void hien_thi_doc_gia(BST_Accout &b);
    void hien_thi_lich_su(BST_History &b);


    void xuat_csv_dau_sach();

    QChartView* createLuotMuonChart();
    QChartView* createPhanboTheLoaiChart();
    void refresh_ngay_lich_su(int thang, int nam);
    void set_up_time_lich_su(QComboBox* ngay, QComboBox* thang, QComboBox* nam);
    void set_up_user_lich_su();
    void can_chinh_table(QTableWidget *table);
    void remove_table(QTableWidget *table);
    void add_book_to_table(QTableWidget *table, book *b);
    void add_book_(BST_Book& Book);
    QPixmap load_image_pro(const QString &path, const QSize &targetSize, int radius, bool cropToFill);
    QTableWidgetItem* makeCheckItem(bool value);
    QWidget* createStatusWidget(bool isOnline, bool isDownloadable);
    QWidget* createStatusDatWidget(StatusType trang_thai, int days);
    QWidget* createNutDatWidget(StatusType trang_thai,long long id);
    QWidget* createNutMuonWidget(StatusType trang_thai,long long id);
    QWidget* createTinhTrangWidget(TinhTrangsach tinh_trang,long long id);
    QWidget* createNutXemTraWidget(long long id);
    QWidget* createNutXoaWidget(long long id);
    QWidget* createNutThongTinUserWidget(long long user_id);
    QWidget* createActionLichSuWidget(ActionType action_type);
};

#endif // ADMIN_H
