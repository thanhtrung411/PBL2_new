#ifndef INFO_H
#define INFO_H

#include <QMainWindow>
#include <QCloseEvent>

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

private:
    Ui::info *ui;
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // INFO_H
