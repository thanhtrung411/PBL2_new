#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QWidget>
#include <QTableWidget>
#include <QToolTip>
#include <QPoint>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>

#include "book.h"
#include "tree.h"

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

private:
    Ui::admin *ui;
    void set_thong_ke();
    void hien_thi_thong_ke();
    void cau_hinh_dat_sach();
    void cau_hinh_muon_sach();
    void cau_hinh_tra_sach();

    void hien_thi_sach_dat(BST_Borrow &b);
    void hien_thi_sach_muon(BST_Borrow &b);
    void hien_thi_sach_tra(BST_Borrow &b);

    QChartView* createLuotMuonChart();
    QChartView* createPhanboTheLoaiChart();

    void can_chinh_table(QTableWidget *table);
    void remove_table(QTableWidget *table);
    void add_book_to_table(QTableWidget *table, book *b);
    void add_book_(BST_Book& Book);

    QTableWidgetItem* makeCheckItem(bool value);
    QWidget* createStatusWidget(bool isOnline, bool isDownloadable);
    QWidget* createStatusDatWidget(StatusType trang_thai, int days);
    QWidget* createNutDatWidget(StatusType trang_thai,long long id);
    QWidget* createNutMuonWidget(StatusType trang_thai,long long id);
    QWidget* createTinhTrangWidget(TinhTrangsach tinh_trang,long long id);
    QWidget* createNutXemTraWidget(long long id);

};

#endif // ADMIN_H
