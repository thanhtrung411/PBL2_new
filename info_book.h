#ifndef INFO_BOOK_H
#define INFO_BOOK_H

#include <QMainWindow>
#include "book.h"

namespace Ui {
class info_book;
}

class info_book : public QMainWindow
{
    Q_OBJECT

public:
    explicit info_book(const book &book_inf, QWidget *parent = nullptr);
    ~info_book();

private:
    Ui::info_book *ui;
    const book &book_info;
    void displayBookInfo();
    QPixmap loadScaled(const QString& path, const QSize& physicalSize, int radius);
    void set_up_anh();
};

#endif // INFO_BOOK_H
