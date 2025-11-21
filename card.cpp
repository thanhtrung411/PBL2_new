#include "card.h"
#include "book.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QStyle>
#include <QMouseEvent>
#include <QEvent>
#include <QCursor>
#include <QPainter>
#include <QPainterPath>
#include <QLabel>
#include <QFontMetrics>
#include <iostream>
using namespace std;

namespace {
//kich thuoc card
constexpr int CARD_W = 150;
constexpr int CARD_H = 265;

//trai/phai: x
constexpr int X = 3;
constexpr int Z = 3;  // tren
//ti le anh
constexpr int IMG_W_RATIO = 4;
constexpr int IMG_H_RATIO = 5;

constexpr int CARD_MUON_H = 200;
constexpr int IMG_W = 140;
constexpr int IMG_H = 180;


}

ProductCard::ProductCard(const book& b,
                         QWidget* parent)
    : QFrame(parent)
{
    set_ID(b);
    setObjectName("ProductCard");
    setFixedSize(CARD_W, CARD_H);
    setStyleSheet(R"(
        #ProductCard:hover {
            border:1px solid #617fb9;
        }
        #ProductCard {
            background:#fff;
        }
        #ProductCard QLabel[role="title"] {
            color:#0f172a;
        }
        #ProductCard QPushButton {
            background:#fff;
            color:#4568ad;
            border:2px solid #4568ad;
            border-radius:8px;
            padding:6px 8px;
        }
        #ProductCard QLabel {
            background:#fff;
        }
        #ProductCard QPushButton:hover   { background:#e9ecf5; }
        #ProductCard QPushButton:pressed { background:#d6d8e0; }
    )");

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
    QString imgPath =QString::fromUtf8(b.get_Link_png().c_str());
    imageLabel->setPixmap(loadScaled(imgPath, imageLabel->size()));
    v->addWidget(imageLabel);

    // Tieu de
    QString title_ = QString::fromUtf8(b.get_Name().c_str());
    titleLabel = new QLabel(title_, this);
    titleLabel->setFixedWidth(CARD_W-5);
    QFontMetrics fmTitle(titleLabel->font());
    QString elided_title = fmTitle.elidedText(title_, Qt::ElideRight, titleLabel->width()*2 - 10);
    titleLabel->setText(elided_title);
    int line = fmTitle.lineSpacing();
    titleLabel->setProperty("role", "title");
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // Gioi han chieu cao
    titleLabel->setFixedHeight(line*2);
    v->addWidget(titleLabel);
    QString Auth = QString::fromUtf8(b.get_Author().c_str());
    Auth_label = new QLabel (Auth, this);
    Auth_label->setFixedWidth(CARD_W-10);
    QFontMetrics fmAuthor(Auth_label->font());
    QString elided_Author = fmAuthor.elidedText(Auth, Qt::ElideRight, Auth_label->width());
    Auth_label->setText(elided_Author);
    Auth_label->setProperty("role", "title");
    Auth_label->setWordWrap(true);
    Auth_label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    Auth_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    Auth_label->setFixedHeight(line);
    v->addWidget(Auth_label);
    // Hang duoi cung
    auto h = new QHBoxLayout();
    h->setSpacing(0);

    btnBorrowed = new QLabel(QStringLiteral("Sách mới"), this);
    btnRemove   = new QLabel(QStringLiteral(""),  this);

    btnBorrowed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btnRemove->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    h->addWidget(btnBorrowed);
    h->addWidget(btnRemove);
    v->addLayout(h);
    setCursor(Qt::PointingHandCursor);
    imageLabel->installEventFilter(this);
    titleLabel->installEventFilter(this);
    btnBorrowed->installEventFilter(this);
    btnRemove->installEventFilter(this);
}

void ProductCard::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) emit clicked(b);
    QFrame::mousePressEvent(e);
}

bool ProductCard::eventFilter(QObject* obj, QEvent* ev) {
    if (ev->type() == QEvent::MouseButtonPress) {
        auto *me = static_cast<QMouseEvent*>(ev);
        if (me->button() == Qt::LeftButton) {
            emit clicked(b);
            return true;                 // đã xử lý
        }
    }
    return QFrame::eventFilter(obj, ev);
}

void ProductCard::enterEvent(QEnterEvent* e)  { QFrame::enterEvent(e); }
void ProductCard::leaveEvent(QEvent* e)       { QFrame::leaveEvent(e); }

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



ProductCard_Tim_kiem::ProductCard_Tim_kiem(const book& b,
                         QWidget* parent)
    : QFrame(parent)
{
    set_ID(b);
    setObjectName("ProductCard_tim_kiem");
    setFixedSize(CARD_W, CARD_H);
    setStyleSheet(R"(
        #ProductCard_tim_kiem:hover {
            border:1px solid #617fb9;
        }
        #ProductCard_tim_kiem {
            background:#fff;
        }
        #ProductCard_tim_kiem QLabel[role="title"] {
            color:#0f172a;
        }
        #ProductCard_tim_kiem QPushButton {
            background:#fff;
            color:#4568ad;
            border:2px solid #4568ad;
            border-radius:8px;
            padding:6px 8px;
        }
        #ProductCard_tim_kiem QLabel {
            background:#fff;
        }
        #ProductCard_tim_kiem QPushButton:hover   { background:#e9ecf5; }
        #ProductCard_tim_kiem QPushButton:pressed { background:#d6d8e0; }
    )");

    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(16);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0,0,0,50));
    setGraphicsEffect(shadow);

    // ========== Layout tổng ==========
    auto hMain = new QHBoxLayout(this);
    hMain->setContentsMargins(X, Z, X, X);
    hMain->setSpacing(6);

    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(IMG_W, IMG_H);
    imageLabel->setAlignment(Qt::AlignCenter);
    QString imgPath =QString::fromUtf8(b.get_Link_png().c_str());
    imageLabel->setPixmap(loadScaled(imgPath, imageLabel->size()));
    hMain->addWidget(imageLabel);

    auto VInfo = new QVBoxLayout();
    VInfo->setSpacing(4);

    titleLabel = new QLabel(QString::fromUtf8(b.get_Name().c_str()));
    titleLabel->setProperty("role","tittle");
    titleLabel->setWordWrap(true);
    titleLabel->setMaximumHeight(QFontMetrics(titleLabel->font()).lineSpacing() * 2);
    VInfo->addWidget(titleLabel);

}

QPixmap ProductCard_Tim_kiem::loadScaled(const QString& path, const QSize& toSize) const
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
