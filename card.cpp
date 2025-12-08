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
#include <QFont>
#include <QSize>
#include <QPainter>
#include <QPainterPath>
#include <QFontMetrics>
#include <QApplication>
#include <QScreen>

namespace {
    // Kích thước Card
    constexpr int CARD_W = 180;
    // Padding (lề trong)
    constexpr int PADDING = 10;
    // Tỉ lệ ảnh 4:5
    constexpr double IMG_RATIO = 5.0 / 4.0; 
}

ProductCard::ProductCard(const book& b, QWidget* parent)
    : QFrame(parent)
{
    this->b = b;
    setObjectName("ProductCard");
    
    // --- 1. QUAN TRỌNG: CHỈ FIX CHIỀU RỘNG, KHÔNG FIX CHIỀU CAO ---
    // Để layout tự tính chiều cao, tránh việc chữ đè lên ảnh
    setFixedWidth(CARD_W);
    // setFixedSize(...) -> XÓA DÒNG NÀY ĐI

    // --- 2. STYLESHEET ---
    setStyleSheet(R"(
        #ProductCard {
            background-color: #ffffff;
            border-radius: 12px;
            border: 1px solid #d0d0d0;
        }
        #ProductCard:hover {
            border: 1px solid #3b82f6;
            background-color: #f8fafc;
        }
        QLabel {
            background-color: transparent; /* Đảm bảo nền label trong suốt */
            border: none;
        }
        QLabel[role="title"] {
            color: #1e293b;
            font-family: 'Segoe UI', sans-serif;
            font-weight: 700;
            font-size: 14px;
            margin-top: 6px;
        }
        QLabel[role="author"] {
            color: #64748b;
            font-family: 'Segoe UI', sans-serif;
            font-size: 12px;
            margin-bottom: 4px;
        }
        QLabel[role="status"] {
            background-color: #dbeafe;
            color: #1d4ed8;
            border-radius: 4px;
            padding: 2px 8px;
            font-weight: 600;
            font-size: 10px;
        }
    )");

    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 20));
    setGraphicsEffect(shadow);

    // --- 3. LAYOUT ---
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(PADDING, PADDING, PADDING, PADDING);
    mainLayout->setSpacing(4); 
    
    // Dòng này giúp Card tự động co lại vừa khít với nội dung bên trong
    mainLayout->setSizeConstraint(QLayout::SetFixedSize); 

    // === XỬ LÝ ẢNH (GIỮ NGUYÊN CODE NÉT + ASYNC - ĐA LUỒNG) ===
    int logicalW = CARD_W - (2 * PADDING);
    int logicalH = static_cast<int>(logicalW * IMG_RATIO);
    QSize logicalSize(logicalW, logicalH);

    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(logicalSize); // Cố định khung ảnh để không bị layout ép nhỏ
    imageLabel->setAlignment(Qt::AlignCenter);
    // Quan trọng: Set policy để ảnh không bị co giãn linh tinh
    imageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    imageLabel->setScaledContents(true);
    imageLabel->setStyleSheet("background-color: #f1f5f9; border-radius: 12px;");
    mainLayout->addWidget(imageLabel);

    // === CÁC PHẦN TEXT ===
    QString titleText = QString::fromUtf8(b.get_Name().c_str());
    titleLabel = new QLabel(titleText, this);
    titleLabel->setProperty("role", "title");
    titleLabel->setWordWrap(true);
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    // Giới hạn chiều cao text title (tối đa 2 dòng)
    QFont f = titleLabel->font();
    f.setFamily("Segoe UI");
    f.setPixelSize(14);
    f.setBold(true);
    titleLabel->setFont(f);

    QFontMetrics fmTitle(titleLabel->font());
    int lineHeight = fmTitle.lineSpacing();
    titleLabel->setFixedHeight(lineHeight * 2 + 10);// +10 để có chút padding
    titleLabel->setFixedWidth(logicalW);
    QString elidedTitle = fmTitle.elidedText(titleText, Qt::ElideRight, logicalW*2 - 35);
    titleLabel->setText(elidedTitle);
    mainLayout->addWidget(titleLabel);

    QString authText = QString::fromUtf8(b.get_Author().c_str());
    Auth_label = new QLabel(authText, this);
    Auth_label->setProperty("role", "author");
    Auth_label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    QFontMetrics fmAuth(Auth_label->font());
    QString elidedAuth = fmAuth.elidedText(authText, Qt::ElideRight, logicalW);
    Auth_label->setText(elidedAuth);
    // Tác giả chỉ 1 dòng thì không cần fixHeight, để nó tự nhiên
    mainLayout->addWidget(Auth_label);

    // Spacer đẩy footer xuống
    mainLayout->addStretch();

    // Footer
    auto footerLayout = new QHBoxLayout();
    footerLayout->setSpacing(0);
    footerLayout->setContentsMargins(0, 0, 0, 0);
    btnBorrowed = new QLabel("MỚI", this); 
    btnBorrowed->setProperty("role", "status"); 
    btnBorrowed->setAlignment(Qt::AlignCenter);
    btnBorrowed->setFixedSize(40, 20);
    footerLayout->addWidget(btnBorrowed);
    footerLayout->addStretch();
    mainLayout->addLayout(footerLayout);

    setCursor(Qt::PointingHandCursor);
    imageLabel->installEventFilter(this);
    titleLabel->installEventFilter(this);

    // --- 4. LOAD ẢNH ASYNC ---
    qreal dpr = QGuiApplication::primaryScreen()->devicePixelRatio();
    QSize physicalSize = logicalSize * dpr;
    int physicalRadius = 12 * dpr;

    QString imgPath = QString::fromUtf8(b.get_Link_png().c_str());
    connect(&watcher, &QFutureWatcher<QPixmap>::finished, this, &ProductCard::onImageLoaded);
    QFuture<QPixmap> future = QtConcurrent::run(
        &ProductCard::loadScaled, // Gọi hàm static loadScaled
        imgPath, physicalSize, physicalRadius // Truyền tham số vào
    );
    watcher.setFuture(future);
}

