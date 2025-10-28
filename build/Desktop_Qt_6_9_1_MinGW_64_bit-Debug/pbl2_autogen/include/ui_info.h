/********************************************************************************
** Form generated from reading UI file 'info.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFO_H
#define UI_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_info
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *thu_vien_so;
    QLabel *xin_chao;
    QLabel *label_2;
    QLabel *score;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_6;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *user_id;
    QLabel *label_10;
    QLabel *label_5;
    QLineEdit *user_name;
    QLabel *label_11;
    QLabel *label_4;
    QLineEdit *email;
    QLabel *label_12;
    QLabel *label_6;
    QLineEdit *number_call;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QLabel *label_13;
    QLabel *label_8;
    QComboBox *comboBox;
    QLabel *label_14;
    QLabel *label_9;
    QDateEdit *dateEdit;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *info)
    {
        if (info->objectName().isEmpty())
            info->setObjectName("info");
        info->resize(1250, 790);
        info->setStyleSheet(QString::fromUtf8("background-color: rgb(69, 104, 173);"));
        info->setIconSize(QSize(30, 30));
        info->setAnimated(true);
        info->setDockOptions(QMainWindow::DockOption::AllowTabbedDocks|QMainWindow::DockOption::AnimatedDocks);
        centralwidget = new QWidget(info);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_4 = new QHBoxLayout(centralwidget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        thu_vien_so = new QLabel(centralwidget);
        thu_vien_so->setObjectName("thu_vien_so");
        QFont font;
        font.setPointSize(18);
        thu_vien_so->setFont(font);
        thu_vien_so->setStyleSheet(QString::fromUtf8("color: rgb(243, 246, 255);"));

        verticalLayout->addWidget(thu_vien_so);

        xin_chao = new QLabel(centralwidget);
        xin_chao->setObjectName("xin_chao");
        xin_chao->setStyleSheet(QString::fromUtf8("color: rgb(243, 246, 255);"));

        verticalLayout->addWidget(xin_chao);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(243, 246, 255);"));

        verticalLayout->addWidget(label_2);

        score = new QLabel(centralwidget);
        score->setObjectName("score");
        score->setStyleSheet(QString::fromUtf8("color: rgb(243, 246, 255);"));

        verticalLayout->addWidget(score);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(255, 0));
        QFont font1;
        font1.setPointSize(10);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("text-align: left;\n"
"background-color: rgb(69, 104, 173);\n"
"color: rgb(243, 246, 255);"));

        verticalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QString::fromUtf8("text-align: left;\n"
"background-color: rgb(69, 104, 173);\n"
"color: rgb(243, 246, 255);"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setFont(font1);
        pushButton_4->setStyleSheet(QString::fromUtf8("text-align: left;\n"
"background-color: rgb(69, 104, 173);\n"
"color: rgb(243, 246, 255);"));

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setFont(font1);
        pushButton_5->setStyleSheet(QString::fromUtf8("text-align: left;\n"
"background-color: rgb(69, 104, 173);\n"
"color: rgb(243, 246, 255);"));

        verticalLayout->addWidget(pushButton_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton_6 = new QPushButton(centralwidget);
        pushButton_6->setObjectName("pushButton_6");
        QFont font2;
        font2.setPointSize(12);
        pushButton_6->setFont(font2);

        verticalLayout->addWidget(pushButton_6);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setFont(font1);
        stackedWidget->setStyleSheet(QString::fromUtf8("\n"
"	background-color: rgb(243, 246, 255);\n"
"\n"
"QLabel{\n"
"	color: rgb(15, 15, 15);\n"
"}"));
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_5 = new QVBoxLayout(page);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(page);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 80));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        label->setFont(font3);
        label->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(39);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(15, 0, 15, -1);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(7);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(page);
        label_3->setObjectName("label_3");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font1);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));

        verticalLayout_3->addWidget(label_3);

        user_id = new QLineEdit(page);
        user_id->setObjectName("user_id");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(user_id->sizePolicy().hasHeightForWidth());
        user_id->setSizePolicy(sizePolicy1);
        user_id->setMinimumSize(QSize(0, 35));
        user_id->setSizeIncrement(QSize(0, 0));
        user_id->setBaseSize(QSize(0, 0));
        QFont font4;
        font4.setPointSize(10);
        font4.setUnderline(false);
        user_id->setFont(font4);
        user_id->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);\n"
"border: 1px solid rgb(15, 15, 15);\n"
"border-radius: 14px;\n"
"padding-left: 12px;\n"
""));

        verticalLayout_3->addWidget(user_id);

        label_10 = new QLabel(page);
        label_10->setObjectName("label_10");

        verticalLayout_3->addWidget(label_10);

        label_5 = new QLabel(page);
        label_5->setObjectName("label_5");
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));

        verticalLayout_3->addWidget(label_5);

        user_name = new QLineEdit(page);
        user_name->setObjectName("user_name");
        sizePolicy1.setHeightForWidth(user_name->sizePolicy().hasHeightForWidth());
        user_name->setSizePolicy(sizePolicy1);
        user_name->setMinimumSize(QSize(0, 35));
        user_name->setFont(font1);
        user_name->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);\n"
"border: 1px solid rgb(15, 15, 15);\n"
"border-radius: 14px;\n"
"padding-left: 12px;"));

        verticalLayout_3->addWidget(user_name);

        label_11 = new QLabel(page);
        label_11->setObjectName("label_11");

        verticalLayout_3->addWidget(label_11);

        label_4 = new QLabel(page);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));

        verticalLayout_3->addWidget(label_4);

        email = new QLineEdit(page);
        email->setObjectName("email");
        sizePolicy1.setHeightForWidth(email->sizePolicy().hasHeightForWidth());
        email->setSizePolicy(sizePolicy1);
        email->setMinimumSize(QSize(0, 35));
        email->setFont(font1);
        email->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);\n"
"border: 1px solid rgb(15, 15, 15);\n"
"border-radius: 14px;\n"
"padding-left: 12px;"));

        verticalLayout_3->addWidget(email);

        label_12 = new QLabel(page);
        label_12->setObjectName("label_12");

        verticalLayout_3->addWidget(label_12);

        label_6 = new QLabel(page);
        label_6->setObjectName("label_6");
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setFont(font1);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));

        verticalLayout_3->addWidget(label_6);

        number_call = new QLineEdit(page);
        number_call->setObjectName("number_call");
        sizePolicy1.setHeightForWidth(number_call->sizePolicy().hasHeightForWidth());
        number_call->setSizePolicy(sizePolicy1);
        number_call->setMinimumSize(QSize(0, 35));
        number_call->setFont(font1);
        number_call->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);\n"
"border: 1px solid rgb(15, 15, 15);\n"
"border-radius: 14px;\n"
"padding-left: 12px;"));

        verticalLayout_3->addWidget(number_call);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(7);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_7 = new QLabel(page);
        label_7->setObjectName("label_7");
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setFont(font1);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));

        verticalLayout_4->addWidget(label_7);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(7);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_8 = new QPushButton(page);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setMinimumSize(QSize(0, 35));
        pushButton_8->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));

        horizontalLayout_3->addWidget(pushButton_8);

        pushButton_7 = new QPushButton(page);
        pushButton_7->setObjectName("pushButton_7");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy2);
        pushButton_7->setMinimumSize(QSize(0, 35));
        pushButton_7->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));

        horizontalLayout_3->addWidget(pushButton_7);


        verticalLayout_4->addLayout(horizontalLayout_3);

        label_13 = new QLabel(page);
        label_13->setObjectName("label_13");

        verticalLayout_4->addWidget(label_13);

        label_8 = new QLabel(page);
        label_8->setObjectName("label_8");
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setFont(font1);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));

        verticalLayout_4->addWidget(label_8);

        comboBox = new QComboBox(page);
        comboBox->setObjectName("comboBox");
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(0, 35));
        comboBox->setFont(font1);
        comboBox->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);\n"
"border: 2px solid rgb(15, 15, 15);\n"
""));

        verticalLayout_4->addWidget(comboBox);

        label_14 = new QLabel(page);
        label_14->setObjectName("label_14");

        verticalLayout_4->addWidget(label_14);

        label_9 = new QLabel(page);
        label_9->setObjectName("label_9");
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setFont(font1);
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));

        verticalLayout_4->addWidget(label_9);

        dateEdit = new QDateEdit(page);
        dateEdit->setObjectName("dateEdit");
        sizePolicy1.setHeightForWidth(dateEdit->sizePolicy().hasHeightForWidth());
        dateEdit->setSizePolicy(sizePolicy1);
        dateEdit->setMinimumSize(QSize(0, 35));
        dateEdit->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);\n"
"border: 2px solid rgb(15, 15, 15);\n"
""));

        verticalLayout_4->addWidget(dateEdit);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setStyleSheet(QString::fromUtf8("color: rgb(15, 15, 15);"));

        horizontalLayout_6->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        verticalLayout_5->setStretch(3, 1);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        verticalLayout_2->addWidget(stackedWidget);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_4->addLayout(horizontalLayout);

        info->setCentralWidget(centralwidget);
        menubar = new QMenuBar(info);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1250, 25));
        info->setMenuBar(menubar);
        statusbar = new QStatusBar(info);
        statusbar->setObjectName("statusbar");
        statusbar->setSizeGripEnabled(true);
        info->setStatusBar(statusbar);

        retranslateUi(info);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(info);
    } // setupUi

    void retranslateUi(QMainWindow *info)
    {
        info->setWindowTitle(QCoreApplication::translate("info", "MainWindow", nullptr));
        thu_vien_so->setText(QCoreApplication::translate("info", "Th\306\260 vi\341\273\207n s\341\273\221", nullptr));
        xin_chao->setText(QCoreApplication::translate("info", "Xin ch\303\240o", nullptr));
        label_2->setText(QCoreApplication::translate("info", "user_name", nullptr));
        score->setText(QCoreApplication::translate("info", "S\341\273\221 \304\221i\341\273\203m: 0", nullptr));
        pushButton->setText(QCoreApplication::translate("info", "Th\303\264ng tin c\303\241 nh\303\242n", nullptr));
        pushButton_3->setText(QCoreApplication::translate("info", "T\341\273\247 s\303\241ch c\341\273\247a t\303\264i", nullptr));
        pushButton_4->setText(QCoreApplication::translate("info", "H\341\273\215at \304\221\341\273\231ng v\303\240 t\306\260\306\241ng t\303\241c", nullptr));
        pushButton_5->setText(QCoreApplication::translate("info", "C\303\240i \304\221\341\272\267t v\303\240 b\341\272\243o m\341\272\255t", nullptr));
        pushButton_6->setText(QCoreApplication::translate("info", "\304\220\304\203ng xu\341\272\245t", nullptr));
        label->setText(QCoreApplication::translate("info", "Th\303\264ng tin c\303\241 nh\303\242n", nullptr));
        label_3->setText(QCoreApplication::translate("info", "T\303\252n \304\221\304\203ng nh\341\272\255p", nullptr));
        user_id->setText(QString());
        label_10->setText(QString());
        label_5->setText(QCoreApplication::translate("info", "H\341\273\215 v\303\240 t\303\252n", nullptr));
        label_11->setText(QString());
        label_4->setText(QCoreApplication::translate("info", "\304\220\341\273\213a ch\341\273\211 email", nullptr));
        label_12->setText(QString());
        label_6->setText(QCoreApplication::translate("info", "S\341\273\221 \304\221i\341\273\207n tho\341\272\241i", nullptr));
        label_7->setText(QCoreApplication::translate("info", "Gi\341\273\233i t\303\255nh", nullptr));
        pushButton_8->setText(QCoreApplication::translate("info", "Nam", nullptr));
        pushButton_7->setText(QCoreApplication::translate("info", "N\341\273\257", nullptr));
        label_13->setText(QString());
        label_8->setText(QCoreApplication::translate("info", "\304\220\341\273\221i t\306\260\341\273\243ng", nullptr));
        label_14->setText(QString());
        label_9->setText(QCoreApplication::translate("info", "Ng\303\240y sinh", nullptr));
        pushButton_2->setText(QCoreApplication::translate("info", "C\341\272\255p nh\341\272\255t th\303\264ng tin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class info: public Ui_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_H
