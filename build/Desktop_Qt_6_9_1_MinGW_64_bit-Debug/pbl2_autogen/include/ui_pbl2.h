/********************************************************************************
** Form generated from reading UI file 'pbl2.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PBL2_H
#define UI_PBL2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pbl2
{
public:
    QAction *actionTong_quan;
    QAction *actionChuc_nang_Nhiem_vu;
    QWidget *centralwidget;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *dang_ky_button_2;
    QPushButton *dang_ky_button;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuTRANG_CH;
    QMenu *menuGI_I_THI_U;
    QMenu *menuCSDL_N_I_SINH;
    QMenu *menuCSDL_TR_C_TUY_N;
    QMenu *menuD_CH_V_TH_VI_N;
    QMenu *menuH_NG_D_N_S_D_NG;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *pbl2)
    {
        if (pbl2->objectName().isEmpty())
            pbl2->setObjectName("pbl2");
        pbl2->resize(1317, 740);
        QFont font;
        font.setStyleStrategy(QFont::PreferDefault);
        pbl2->setFont(font);
        actionTong_quan = new QAction(pbl2);
        actionTong_quan->setObjectName("actionTong_quan");
        actionChuc_nang_Nhiem_vu = new QAction(pbl2);
        actionChuc_nang_Nhiem_vu->setObjectName("actionChuc_nang_Nhiem_vu");
        centralwidget = new QWidget(pbl2);
        centralwidget->setObjectName("centralwidget");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(1120, 80, 181, 28));
        lineEdit->setDragEnabled(true);
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(1120, 120, 181, 28));
        lineEdit_2->setDragEnabled(true);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(1120, 150, 181, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        dang_ky_button_2 = new QPushButton(horizontalLayoutWidget);
        dang_ky_button_2->setObjectName("dang_ky_button_2");

        horizontalLayout->addWidget(dang_ky_button_2);

        dang_ky_button = new QPushButton(horizontalLayoutWidget);
        dang_ky_button->setObjectName("dang_ky_button");

        horizontalLayout->addWidget(dang_ky_button);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(true);
        pushButton->setGeometry(QRect(1120, 190, 181, 29));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(true);
        font1.setUnderline(false);
        font1.setStrikeOut(false);
        font1.setStyleStrategy(QFont::PreferDefault);
        font1.setHintingPreference(QFont::PreferDefaultHinting);
        pushButton->setFont(font1);
        pushButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pbl2->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pbl2);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1317, 25));
        menuTRANG_CH = new QMenu(menubar);
        menuTRANG_CH->setObjectName("menuTRANG_CH");
        menuGI_I_THI_U = new QMenu(menubar);
        menuGI_I_THI_U->setObjectName("menuGI_I_THI_U");
        menuCSDL_N_I_SINH = new QMenu(menubar);
        menuCSDL_N_I_SINH->setObjectName("menuCSDL_N_I_SINH");
        menuCSDL_TR_C_TUY_N = new QMenu(menubar);
        menuCSDL_TR_C_TUY_N->setObjectName("menuCSDL_TR_C_TUY_N");
        menuD_CH_V_TH_VI_N = new QMenu(menubar);
        menuD_CH_V_TH_VI_N->setObjectName("menuD_CH_V_TH_VI_N");
        menuH_NG_D_N_S_D_NG = new QMenu(menubar);
        menuH_NG_D_N_S_D_NG->setObjectName("menuH_NG_D_N_S_D_NG");
        pbl2->setMenuBar(menubar);
        statusbar = new QStatusBar(pbl2);
        statusbar->setObjectName("statusbar");
        pbl2->setStatusBar(statusbar);

        menubar->addAction(menuTRANG_CH->menuAction());
        menubar->addAction(menuGI_I_THI_U->menuAction());
        menubar->addAction(menuCSDL_N_I_SINH->menuAction());
        menubar->addAction(menuCSDL_TR_C_TUY_N->menuAction());
        menubar->addAction(menuD_CH_V_TH_VI_N->menuAction());
        menubar->addAction(menuH_NG_D_N_S_D_NG->menuAction());
        menuGI_I_THI_U->addAction(actionTong_quan);
        menuGI_I_THI_U->addAction(actionChuc_nang_Nhiem_vu);

        retranslateUi(pbl2);

        QMetaObject::connectSlotsByName(pbl2);
    } // setupUi

    void retranslateUi(QMainWindow *pbl2)
    {
        pbl2->setWindowTitle(QCoreApplication::translate("pbl2", "pbl2", nullptr));
        actionTong_quan->setText(QCoreApplication::translate("pbl2", "Tong quan", nullptr));
        actionChuc_nang_Nhiem_vu->setText(QCoreApplication::translate("pbl2", "Chuc nang - Nhiem vu", nullptr));
#if QT_CONFIG(accessibility)
        lineEdit->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        lineEdit->setInputMask(QString());
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("pbl2", "T\303\252n ng\306\260\341\273\235i d\303\271ng", nullptr));
#if QT_CONFIG(accessibility)
        lineEdit_2->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        lineEdit_2->setInputMask(QString());
        lineEdit_2->setText(QString());
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("pbl2", "M\341\272\255t kh\341\272\251u", nullptr));
        dang_ky_button_2->setText(QCoreApplication::translate("pbl2", "\304\220\304\203ng nh\341\272\255p", nullptr));
        dang_ky_button->setText(QCoreApplication::translate("pbl2", "\304\220\304\203ng k\303\275", nullptr));
        pushButton->setText(QCoreApplication::translate("pbl2", "B\341\272\241n qu\303\252n m\341\272\255t kh\341\272\251u ?", nullptr));
#if QT_CONFIG(shortcut)
        pushButton->setShortcut(QString());
#endif // QT_CONFIG(shortcut)
        menuTRANG_CH->setTitle(QCoreApplication::translate("pbl2", "TRANG CH\341\273\246", nullptr));
        menuGI_I_THI_U->setTitle(QCoreApplication::translate("pbl2", "GI\341\273\232I THI\341\273\206U", nullptr));
        menuCSDL_N_I_SINH->setTitle(QCoreApplication::translate("pbl2", "CSDL N\341\273\230I SINH", nullptr));
        menuCSDL_TR_C_TUY_N->setTitle(QCoreApplication::translate("pbl2", "CSDL TR\341\273\260C TUY\341\272\276N", nullptr));
        menuD_CH_V_TH_VI_N->setTitle(QCoreApplication::translate("pbl2", "D\341\273\212CH V\341\273\244 TH\306\257 VI\341\273\206N", nullptr));
        menuH_NG_D_N_S_D_NG->setTitle(QCoreApplication::translate("pbl2", "H\306\257\341\273\232NG D\341\272\252N S\341\273\254 D\341\273\244NG", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pbl2: public Ui_pbl2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PBL2_H
