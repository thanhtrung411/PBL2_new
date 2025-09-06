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

static QString getDataFilePath() {
    // Tìm data/accout.txt từ cạnh .exe, nếu không thấy thì đi lên tối đa 3 cấp
    QDir dir(QCoreApplication::applicationDirPath());
    for (int i = 0; i < 4; ++i) {
        const QString cand = dir.filePath("data/accout.txt");
        if (QFileInfo::exists(cand)) return cand;
        dir.cdUp();
    }
    // Nếu chưa tồn tại, trả về vị trí cạnh .exe (tạo mới khi ghi)
    return QDir(QCoreApplication::applicationDirPath()).filePath("data/accout.txt");
}

void doc_accout(BST_Accout &accout_data);

void ghi_accout(BST_Accout &accout_data);

#endif // MY_FILE_H
