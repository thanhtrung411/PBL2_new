#include "card_muon.h"
#include "global.h"
#include "working.h"

card_muon::card_muon(const string& t1,
                     const string& t2,
                     const string& t3,
                     const QString& btnText,
                     QWidget* parent)
    : QWidget(parent)
{
    auto* h = new QHBoxLayout(this);
    h->setContentsMargins(0, 0, 0, 0);
    h->setSpacing(0);
    QString tqs1 = QString::fromStdString(t1);
    QString tqs2 = QString::fromStdString(t2);
    QString tqs3 = QString::fromStdString(t3);
    m_lb1 = new QLabel(tqs1, this);
    m_lb1->setStyleSheet(R"(
        border: 2px solid rgb(69, 104, 173);
    )");
    m_lb1->setFixedSize(125,32);
    m_lb1->setAlignment(Qt::AlignCenter);
    m_lb2 = new QLabel(tqs2, this);
    m_lb2->setStyleSheet(R"(
        border: 2px solid rgb(69, 104, 173);
    )");
    m_lb3 = new QLabel(tqs3, this);
    m_lb3->setStyleSheet(R"(
        border: 2px solid rgb(69, 104, 173);
    )");
    m_lb3->setFixedSize(100,32);
    m_lb3->setAlignment(Qt::AlignCenter);
    m_btn = new QPushButton(btnText, this);
    m_btn->setStyleSheet(R"(
        border: 2px solid rgb(69, 104, 173);
    )");
    m_btn->setFixedSize(QSize(105,32));
    m_btn->setCursor(Qt::PointingHandCursor);
    m_btn->setIcon(QIcon(":/icons/icons_/borrow.png"));
    h->addWidget(m_lb1);
    h->addWidget(m_lb2);
    h->addWidget(m_lb3);
    h->addWidget(m_btn);
    connect(m_btn, &QPushButton::clicked, this, [this](bool){
        qDebug() << "Run muon sach..";
        if (is_sign_in){
            my_time t;
            t.set_time_now();
            string time_now_ = t.get_time();
            working::muon_sach(m_lb1->text().toUtf8().toStdString(), acc_sign_in.getAccout_id(), time_now_, "15");
            box_thong_bao("Mượn sách thành công ! Vui lòng đến thư viện để nhận sách.");
        }
        else{

        }
    });

}
void card_muon::set_text(const string& t1, const string& t2, const string& t3) {
    QString tqs1 = QString::fromStdString(t1);
    QString tqs2 = QString::fromStdString(t2);
    QString tqs3 = QString::fromStdString(t3);
    m_lb1->setText(tqs1);
    m_lb2->setText(tqs2);
    m_lb3->setText(tqs3);
}
void card_muon::setButtonText(const string& text) {
    QString tqs = QString::fromStdString(text);
    m_btn->setText(tqs);
}