void ProductCard::onImageLoaded() {
    QPixmap result = watcher.result();
    if (!result.isNull()) {
        // Lấy lại DPR màn hình hiện tại để set cho ảnh (quan trọng để ảnh nét)
        qreal dpr = QGuiApplication::primaryScreen()->devicePixelRatio();
        result.setDevicePixelRatio(dpr);

        imageLabel->setPixmap(result);
        // Xóa màu nền xám đi
        imageLabel->setStyleSheet("background-color: transparent; border: none;");
    }
}

void ProductCard::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) emit clicked(b);
    QFrame::mousePressEvent(e);
}
bool ProductCard::eventFilter(QObject* obj, QEvent* ev) {
    if (ev->type() == QEvent::MouseButtonPress) {
        auto *me = static_cast<QMouseEvent*>(ev);
        if (me->button() == Qt::LeftButton) { emit clicked(b); return true; }
    }
    return QFrame::eventFilter(obj, ev);
}
void ProductCard::enterEvent(QEnterEvent* e)  { QFrame::enterEvent(e); }
void ProductCard::leaveEvent(QEvent* e)       { QFrame::leaveEvent(e); }

// ... (Giữ nguyên hàm loadScaled mới nhất) ...
QPixmap ProductCard::loadScaled(const QString& path, const QSize& physicalSize, int radius)
{
    QPixmap src(path);
    if (src.isNull()) {
        // Thử load ảnh mặc định
        src = QPixmap("../../png_background/default_book.png");
        if (src.isNull()) {
            // Nếu ảnh mặc định cũng không có, dùng màu nền
            QPixmap ph(physicalSize);
            ph.fill(QColor("#f1f5f9"));
            return ph;
        }
    }
    QPixmap scaled = src.scaled(physicalSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    int x = (scaled.width() - physicalSize.width()) / 2;
    int y = (scaled.height() - physicalSize.height()) / 2;
    QPixmap cropped = scaled.copy(x, y, physicalSize.width(), physicalSize.height());

    QPixmap dest(physicalSize);
    dest.fill(Qt::transparent);

    QPainter painter(&dest);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QPainterPath pathObj;
    pathObj.addRoundedRect(0, 0, physicalSize.width(), physicalSize.height(), radius, radius);
    
    painter.setClipPath(pathObj);
    painter.drawPixmap(0, 0, cropped);

    // Viền mờ
    painter.setClipping(false);
    painter.setPen(QPen(QColor(0, 0, 0, 20), 1)); 
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(0, 0, physicalSize.width()-1, physicalSize.height()-1, radius, radius);

    return dest;
}
