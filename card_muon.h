#pragma once
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <iostream>
using namespace std;
class card_muon : public QWidget{
    Q_OBJECT
public:
    explicit card_muon(const string& t1 = {},
                       const string& t2 = {},
                       const string& t3 = {},
                       const QString& btnText = "Action",
                       QWidget* parent = nullptr);
    void set_text(const string& t1, const string& t2, const string& t3);
    void setButtonText(const string& text);
    QLabel* label1() const { return m_lb1; }
    QLabel* label2() const { return m_lb2; }
    QLabel* label3() const { return m_lb3; }
    QPushButton* button() const { return m_btn; }
signals:
    void button_clicked();
private:
    QLabel* m_lb1 {nullptr};
    QLabel* m_lb2 {nullptr};
    QLabel* m_lb3 {nullptr};
    QPushButton* m_btn {nullptr};
};
