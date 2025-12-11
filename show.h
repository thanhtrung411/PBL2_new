#ifndef SHOW_H
#define SHOW_H

#include <QMainWindow>

namespace Ui {
class show;
}

class show : public QMainWindow
{
    Q_OBJECT

public:
    explicit show(QWidget *parent = nullptr);
    ~show();

private:
    Ui::show *ui;
};

#endif // SHOW_H
