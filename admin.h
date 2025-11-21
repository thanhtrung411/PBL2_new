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

private:
    Ui::admin *ui;
    void set_thong_ke();
    void hien_thi_thong_ke();

    QChartView* createLuotMuonChart();
    QChartView* createPhanboTheLoaiChart();

    void can_chinh_table(QTableWidget *table);
    void remove_table(QTableWidget *table);
    void add_book_to_table(QTableWidget *table, book *b);
    void add_book_(BST_Book& Book);

    QTableWidgetItem* makeCheckItem(bool value);
    QWidget* createStatusWidget(bool isOnline, bool isDownloadable);
};

#endif // ADMIN_H
