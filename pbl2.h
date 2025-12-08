#ifndef PBL2_H
#define PBL2_H
#include <iostream>
#include <algorithm>
#include <QMainWindow>
#include <QGridLayout>
#include <QScrollArea>
#include <QDir>
#include <QDebug>
#include "card.h"
#include "book.h"
#include "tree.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class pbl2;
}
QT_END_NAMESPACE
class pbl2 : public QMainWindow
{
    Q_OBJECT

public:
    pbl2(QWidget *parent = nullptr);
    ~pbl2();
public slots:
    void sign_in();
private slots:
    void on_dang_ky_button_clicked();
    void on_dang_nhap_button_clicked();
    void on_pushButton_clicked();
    void on_chi_tiet_button_clicked();
    void on_trich_dan_button_clicked();
    void on_the_loai_list_layout_currentIndexChanged(int index);

    void on_chuyen_nganh_list_layout_currentIndexChanged(int index);

    void on_tim_kiem_button_clicked();

    void on_yeu_thich_toggled(bool checked);

    void on_dat_lai_button_clicked();


private:
    Ui::pbl2 *ui;
    unsigned int random_seed;
    int page_previous = 0;
    book current_selected_book;
    void set_tong_sach_tong_muon_tong_dat_number();
    void set_scroll(QScrollArea* p, int width);
    void show_info_sach(book& b);
    void Reload_show_info(book& b);
    void set_up(BST_Book& book_data_);
    template<typename Tree>
    void Reload(Tree &book_data_);
    QPixmap loadScaled(const QString& path, const QSize& physicalSize, int radius);
    void clear_layout(QLayout* layout);
    template<typename Tree>
    void set_up_card_moi(Tree &b, QGridLayout* path_link);
    template<typename Tree>
    void set_up_card_goi_y(Tree &b, QGridLayout* path_link);
    void set_up_top_doc_nhieu_nhat();
    void set_up_top_muon_nhieu_nhat();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // PBL2_H
