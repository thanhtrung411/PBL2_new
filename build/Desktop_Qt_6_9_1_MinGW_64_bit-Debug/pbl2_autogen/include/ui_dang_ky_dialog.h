/********************************************************************************
** Form generated from reading UI file 'dang_ky_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DANG_KY_DIALOG_H
#define UI_DANG_KY_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dang_ky_dialog
{
public:
    QWidget *centralwidget;
    QLineEdit *user_input;
    QLabel *user_layout;
    QLabel *name_layout;
    QLineEdit *name_input;
    QLabel *gioi_tinh_input;
    QLabel *birthday_layout;
    QLabel *email_layout;
    QLineEdit *email_input;
    QLabel *nuber_call_layout;
    QLabel *doi_tuong_layout;
    QLabel *pass_again_layout;
    QLabel *password_layout;
    QLineEdit *pass_again_input;
    QCheckBox *dieu_khoan_input;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *Boy_button;
    QRadioButton *Girl_button;
    QDateEdit *date_birthday_input;
    QComboBox *Doi_tuong_input;
    QPushButton *dang_ky_2_button;
    QLineEdit *so_dien_thoai_input;
    QLineEdit *pass_input;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *dang_ky_dialog)
    {
        if (dang_ky_dialog->objectName().isEmpty())
            dang_ky_dialog->setObjectName("dang_ky_dialog");
        dang_ky_dialog->resize(1317, 740);
        centralwidget = new QWidget(dang_ky_dialog);
        centralwidget->setObjectName("centralwidget");
        user_input = new QLineEdit(centralwidget);
        user_input->setObjectName("user_input");
        user_input->setGeometry(QRect(275, 160, 291, 28));
        user_layout = new QLabel(centralwidget);
        user_layout->setObjectName("user_layout");
        user_layout->setGeometry(QRect(275, 130, 291, 20));
        name_layout = new QLabel(centralwidget);
        name_layout->setObjectName("name_layout");
        name_layout->setGeometry(QRect(275, 200, 291, 20));
        name_input = new QLineEdit(centralwidget);
        name_input->setObjectName("name_input");
        name_input->setGeometry(QRect(275, 230, 291, 28));
        gioi_tinh_input = new QLabel(centralwidget);
        gioi_tinh_input->setObjectName("gioi_tinh_input");
        gioi_tinh_input->setGeometry(QRect(275, 270, 291, 20));
        birthday_layout = new QLabel(centralwidget);
        birthday_layout->setObjectName("birthday_layout");
        birthday_layout->setGeometry(QRect(275, 340, 291, 20));
        email_layout = new QLabel(centralwidget);
        email_layout->setObjectName("email_layout");
        email_layout->setGeometry(QRect(275, 410, 291, 20));
        email_input = new QLineEdit(centralwidget);
        email_input->setObjectName("email_input");
        email_input->setGeometry(QRect(275, 440, 291, 28));
        nuber_call_layout = new QLabel(centralwidget);
        nuber_call_layout->setObjectName("nuber_call_layout");
        nuber_call_layout->setGeometry(QRect(750, 130, 291, 20));
        doi_tuong_layout = new QLabel(centralwidget);
        doi_tuong_layout->setObjectName("doi_tuong_layout");
        doi_tuong_layout->setGeometry(QRect(750, 200, 291, 20));
        pass_again_layout = new QLabel(centralwidget);
        pass_again_layout->setObjectName("pass_again_layout");
        pass_again_layout->setGeometry(QRect(750, 340, 291, 20));
        password_layout = new QLabel(centralwidget);
        password_layout->setObjectName("password_layout");
        password_layout->setGeometry(QRect(750, 270, 291, 20));
        pass_again_input = new QLineEdit(centralwidget);
        pass_again_input->setObjectName("pass_again_input");
        pass_again_input->setGeometry(QRect(750, 370, 291, 28));
        pass_again_input->setEchoMode(QLineEdit::EchoMode::Password);
        dieu_khoan_input = new QCheckBox(centralwidget);
        dieu_khoan_input->setObjectName("dieu_khoan_input");
        dieu_khoan_input->setGeometry(QRect(280, 490, 761, 25));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(280, 289, 291, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Boy_button = new QRadioButton(horizontalLayoutWidget);
        Boy_button->setObjectName("Boy_button");

        horizontalLayout->addWidget(Boy_button);

        Girl_button = new QRadioButton(horizontalLayoutWidget);
        Girl_button->setObjectName("Girl_button");

        horizontalLayout->addWidget(Girl_button);

        date_birthday_input = new QDateEdit(centralwidget);
        date_birthday_input->setObjectName("date_birthday_input");
        date_birthday_input->setGeometry(QRect(280, 370, 281, 31));
        Doi_tuong_input = new QComboBox(centralwidget);
        Doi_tuong_input->addItem(QString());
        Doi_tuong_input->addItem(QString());
        Doi_tuong_input->addItem(QString());
        Doi_tuong_input->setObjectName("Doi_tuong_input");
        Doi_tuong_input->setGeometry(QRect(750, 230, 291, 28));
        dang_ky_2_button = new QPushButton(centralwidget);
        dang_ky_2_button->setObjectName("dang_ky_2_button");
        dang_ky_2_button->setGeometry(QRect(660, 550, 141, 31));
        so_dien_thoai_input = new QLineEdit(centralwidget);
        so_dien_thoai_input->setObjectName("so_dien_thoai_input");
        so_dien_thoai_input->setGeometry(QRect(750, 160, 291, 28));
        pass_input = new QLineEdit(centralwidget);
        pass_input->setObjectName("pass_input");
        pass_input->setGeometry(QRect(750, 300, 291, 28));
        pass_input->setEchoMode(QLineEdit::EchoMode::Password);
        dang_ky_dialog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(dang_ky_dialog);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1317, 25));
        dang_ky_dialog->setMenuBar(menubar);
        statusbar = new QStatusBar(dang_ky_dialog);
        statusbar->setObjectName("statusbar");
        dang_ky_dialog->setStatusBar(statusbar);

        retranslateUi(dang_ky_dialog);

        QMetaObject::connectSlotsByName(dang_ky_dialog);
    } // setupUi

    void retranslateUi(QMainWindow *dang_ky_dialog)
    {
        dang_ky_dialog->setWindowTitle(QCoreApplication::translate("dang_ky_dialog", "MainWindow", nullptr));
        user_input->setPlaceholderText(QCoreApplication::translate("dang_ky_dialog", "Nh\341\272\255p M\303\243 s\341\273\221 sinh vi\303\252n (n\341\272\277u c\303\263)", nullptr));
        user_layout->setText(QCoreApplication::translate("dang_ky_dialog", "T\303\252n \304\221\304\203ng nh\341\272\255p (M\303\243 s\341\273\221 sinh vi\303\252n)", nullptr));
        name_layout->setText(QCoreApplication::translate("dang_ky_dialog", "H\341\273\215 v\303\240 t\303\252n", nullptr));
        name_input->setPlaceholderText(QCoreApplication::translate("dang_ky_dialog", "Nh\341\272\255p h\341\273\215 v\303\240 t\303\252n", nullptr));
        gioi_tinh_input->setText(QCoreApplication::translate("dang_ky_dialog", "Gi\341\273\233i t\303\255nh", nullptr));
        birthday_layout->setText(QCoreApplication::translate("dang_ky_dialog", "Ng\303\240y sinh", nullptr));
        email_layout->setText(QCoreApplication::translate("dang_ky_dialog", "\304\220\341\273\213a ch\341\273\211 email", nullptr));
        email_input->setPlaceholderText(QCoreApplication::translate("dang_ky_dialog", "Nh\341\272\255p \304\221\341\273\213a ch\341\273\211 email", nullptr));
        nuber_call_layout->setText(QCoreApplication::translate("dang_ky_dialog", "S\341\273\221 \304\221i\341\273\207n tho\341\272\241i", nullptr));
        doi_tuong_layout->setText(QCoreApplication::translate("dang_ky_dialog", "\304\220\341\273\221i t\306\260\341\273\243ng", nullptr));
        pass_again_layout->setText(QCoreApplication::translate("dang_ky_dialog", "Nh\341\272\255p l\341\272\241i m\341\272\255t kh\341\272\251u", nullptr));
        password_layout->setText(QCoreApplication::translate("dang_ky_dialog", "M\341\272\255t kh\341\272\251u", nullptr));
        pass_again_input->setPlaceholderText(QCoreApplication::translate("dang_ky_dialog", "Nh\341\272\255p l\341\272\241i m\341\272\255t kh\341\272\251u", nullptr));
        dieu_khoan_input->setText(QCoreApplication::translate("dang_ky_dialog", "\304\220\304\203ng nh\341\272\255p ngh\304\251a l\303\240 b\341\272\241n \304\221\341\273\223ng \303\275 v\341\273\233i \304\220i\341\273\201u kho\341\272\243n v\303\240 Ch\303\255nh s\303\241ch s\341\273\255 d\341\273\245ng c\341\273\247a h\341\273\207 th\341\273\221ng ph\341\272\247n m\341\273\201m Th\306\260 vi\341\273\207n s\341\273\221.", nullptr));
        Boy_button->setText(QCoreApplication::translate("dang_ky_dialog", "Nam", nullptr));
        Girl_button->setText(QCoreApplication::translate("dang_ky_dialog", "N\341\273\257", nullptr));
        Doi_tuong_input->setItemText(0, QCoreApplication::translate("dang_ky_dialog", "Sinh vi\303\252n", nullptr));
        Doi_tuong_input->setItemText(1, QCoreApplication::translate("dang_ky_dialog", "Gi\341\272\243ng vi\303\252n", nullptr));
        Doi_tuong_input->setItemText(2, QCoreApplication::translate("dang_ky_dialog", "Kh\303\241c", nullptr));

        dang_ky_2_button->setText(QCoreApplication::translate("dang_ky_dialog", "\304\220\304\202NG K\303\235", nullptr));
        so_dien_thoai_input->setPlaceholderText(QCoreApplication::translate("dang_ky_dialog", "Nh\341\272\255p s\341\273\221 \304\221i\341\273\207n tho\341\272\241i", nullptr));
        pass_input->setPlaceholderText(QCoreApplication::translate("dang_ky_dialog", "Nh\341\272\255p m\341\272\255t kh\341\272\251u", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dang_ky_dialog: public Ui_dang_ky_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DANG_KY_DIALOG_H
