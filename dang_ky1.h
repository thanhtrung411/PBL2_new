#ifndef DANG_KY1_H
#define DANG_KY1_H

#include <QDialog>

namespace Ui {
class dang_ky1;
}

class dang_ky1 : public QDialog
{
    Q_OBJECT

public:
    explicit dang_ky1(QWidget *parent = nullptr);
    ~dang_ky1();

private:
    Ui::dang_ky1 *ui;
};

#endif // DANG_KY1_H
