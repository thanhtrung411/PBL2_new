#include "my_file.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include "accout.h"
#include "tree.h"

void doc_accout(BST_Accout &accout_data){
    const QString path = getDataFilePath();
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
        accout_data.insert_Accout(p);
    }
}

void ghi_accout(BST_Accout &accout_data){
    const QString path = getDataFilePath();
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
