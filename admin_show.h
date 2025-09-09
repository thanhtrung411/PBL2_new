#ifndef ADMIN_SHOW_H
#define ADMIN_SHOW_H

#include <QMainWindow>

namespace Ui {
class admin_show;
}

class admin_show : public QMainWindow
{
    Q_OBJECT

public:
    explicit admin_show(QWidget *parent = nullptr);
    ~admin_show();

private:
    Ui::admin_show *ui_3;
};

#endif // ADMIN_SHOW_H
