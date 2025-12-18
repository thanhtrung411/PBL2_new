#pragma once
#include "book.h"
#include <QFrame>
#include <iostream>
#include <QFutureWatcher>
#include <QtConcurrent>
using namespace std;

class QLabel;
class QPushButton;

class ProductCard : public QFrame {
    Q_OBJECT
public:
    explicit ProductCard(const book& b,
                         QWidget* parent = nullptr);
    void set_ID (book set_book){
        b = set_book;
    }
signals:
    void clicked(book b);
protected:
    bool eventFilter(QObject* obj, QEvent* ev) override;
    void mousePressEvent(QMouseEvent* e) override;
    void enterEvent(QEnterEvent* e) override;
    void leaveEvent(QEvent* e) override;
private:
    QFutureWatcher<QPixmap> watcher;
    QLabel* imageLabel{};
    QLabel* titleLabel{};
    QLabel* Auth_label{};
    QLabel* btnBorrowed{};
    QLabel* btnRemove{};
    book b;
    static QPixmap loadScaled(const QString& path, const QSize& physicalSize, int radius);
private slots:
    void onImageLoaded();
};