#ifndef MY_FILE_H
#define MY_FILE_H

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include "accout.h"
#include "tree.h"
#include "book.h"

static QString getDataFilePath(string link) {
    // Tìm data/accout.txt từ cạnh .exe, nếu không thấy thì đi lên tối đa 3 cấp
    QDir dir(QCoreApplication::applicationDirPath());
    for (int i = 0; i < 4; ++i) {
        const QString cand = dir.filePath(link.c_str());
        if (QFileInfo::exists(cand)) return cand;
        dir.cdUp();
    }
    // Nếu chưa tồn tại, trả về vị trí cạnh .exe (tạo mới khi ghi)
    return QDir(QCoreApplication::applicationDirPath()).filePath(link.c_str());
}

void doc_accout(BST_Accout &accout_data);

void ghi_accout(BST_Accout &accout_data);

void doc_book(BST_Book &book_data);

void ghi_book(BST_Book &book_data);

void doc_support_book(BST_string &the_loai_, BST_string &chuyen_nganh_);

void ghi_support_book(BST_string &support_book_data);

void copy_file(const string& file1, const string& file2);

#endif // MY_FILE_H
