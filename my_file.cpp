#include "my_file.h"
#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <fstream>
#include "accout.h"
#include "tree.h"
using namespace std;



void doc_accout(BST_Accout &accout_data){
    const QString path = getDataFilePath("data/accout.txt");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file de doc:" << path;
        return;
    }
    QTextStream in(&file);
    bool okCount = false;
    int n = in.readLine().toInt(&okCount);
    if (!okCount) n = 0;

    for (int i = 0; i < n; ++i) {
        const QString user_id    = in.readLine();
        const QString user_name  = in.readLine();
        const QString email      = in.readLine();
        const QString phonenumber= in.readLine();
        const int gioi_tinh      = in.readLine().toInt();
        const int doi_tuong      = in.readLine().toInt();
        const QString ngay_sinh  = in.readLine();
        const QString pass       = in.readLine();
        const QString level      = in.readLine();
        const QString date_created = in.readLine();
        accout p;
        p.setAccout_id(user_id.toStdString());
        p.setAccout_name(user_name.toStdString());
        p.setEmail(email.toStdString());
        p.setPhonenumber(phonenumber.toStdString());
        p.setGioi_tinh(gioi_tinh);
        p.setDoi_tuong(doi_tuong);
        p.setNgay_sinh(ngay_sinh.toStdString());
        p.setPass(pass.toStdString());
        p.setlevel(level.toStdString());
        p.setDate_created(date_created.toStdString());
        accout_data.insert_Accout(p);
    }
}

void ghi_accout(BST_Accout &accout_data){
    const QString path = getDataFilePath("data/accout.txt");
    QDir().mkpath(QFileInfo(path).absolutePath()); // tạo thư mục data nếu chưa có

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Khong the mo file de ghi:" << path;
        return;
    }
    QTextStream out(&file);
    out << accout_data.count_accout() << '\n';
    accout_data.write_accout(out); // cần overload với QTextStream (bên dưới)
    qDebug() << "Ghi file thanh cong:" << path;
}



void doc_book(BST_Book &book_data){
    const QString path = getDataFilePath("data/CSDL.csv");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file de doc:" << path;
        return;
    }
    QTextStream in(&file);
    in.readLine(); //doc tieu de va bo qua
    while (!in.atEnd()) {
        QString qline = in.readLine();
        if (qline.trimmed().isEmpty()) continue;
        qDebug() << qline;
        string line = qline.toUtf8().toStdString();
        book b;
        int idx = 0;
        for (int i = 0 ; i < line.size() ; i++){
            string res = "";
            if (line[i] == '"'){
                i++;
                while (i < line.size() && line[i] != '"'){
                    res += line[i];
                    i++;
                }
                i++;
            }
            else{
                while (i < line.size() && line[i] != ','){
                    res += line[i];
                    i++;
                }
            }
            switch (idx)
            {
            case 0:
                b.set_id_book(res);
                break;
            case 1:
                b.set_name_book(res);
                break;
            case 2:
                b.set_tac_gia(res);
                break;
            case 3:
                b.set_the_loai(res);
                break;
            case 4:
                b.set_nha_xuat_ban(res);
                break;
            case 5: 
                b.set_nam_xuat_ban(res);
                break;
            case 6:
                b.set_so_trang(res);
                break;
            case 7:
                b.set_ISBN(res);
                break;
            case 8:
                b.set_ngon_ngu(res);
                break;
            case 9:
                b.set_tu_khoa(res);
                break;
            case 10:
                b.set_chuyen_nganh(res);
                break;
            case 11:
                b.set_don_gia(res);
                break;
            case 12:
                b.set_tom_tat(res);
                break;
            case 13:
                b.set_link_png(res);
                break;
            case 14:
                b.set_link_pdf(res);
                break;
            case 15:
                b.set_type_book(res);
                break;
            case 16:
                b.set_tinh_trang(res);
                break;
            case 17:
                b.set_date_created(res);
            case 18:
                b.set_admin_created(res);
            default:
                break;
            }
            idx++;
        }
        book_data.insert_Book(b);
    }
    file.close();
}

void ghi_book(BST_Book &book_data){
    const QString path = getDataFilePath("data/CSDL.csv");
    QDir().mkpath(QFileInfo(path).absolutePath()); // tạo thư mục data nếu chưa có

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Khong the mo file de ghi:" << path;
        return;
    }
    QTextStream out(&file);
    book_data.write_book(out); // cần overload với QTextStream (bên dưới)
    qDebug() << "Ghi file thanh cong:" << path;
}

void doc_support_book(BST_string &the_loai_, BST_string &chuyen_nganh_){
    const QString path = getDataFilePath("data/support_book.txt");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file de doc:" << path;
        return;
    }
    QTextStream in(&file);
    int n_the_loai_ = in.readLine().toInt();
    for (int i = 0 ; i < n_the_loai_ ; i++){
        QString qline = in.readLine();
        string line = qline.toUtf8().toStdString();
        the_loai_.insert_string(line);
    }
    int n_chuyen_nganh_ = in.readLine().toInt();
    for (int i = 0 ; i < n_chuyen_nganh_ ; i++){
        QString qline = in.readLine();
        string line = qline.toUtf8().toStdString();
        chuyen_nganh_.insert_string(line);
    }
    file.close();
}

void copy_file(const string& file1, const string& file2){
    ifstream source(file1, ios::binary);
    ofstream dest(file2, ios::binary);
    dest << source.rdbuf();
    source.close();
    dest.close();
}
