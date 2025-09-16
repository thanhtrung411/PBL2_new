#pragma once
#include <QFrame>

class QLabel;
class QPushButton;

class ProductCard : public QFrame {
    Q_OBJECT
public:
    explicit ProductCard(const QString& imagePath,
                         const QString& title,
                         QWidget* parent = nullptr);

private:
    QLabel* imageLabel{};
    QLabel* titleLabel{};
    QPushButton* btnBorrowed{};
    QPushButton* btnRemove{};

    QPixmap loadScaled(const QString& path, const QSize& toSize) const;
};
