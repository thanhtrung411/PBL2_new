#ifndef PBL2_H
#define PBL2_H

#include <QMainWindow>

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

private:
    Ui::pbl2 *ui;
};
#endif // PBL2_H
