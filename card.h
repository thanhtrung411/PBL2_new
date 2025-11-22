#pragma once
#include "book.h"
#include <QFrame>
#include <iostream>
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
    QLabel* imageLabel{};
    QLabel* titleLabel{};
    QLabel* Auth_label{};
    QLabel* btnBorrowed{};
    QLabel* btnRemove{};
    book b;
    QPixmap loadScaled(const QString& path, const QSize& toSize) const;
};

class ProductCard_Tim_kiem : public QFrame {
    Q_OBJECT
public:
    explicit ProductCard_Tim_kiem(const book& b,
                         QWidget* parent = nullptr);
    void set_ID (book set_book){
        b = set_book;
    }
signals:
    void clicked(book b);
protected:
    //bool eventFilter(QObject* obj, QEvent* ev) override;
    //void mousePressEvent(QMouseEvent* e) override;
    //void enterEvent(QEnterEvent* e) override;
    //void leaveEvent(QEvent* e) override;
private:
    QLabel* imageLabel{};
    QLabel* titleLabel{};
    QLabel* Auth_label{};
    QLabel* btnBorrowed{};
    QLabel* btnRemove{};
    book b;
    QPixmap loadScaled(const QString& path, const QSize& toSize) const;
};
