#ifndef PBL2_H
#define PBL2_H
#include <iostream>
#include <QMainWindow>
#include <QGridLayout>
#include <QScrollArea>
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

    void on_quyen_quan_tri_clicked();

    void set_scroll(QScrollArea* p, int width);

    void set_up_card(BST_Book &b,QGridLayout* path_link);

    void show_info_sach(book& b);

    void Reload();

    QPixmap loadScaled(const QString& path, const QSize& toSize) const;

    void on_pushButton_clicked();

    void on_chi_tiet_button_clicked();

    void on_trich_dan_button_clicked();

private:
    Ui::pbl2 *ui;
};
#endif // PBL2_H
