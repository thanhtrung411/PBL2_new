#include "card.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QStyle>

namespace {
// Kích thước card cố định (bạn chỉnh tùy ý)
constexpr int CARD_W = 180;
constexpr int CARD_H = 265;

// Lề trái/phải = X, lề dưới cũng dùng X cho đẹp
constexpr int X = 0;             // hai bên
constexpr int Z = 0;             // khoảng cách từ mép trên tới ảnh
// Ảnh theo tỉ lệ 4:5 (width:height)
constexpr int IMG_W_RATIO = 4;
constexpr int IMG_H_RATIO = 5;
}

ProductCard::ProductCard(const QString& imagePath,
                         const QString& title,
                         QWidget* parent)
    : QFrame(parent)
{
    setObjectName("ProductCard");
    setFixedSize(CARD_W, CARD_H);

    // Style gọn cho card (bạn có thể đưa ra QSS ngoài app)
    setStyleSheet(R"(
        #ProductCard {
            background:#fff;
            border:1px solid #e0e2eb;
            border-radius:12px;
        }
        #ProductCard QLabel[role="title"] {
            color:#0f172a;
        }
        #ProductCard QPushButton {
            background:#ffffff;
            color:#4568ad;
            border:2px solid #4568ad;
            border-radius:8px;
            padding:6px 8px;
        }
        #ProductCard QPushButton:hover   { background:#e9ecf5; }
        #ProductCard QPushButton:pressed { background:#d6d8e0; }
    )");

    // (Tuỳ chọn) đổ bóng nhẹ cho card
    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(16);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0,0,0,50));
    setGraphicsEffect(shadow);

    // ========== Layout tổng ==========
    auto v = new QVBoxLayout(this);
    v->setContentsMargins(X, Z, X, X);
    v->setSpacing(10);

    // Tính kích thước ảnh theo tỉ lệ 4:5
    const int imgW = CARD_W - 2*X;
    const int imgH = imgW * IMG_H_RATIO / IMG_W_RATIO;

    // Ảnh
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(imgW, imgH);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setPixmap(loadScaled(imagePath, imageLabel->size()));
    v->addWidget(imageLabel);

    // Tiêu đề (tự xuống dòng)
    titleLabel = new QLabel(title, this);
    titleLabel->setProperty("role", "title");
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    // Giới hạn cao vừa phải để tổng chiều cao không vượt CARD_H
    titleLabel->setMinimumHeight(48);
    titleLabel->setMaximumHeight(72);
    v->addWidget(titleLabel);

    // Hàng nút dưới cùng
    auto h = new QHBoxLayout();
    h->setSpacing(8);

    btnBorrowed = new QPushButton(QStringLiteral("Đã mượn"), this);
    btnRemove   = new QPushButton(QStringLiteral("Gỡ đơn"),  this);

    btnBorrowed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnRemove->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    h->addWidget(btnBorrowed);
    h->addWidget(btnRemove);
    v->addLayout(h);
}

QPixmap ProductCard::loadScaled(const QString& path, const QSize& toSize) const
{
    QPixmap pm(path);
    if (pm.isNull()) {
        // placeholder nếu không tìm thấy ảnh
        QPixmap ph(toSize);
        ph.fill(Qt::lightGray);
        return ph;
    }
    return pm.scaled(toSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}
