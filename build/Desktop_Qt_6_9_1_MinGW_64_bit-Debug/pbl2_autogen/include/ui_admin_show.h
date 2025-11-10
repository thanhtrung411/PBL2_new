/********************************************************************************
** Form generated from reading UI file 'admin_show.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_SHOW_H
#define UI_ADMIN_SHOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_admin_show
{
public:
    QAction *actionThem_phong;
    QAction *actionThem_nguoi_dung_quan_tri;
    QAction *actionThem_nguoi_dung;
    QAction *action_them_sach;
    QAction *action_them_quan_tri;
    QAction *action_them_nguoi_dung;
    QAction *actionHIHIH;
    QAction *actionHAHAH;
    QAction *actionHEHEHE;
    QAction *actionTHONG_TIN_SACH;
    QAction *actionTHONG_TIN_NGUOI_DUNG;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *them_sach_layout;
    QLabel *label_3;
    QLabel *ten_sach_layout;
    QLineEdit *ten_sach_input;
    QLabel *tac_gia_layout;
    QLineEdit *tac_gia_input;
    QLabel *the_loai_layout;
    QComboBox *the_loai_sach_input;
    QLabel *chuyen_nganh_layout;
    QComboBox *chuyen_nganh_input;
    QLabel *ID_Sach_layout;
    QLineEdit *ID_Sach_input;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *nha_xuat_ban_layout;
    QLineEdit *nha_xuat_ban_input;
    QVBoxLayout *verticalLayout_6;
    QLabel *nam_xuat_ban_layout;
    QLineEdit *nam_xuat_ban_input;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_7;
    QLabel *so_trang_layout;
    QLineEdit *so_trang_input;
    QVBoxLayout *verticalLayout_8;
    QLabel *ISBN_layout;
    QLineEdit *ISBN_input;
    QLabel *language_layout;
    QLineEdit *language_input;
    QLabel *tom_tat_layout;
    QPlainTextEdit *tom_tat_input;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_2;
    QSpinBox *number_of_book;
    QCheckBox *is_borrow_check;
    QCheckBox *is_read_online_check;
    QCheckBox *is_download_check;
    QSpacerItem *horizontalSpacer_2;
    QLabel *link_png_name;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *link_png_button;
    QLabel *link_png_layout;
    QLabel *link_pdf_name;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *link_pdf_button;
    QLabel *link_pdf_layout;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *them_button;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *admin_show)
    {
        if (admin_show->objectName().isEmpty())
            admin_show->setObjectName("admin_show");
        admin_show->resize(1390, 785);
        QPalette palette;
        QBrush brush(QColor(69, 104, 173, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(243, 246, 255, 255));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        QBrush brush2(QColor(170, 191, 255, 255));
        brush2.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::HighlightedText, brush2);
        QBrush brush3(QColor(69, 104, 173, 128));
        brush3.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush3);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::HighlightedText, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush3);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::HighlightedText, brush2);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush3);
#endif
        admin_show->setPalette(palette);
        QFont font;
        font.setWeight(QFont::Thin);
        admin_show->setFont(font);
        admin_show->setStyleSheet(QString::fromUtf8("\n"
"QWidget { background: #f3f6ff; color: #0f172a; }\n"
"\n"
"\n"
"QLineEdit, QComboBox, QSpinBox, QDateEdit {\n"
"  background: #ffffff;\n"
"  color: #0f172a;\n"
"  border: 1px solid #e0e2eb;\n"
"  border-radius: 8px;\n"
"  padding: 6px 8px;\n"
"}\n"
"QLineEdit:focus, QComboBox:focus, QSpinBox:focus, QDateEdit:focus {\n"
"  border-color: #617fb9;            \n"
"  outline: none;\n"
"}\n"
"\n"
"\n"
"QPushButton {\n"
"  background: #ffffff;\n"
"  color: #4568ad;\n"
"  border: 2px solid #4568ad;\n"
"  border-radius: 8px;\n"
"}\n"
"QPushButton:hover   { background: #e9ecf5; border-color: #3e5e9c; }\n"
"QPushButton:pressed { background: #d6d8e0; border-color: #37538a; }\n"
"QPushButton:disabled{\n"
"  background: #f1f3f9; color: #9aa0a6; border-color: #e0e2eb;\n"
"}\n"
"\n"
"QPushButton#primaryBtn { background:#4568ad; color:#fff; border-color:#4568ad; }\n"
"QPushButton#primaryBtn:hover   { background:#3e5e9c; }\n"
"QPushButton#primaryBtn:pressed { background:#37538a; }\n"
"\n"
"QTableView {\n"
"  background: #ff"
                        "ffff;\n"
"  alternate-background-color: #e9ecf5;\n"
"  gridline-color: #e0e2eb;\n"
"  selection-background-color: #4568ad;\n"
"  selection-color: #ffffff;\n"
"}\n"
"\n"
"\n"
"QToolTip {\n"
"  color: #ffffff;\n"
"  background: #1f2937;\n"
"  border: 1px solid #0b1220;\n"
"  border-radius: 8px;\n"
"  padding: 6px;\n"
"}\n"
""));
        actionThem_phong = new QAction(admin_show);
        actionThem_phong->setObjectName("actionThem_phong");
        actionThem_nguoi_dung_quan_tri = new QAction(admin_show);
        actionThem_nguoi_dung_quan_tri->setObjectName("actionThem_nguoi_dung_quan_tri");
        actionThem_nguoi_dung = new QAction(admin_show);
        actionThem_nguoi_dung->setObjectName("actionThem_nguoi_dung");
        action_them_sach = new QAction(admin_show);
        action_them_sach->setObjectName("action_them_sach");
        action_them_quan_tri = new QAction(admin_show);
        action_them_quan_tri->setObjectName("action_them_quan_tri");
        action_them_nguoi_dung = new QAction(admin_show);
        action_them_nguoi_dung->setObjectName("action_them_nguoi_dung");
        actionHIHIH = new QAction(admin_show);
        actionHIHIH->setObjectName("actionHIHIH");
        actionHAHAH = new QAction(admin_show);
        actionHAHAH->setObjectName("actionHAHAH");
        actionHEHEHE = new QAction(admin_show);
        actionHEHEHE->setObjectName("actionHEHEHE");
        actionTHONG_TIN_SACH = new QAction(admin_show);
        actionTHONG_TIN_SACH->setObjectName("actionTHONG_TIN_SACH");
        actionTHONG_TIN_NGUOI_DUNG = new QAction(admin_show);
        actionTHONG_TIN_NGUOI_DUNG->setObjectName("actionTHONG_TIN_NGUOI_DUNG");
        centralwidget = new QWidget(admin_show);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(200, 0));

        verticalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");

        verticalLayout->addWidget(pushButton_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        scrollArea = new QScrollArea(page);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 1151, 761));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1132, 2586));
        scrollAreaWidgetContents->setMinimumSize(QSize(0, 2586));
        verticalLayoutWidget_3 = new QWidget(scrollAreaWidgetContents);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(89, 9, 941, 1231));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        them_sach_layout = new QLabel(verticalLayoutWidget_3);
        them_sach_layout->setObjectName("them_sach_layout");
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        them_sach_layout->setFont(font1);
        them_sach_layout->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(them_sach_layout);

        label_3 = new QLabel(verticalLayoutWidget_3);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        ten_sach_layout = new QLabel(verticalLayoutWidget_3);
        ten_sach_layout->setObjectName("ten_sach_layout");
        QFont font2;
        font2.setPointSize(10);
        ten_sach_layout->setFont(font2);
        ten_sach_layout->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(ten_sach_layout);

        ten_sach_input = new QLineEdit(verticalLayoutWidget_3);
        ten_sach_input->setObjectName("ten_sach_input");

        verticalLayout_3->addWidget(ten_sach_input);

        tac_gia_layout = new QLabel(verticalLayoutWidget_3);
        tac_gia_layout->setObjectName("tac_gia_layout");
        tac_gia_layout->setFont(font2);
        tac_gia_layout->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(tac_gia_layout);

        tac_gia_input = new QLineEdit(verticalLayoutWidget_3);
        tac_gia_input->setObjectName("tac_gia_input");

        verticalLayout_3->addWidget(tac_gia_input);

        the_loai_layout = new QLabel(verticalLayoutWidget_3);
        the_loai_layout->setObjectName("the_loai_layout");
        the_loai_layout->setFont(font2);
        the_loai_layout->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(the_loai_layout);

        the_loai_sach_input = new QComboBox(verticalLayoutWidget_3);
        the_loai_sach_input->addItem(QString());
        the_loai_sach_input->addItem(QString());
        the_loai_sach_input->addItem(QString());
        the_loai_sach_input->addItem(QString());
        the_loai_sach_input->addItem(QString());
        the_loai_sach_input->addItem(QString());
        the_loai_sach_input->addItem(QString());
        the_loai_sach_input->addItem(QString());
        the_loai_sach_input->addItem(QString());
        the_loai_sach_input->setObjectName("the_loai_sach_input");
        QFont font3;
        font3.setPointSize(9);
        the_loai_sach_input->setFont(font3);

        verticalLayout_3->addWidget(the_loai_sach_input);

        chuyen_nganh_layout = new QLabel(verticalLayoutWidget_3);
        chuyen_nganh_layout->setObjectName("chuyen_nganh_layout");
        chuyen_nganh_layout->setFont(font2);
        chuyen_nganh_layout->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(chuyen_nganh_layout);

        chuyen_nganh_input = new QComboBox(verticalLayoutWidget_3);
        chuyen_nganh_input->addItem(QString());
        chuyen_nganh_input->addItem(QString());
        chuyen_nganh_input->addItem(QString());
        chuyen_nganh_input->addItem(QString());
        chuyen_nganh_input->addItem(QString());
        chuyen_nganh_input->addItem(QString());
        chuyen_nganh_input->addItem(QString());
        chuyen_nganh_input->addItem(QString());
        chuyen_nganh_input->addItem(QString());
        chuyen_nganh_input->addItem(QString());
        chuyen_nganh_input->setObjectName("chuyen_nganh_input");
        chuyen_nganh_input->setFont(font3);

        verticalLayout_3->addWidget(chuyen_nganh_input);

        ID_Sach_layout = new QLabel(verticalLayoutWidget_3);
        ID_Sach_layout->setObjectName("ID_Sach_layout");
        ID_Sach_layout->setFont(font2);
        ID_Sach_layout->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(ID_Sach_layout);

        ID_Sach_input = new QLineEdit(verticalLayoutWidget_3);
        ID_Sach_input->setObjectName("ID_Sach_input");

        verticalLayout_3->addWidget(ID_Sach_input);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        nha_xuat_ban_layout = new QLabel(verticalLayoutWidget_3);
        nha_xuat_ban_layout->setObjectName("nha_xuat_ban_layout");
        nha_xuat_ban_layout->setFont(font2);
        nha_xuat_ban_layout->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout_5->addWidget(nha_xuat_ban_layout);

        nha_xuat_ban_input = new QLineEdit(verticalLayoutWidget_3);
        nha_xuat_ban_input->setObjectName("nha_xuat_ban_input");

        verticalLayout_5->addWidget(nha_xuat_ban_input);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        nam_xuat_ban_layout = new QLabel(verticalLayoutWidget_3);
        nam_xuat_ban_layout->setObjectName("nam_xuat_ban_layout");
        nam_xuat_ban_layout->setFont(font2);

        verticalLayout_6->addWidget(nam_xuat_ban_layout);

        nam_xuat_ban_input = new QLineEdit(verticalLayoutWidget_3);
        nam_xuat_ban_input->setObjectName("nam_xuat_ban_input");
        nam_xuat_ban_input->setMinimumSize(QSize(246, 0));

        verticalLayout_6->addWidget(nam_xuat_ban_input);


        horizontalLayout_2->addLayout(verticalLayout_6);

        horizontalLayout_2->setStretch(0, 1);

        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        so_trang_layout = new QLabel(verticalLayoutWidget_3);
        so_trang_layout->setObjectName("so_trang_layout");
        so_trang_layout->setFont(font2);
        so_trang_layout->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_7->addWidget(so_trang_layout);

        so_trang_input = new QLineEdit(verticalLayoutWidget_3);
        so_trang_input->setObjectName("so_trang_input");

        verticalLayout_7->addWidget(so_trang_input);


        horizontalLayout_3->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName("verticalLayout_8");
        ISBN_layout = new QLabel(verticalLayoutWidget_3);
        ISBN_layout->setObjectName("ISBN_layout");
        ISBN_layout->setFont(font2);
        ISBN_layout->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_8->addWidget(ISBN_layout);

        ISBN_input = new QLineEdit(verticalLayoutWidget_3);
        ISBN_input->setObjectName("ISBN_input");
        ISBN_input->setMinimumSize(QSize(247, 0));

        verticalLayout_8->addWidget(ISBN_input);


        horizontalLayout_3->addLayout(verticalLayout_8);

        horizontalLayout_3->setStretch(0, 1);

        verticalLayout_3->addLayout(horizontalLayout_3);

        language_layout = new QLabel(verticalLayoutWidget_3);
        language_layout->setObjectName("language_layout");
        language_layout->setFont(font2);
        language_layout->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(language_layout);

        language_input = new QLineEdit(verticalLayoutWidget_3);
        language_input->setObjectName("language_input");

        verticalLayout_3->addWidget(language_input);

        tom_tat_layout = new QLabel(verticalLayoutWidget_3);
        tom_tat_layout->setObjectName("tom_tat_layout");
        tom_tat_layout->setFont(font2);
        tom_tat_layout->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(tom_tat_layout);

        tom_tat_input = new QPlainTextEdit(verticalLayoutWidget_3);
        tom_tat_input->setObjectName("tom_tat_input");
        tom_tat_input->setMaximumSize(QSize(16777215, 125));
        tom_tat_input->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_3->addWidget(tom_tat_input);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName("verticalLayout_11");
        label_2 = new QLabel(verticalLayoutWidget_3);
        label_2->setObjectName("label_2");

        verticalLayout_11->addWidget(label_2);

        number_of_book = new QSpinBox(verticalLayoutWidget_3);
        number_of_book->setObjectName("number_of_book");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(number_of_book->sizePolicy().hasHeightForWidth());
        number_of_book->setSizePolicy(sizePolicy);
        number_of_book->setMinimumSize(QSize(165, 0));
        number_of_book->setMinimum(1);

        verticalLayout_11->addWidget(number_of_book);


        horizontalLayout_8->addLayout(verticalLayout_11);

        is_borrow_check = new QCheckBox(verticalLayoutWidget_3);
        is_borrow_check->setObjectName("is_borrow_check");
        is_borrow_check->setMaximumSize(QSize(999999, 16777215));

        horizontalLayout_8->addWidget(is_borrow_check);

        is_read_online_check = new QCheckBox(verticalLayoutWidget_3);
        is_read_online_check->setObjectName("is_read_online_check");
        is_read_online_check->setMaximumSize(QSize(9999999, 16777215));

        horizontalLayout_8->addWidget(is_read_online_check);

        is_download_check = new QCheckBox(verticalLayoutWidget_3);
        is_download_check->setObjectName("is_download_check");

        horizontalLayout_8->addWidget(is_download_check);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_8);

        link_png_name = new QLabel(verticalLayoutWidget_3);
        link_png_name->setObjectName("link_png_name");
        link_png_name->setFont(font2);
        link_png_name->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(link_png_name);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        link_png_button = new QPushButton(verticalLayoutWidget_3);
        link_png_button->setObjectName("link_png_button");
        link_png_button->setMaximumSize(QSize(135, 16777215));
        link_png_button->setFont(font2);

        horizontalLayout_6->addWidget(link_png_button);

        link_png_layout = new QLabel(verticalLayoutWidget_3);
        link_png_layout->setObjectName("link_png_layout");

        horizontalLayout_6->addWidget(link_png_layout);


        verticalLayout_3->addLayout(horizontalLayout_6);

        link_pdf_name = new QLabel(verticalLayoutWidget_3);
        link_pdf_name->setObjectName("link_pdf_name");
        link_pdf_name->setFont(font2);
        link_pdf_name->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(link_pdf_name);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        link_pdf_button = new QPushButton(verticalLayoutWidget_3);
        link_pdf_button->setObjectName("link_pdf_button");
        link_pdf_button->setMaximumSize(QSize(135, 16777215));
        link_pdf_button->setFont(font2);

        horizontalLayout_7->addWidget(link_pdf_button);

        link_pdf_layout = new QLabel(verticalLayoutWidget_3);
        link_pdf_layout->setObjectName("link_pdf_layout");

        horizontalLayout_7->addWidget(link_pdf_layout);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        them_button = new QPushButton(verticalLayoutWidget_3);
        them_button->setObjectName("them_button");
        sizePolicy.setHeightForWidth(them_button->sizePolicy().hasHeightForWidth());
        them_button->setSizePolicy(sizePolicy);
        them_button->setMaximumSize(QSize(200, 16777215));
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        them_button->setFont(font4);

        horizontalLayout_9->addWidget(them_button);


        verticalLayout_3->addLayout(horizontalLayout_9);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        scrollArea->setWidget(scrollAreaWidgetContents);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayoutWidget = new QWidget(page_2);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 9, 1141, 741));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 75));
        label->setFont(font4);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton_6 = new QPushButton(verticalLayoutWidget);
        pushButton_6->setObjectName("pushButton_6");
        pushButton_6->setMinimumSize(QSize(200, 0));
        pushButton_6->setMaximumSize(QSize(200, 200));

        horizontalLayout_4->addWidget(pushButton_6);

        pushButton_5 = new QPushButton(verticalLayoutWidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(200, 0));
        pushButton_5->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_4->addWidget(pushButton_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tableWidget = new QTableWidget(verticalLayoutWidget);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        if (tableWidget->rowCount() < 6)
            tableWidget->setRowCount(6);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setRowCount(6);
        tableWidget->setColumnCount(8);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);

        verticalLayout_2->addWidget(tableWidget);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);

        admin_show->setCentralWidget(centralwidget);

        retranslateUi(admin_show);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(admin_show);
    } // setupUi

    void retranslateUi(QMainWindow *admin_show)
    {
        admin_show->setWindowTitle(QCoreApplication::translate("admin_show", "MainWindow", nullptr));
        actionThem_phong->setText(QCoreApplication::translate("admin_show", "Them phong", nullptr));
        actionThem_nguoi_dung_quan_tri->setText(QCoreApplication::translate("admin_show", "Them nguoi dung quan tri", nullptr));
        actionThem_nguoi_dung->setText(QCoreApplication::translate("admin_show", "Them nguoi dung", nullptr));
        action_them_sach->setText(QCoreApplication::translate("admin_show", "Them sach", nullptr));
        action_them_quan_tri->setText(QCoreApplication::translate("admin_show", "Them quan tri", nullptr));
        action_them_nguoi_dung->setText(QCoreApplication::translate("admin_show", "Them nguoi dung", nullptr));
        actionHIHIH->setText(QCoreApplication::translate("admin_show", "HIHIH", nullptr));
        actionHAHAH->setText(QCoreApplication::translate("admin_show", "HAHAH", nullptr));
        actionHEHEHE->setText(QCoreApplication::translate("admin_show", "HEHEHE", nullptr));
        actionTHONG_TIN_SACH->setText(QCoreApplication::translate("admin_show", "THONG TIN SACH", nullptr));
        actionTHONG_TIN_NGUOI_DUNG->setText(QCoreApplication::translate("admin_show", "THONG TIN NGUOI DUNG", nullptr));
        pushButton_2->setText(QCoreApplication::translate("admin_show", "Qu\341\272\243n l\303\275 s\303\241ch", nullptr));
        pushButton->setText(QCoreApplication::translate("admin_show", "Qu\341\272\243n l\303\275 m\306\260\341\273\243n/tr\341\272\243", nullptr));
        pushButton_3->setText(QCoreApplication::translate("admin_show", "Qu\341\272\243n l\303\275 ng\306\260\341\273\235i d\303\271ng", nullptr));
        pushButton_4->setText(QCoreApplication::translate("admin_show", "Th\341\273\221ng k\303\252 v\303\240 b\303\241o c\303\241o", nullptr));
        them_sach_layout->setText(QCoreApplication::translate("admin_show", "Th\303\252m s\303\241ch", nullptr));
        label_3->setText(QString());
        ten_sach_layout->setText(QCoreApplication::translate("admin_show", "T\303\252n s\303\241ch", nullptr));
        ten_sach_input->setPlaceholderText(QCoreApplication::translate("admin_show", "Vui l\303\262ng nh\341\272\255p t\303\252n s\303\241ch", nullptr));
        tac_gia_layout->setText(QCoreApplication::translate("admin_show", "T\303\252n t\303\241c gi\341\272\243", nullptr));
        tac_gia_input->setPlaceholderText(QCoreApplication::translate("admin_show", "Vui l\303\262ng nh\341\272\255p t\303\252n t\303\241c gi\341\272\243/\304\221\341\273\223ng t\303\241c gi\341\272\243", nullptr));
        the_loai_layout->setText(QCoreApplication::translate("admin_show", "Th\341\273\203 lo\341\272\241i s\303\241ch", nullptr));
        the_loai_sach_input->setItemText(0, QCoreApplication::translate("admin_show", "Vui l\303\262ng ch\341\273\215n th\341\273\203 lo\341\272\241i...", nullptr));
        the_loai_sach_input->setItemText(1, QCoreApplication::translate("admin_show", "S\303\241ch gi\303\241o tr\303\254nh & T\303\240i li\341\273\207u h\341\273\215c t\341\272\255p", nullptr));
        the_loai_sach_input->setItemText(2, QCoreApplication::translate("admin_show", "S\303\241ch chuy\303\252n ng\303\240nh", nullptr));
        the_loai_sach_input->setItemText(3, QCoreApplication::translate("admin_show", "S\303\241ch tham kh\341\272\243o ngo\341\272\241i v\304\203n", nullptr));
        the_loai_sach_input->setItemText(4, QCoreApplication::translate("admin_show", "Lu\341\272\255n v\304\203n - Kh\303\263a lu\341\272\255n - b\303\241o c\303\241o", nullptr));
        the_loai_sach_input->setItemText(5, QCoreApplication::translate("admin_show", "T\303\240i li\341\273\207u ph\341\273\225 th\303\264ng - b\341\273\225 tr\341\273\243", nullptr));
        the_loai_sach_input->setItemText(6, QCoreApplication::translate("admin_show", "B\303\241o - T\341\272\241p ch\303\255 - \341\272\245n ph\341\272\251m \304\221\341\273\213nh k\341\273\263", nullptr));
        the_loai_sach_input->setItemText(7, QCoreApplication::translate("admin_show", "S\303\241ch k\341\273\271 n\304\203ng m\341\273\201m", nullptr));
        the_loai_sach_input->setItemText(8, QCoreApplication::translate("admin_show", "Kh\303\241c...", nullptr));

        the_loai_sach_input->setPlaceholderText(QString());
        chuyen_nganh_layout->setText(QCoreApplication::translate("admin_show", "Chuy\303\252n ng\303\240nh ", nullptr));
        chuyen_nganh_input->setItemText(0, QCoreApplication::translate("admin_show", "Vui l\303\262ng ch\341\273\215n chuy\303\252n ng\303\240nh...", nullptr));
        chuyen_nganh_input->setItemText(1, QCoreApplication::translate("admin_show", "M\303\241y t\303\255nh v\303\240 c\303\264ng ngh\341\273\207 th\303\264ng tin", nullptr));
        chuyen_nganh_input->setItemText(2, QCoreApplication::translate("admin_show", "Khoa h\341\273\215c s\341\273\261 s\341\273\221ng", nullptr));
        chuyen_nganh_input->setItemText(3, QCoreApplication::translate("admin_show", "C\303\264ng ngh\341\273\207 k\341\273\271 thu\341\272\255t", nullptr));
        chuyen_nganh_input->setItemText(4, QCoreApplication::translate("admin_show", "K\341\273\271 thu\341\272\255t ", nullptr));
        chuyen_nganh_input->setItemText(5, QCoreApplication::translate("admin_show", "S\341\272\243n xu\341\272\245t v\303\240 ch\341\272\277 bi\341\272\277n", nullptr));
        chuyen_nganh_input->setItemText(6, QCoreApplication::translate("admin_show", "Ki\341\272\277n tr\303\272c v\303\240 x\303\242y d\341\273\261ng", nullptr));
        chuyen_nganh_input->setItemText(7, QCoreApplication::translate("admin_show", "M\303\264i tr\306\260\341\273\235ng v\303\240 b\341\272\243o v\341\273\207 m\303\264i tr\306\260\341\273\235ng", nullptr));
        chuyen_nganh_input->setItemText(8, QCoreApplication::translate("admin_show", "Kh\303\241c...", nullptr));
        chuyen_nganh_input->setItemText(9, QString());

        ID_Sach_layout->setText(QCoreApplication::translate("admin_show", "ID S\303\241ch", nullptr));
        ID_Sach_input->setText(QString());
        ID_Sach_input->setPlaceholderText(QCoreApplication::translate("admin_show", "ID S\303\241ch s\341\272\275 t\341\273\261 \304\221\341\273\231ng hi\341\273\203n th\341\273\213", nullptr));
        nha_xuat_ban_layout->setText(QCoreApplication::translate("admin_show", "Nh\303\240 xu\341\272\245t b\341\272\243n", nullptr));
        nha_xuat_ban_input->setPlaceholderText(QCoreApplication::translate("admin_show", "Vui l\303\262ng nh\341\272\255p nh\303\240 xu\341\272\245t b\341\272\243n", nullptr));
        nam_xuat_ban_layout->setText(QCoreApplication::translate("admin_show", "N\304\203m xu\341\272\245t b\341\272\243n", nullptr));
        nam_xuat_ban_input->setPlaceholderText(QCoreApplication::translate("admin_show", "Vui l\303\262ng nh\341\272\255p n\304\203m xu\341\272\245t b\341\272\243n", nullptr));
        so_trang_layout->setText(QCoreApplication::translate("admin_show", "S\341\273\221 trang", nullptr));
        so_trang_input->setPlaceholderText(QCoreApplication::translate("admin_show", "Vui l\303\262ng nh\341\272\255p s\341\273\221 trang", nullptr));
        ISBN_layout->setText(QCoreApplication::translate("admin_show", "S\341\273\221 ISBN", nullptr));
        ISBN_input->setPlaceholderText(QCoreApplication::translate("admin_show", "Nh\341\272\255p m\303\243 s\341\273\221 s\303\241ch qu\341\273\221c t\341\272\277 (n\341\272\277u c\303\263)", nullptr));
        language_layout->setText(QCoreApplication::translate("admin_show", "Ng\303\264n ng\341\273\257", nullptr));
        language_input->setPlaceholderText(QCoreApplication::translate("admin_show", "Vui l\303\262ng nh\341\272\255p ng\303\264n ng\341\273\257", nullptr));
        tom_tat_layout->setText(QCoreApplication::translate("admin_show", "T\303\263m t\341\272\257t", nullptr));
        tom_tat_input->setPlaceholderText(QCoreApplication::translate("admin_show", "Nh\341\272\255p n\341\273\231i dung ng\341\272\257n g\341\273\215n c\341\273\247a s\303\241ch", nullptr));
        label_2->setText(QCoreApplication::translate("admin_show", "Nh\341\272\255p s\341\273\221 l\306\260\341\273\243ng", nullptr));
        is_borrow_check->setText(QCoreApplication::translate("admin_show", "Cho ph\303\251p m\306\260\341\273\243n", nullptr));
        is_read_online_check->setText(QCoreApplication::translate("admin_show", "Cho ph\303\251p \304\221\341\273\215c tr\341\273\261c tuy\341\272\277n", nullptr));
        is_download_check->setText(QCoreApplication::translate("admin_show", "Cho ph\303\251p t\341\272\243i v\341\273\201", nullptr));
        link_png_name->setText(QCoreApplication::translate("admin_show", "Nh\341\272\255p h\303\254nh \341\272\243nh s\303\241ch", nullptr));
        link_png_button->setText(QCoreApplication::translate("admin_show", "Ch\341\273\215n file...", nullptr));
        link_png_layout->setText(QString());
        link_pdf_name->setText(QCoreApplication::translate("admin_show", "Nh\341\272\255p file PDF", nullptr));
        link_pdf_button->setText(QCoreApplication::translate("admin_show", "Ch\341\273\215n file...", nullptr));
        link_pdf_layout->setText(QString());
        them_button->setText(QCoreApplication::translate("admin_show", "TH\303\212M", nullptr));
        label->setText(QCoreApplication::translate("admin_show", "Qu\341\272\243n l\303\275 m\306\260\341\273\243n / tr\341\272\243 s\303\241ch", nullptr));
        pushButton_6->setText(QCoreApplication::translate("admin_show", "PushButton", nullptr));
        pushButton_5->setText(QCoreApplication::translate("admin_show", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class admin_show: public Ui_admin_show {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_SHOW_H
