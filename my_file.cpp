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
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QFileDialog>
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
    in.readLine(); //doc tieu de va bo qua
    while (!in.atEnd()) {
        QString qline = in.readLine();
        if (qline.trimmed().isEmpty()) continue;
        qDebug() << qline;
        string line = qline.toUtf8().toStdString();
        accout ac;
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
                ac.set_ID(to_int(res));
                break;
            case 1:
                ac.set_ten_dang_nhap(res);
                break;
            case 2:
                ac.set_ten_tai_khoan(res);
                break;
            case 3:
                ac.set_gioi_tinh(to_int(res));
                break;
            case 4:{
                my_time res_time;
                res_time.set_time_date(res);
                ac.set_ngay_sinh(res_time);
                break;
            }
                
            case 5:
                ac.set_email(res);
                break;
            case 6:
                ac.set_doi_tuong(to_int(res));
                break;
            case 7:
                ac.set_phone_number(res);
                break;
            case 8:
                ac.set_pass(res);
                break;
            case 9:
                ac.set_level(res);
                break;
            case 10:{
                my_time res_time;
                res_time.set_time_datetime(res);
                ac.set_date_created(res_time);
                break;
            }
            default:
                break;
            }
            idx++;
        }
        accout_data.insert(ac);
    }
    file.close();
}

void ghi_accout(BST_Accout &accout_data){
    const QString path = getDataFilePath("data/accout.txt");
    QDir().mkpath(QFileInfo(path).absolutePath());
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Khong the mo file de ghi: accout.txt" << path;
        return;
    }
    QTextStream out(&file);
    accout_data.write_accout(out);
    qDebug() << "Ghi file thanh cong:" << path;
}



void doc_book(BST_Book &book_data) {
    const QString path = getDataFilePath("data/CSDL.csv");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    in.readLine();
    while (!in.atEnd()) {
        QString qline = in.readLine();
        if (qline.trimmed().isEmpty()) continue;
        string line = qline.toStdString() + ",";
        book b;
        int idx = 0;
        int i = 0;
        while (i < line.size()) {
            string res = "";
            if (line[i] == '"') {
                i++;
                while (i < line.size() && line[i] != '"') {
                    res += line[i];
                    i++;
                }
                i++;
            } else {
                while (i < line.size() && line[i] != ',') {
                    res += line[i];
                    i++;
                }
            }
            i++;
            switch (idx) {
            case 0: b.set_ID(to_long_long(res)); break;
            case 1: b.set_Name(res); break;
            case 2: b.set_Author(res); break;
            case 3: b.set_NXB(res); break;
            case 4: b.set_NamXB(to_int(res)); break;
            case 5: b.set_So_trang(to_int(res)); break;
            case 6: b.set_ISBN(res); break;
            case 7: b.set_Language(res); break;
            case 8: b.set_Tom_tat(res); break;
            case 9: b.set_Link_png(res); break;
            case 10: b.set_Link_pdf(res); break;
            case 11: b.set_The_loai_ID(to_int(res)); break;
            case 12: b.set_Chuyen_nganh_ID(to_int(res)); break;
            case 13: b.set_is_Read_online(to_bool(res)); break;
            case 14: b.set_is_Download(to_bool(res)); break;
            case 15: b.set_is_Borrow(to_bool(res)); break;
            case 16: b.set_limit_borrow(to_int(res)); break;
            case 17: b.set_luot_xem(to_int(res)); break;
            case 18: b.set_luot_muon(to_int(res)); break;
            case 19: b.set_luot_tai(to_int(res)); break;
            case 20: b.set_tong_sach(to_int(res)); break;
            case 21: b.set_tong_sach_dang_muon(to_int(res)); break;
            case 22: b.set_tong_sach_dang_dat(to_int(res)); break;
            case 23: b.set_tong_sach_ranh(to_int(res)); break;
            case 24: {
                my_time res_time;
                res_time.set_time_datetime(res);
                b.set_Date_created(res_time);
                break;
            }
            case 25: b.set_Created_by(res); break;
            default: break;
            }
            idx++;
        }
        book_data.insert(b);
    }
    file.close();
}

void ghi_book(BST_Book &book_data){
    const QString path = getDataFilePath("data/CSDL.csv");
    QDir().mkpath(QFileInfo(path).absolutePath());

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Khong the mo file de ghi:" << path;
        return;
    }
    QTextStream out(&file);
    book_data.write_book(out);
    qDebug() << "Ghi file thanh cong:" << path;
}

void doc_copy_book(BST_book_copy &book_copy_data){
    const QString path = getDataFilePath("data/Book_copies.csv");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file de doc:" << path;
        return;
    }

    QTextStream in(&file);
    if (!in.atEnd()) in.readLine(); 

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;
        QStringList fields;
        QString currentField;
        bool inQuote = false;

        for (int i = 0; i < line.length(); ++i) {
            QChar c = line[i];
            
            if (c == '"') {
                // Nếu gặp 2 dấu "" liền nhau -> coi là 1 dấu "
                if (inQuote && i + 1 < line.length() && line[i + 1] == '"') {
                    currentField.append('"');
                    i++; // Bỏ qua dấu " tiếp theo
                } else {
                    inQuote = !inQuote; // Bật/tắt trạng thái đang trong ngoặc
                }
            } 
            else if (c == ',' && !inQuote) {
                // Gặp dấu phẩy mà KHÔNG nằm trong ngoặc -> Kết thúc trường
                fields.append(currentField);
                currentField.clear();
            } 
            else {
                currentField.append(c);
            }
        }
        fields.append(currentField); // Thêm trường cuối cùng

        if (fields.size() >= 4) { // Đảm bảo đủ cột
            Book_copies b;
            b.set_id(fields[0].toLongLong());
            b.set_id_book(fields[1].toLongLong());
            b.set_status(fields[2].toStdString());
            b.set_ghi_chu(fields[3].toStdString());

            book_copy_data.insert(b);
        }
    }
    file.close();
}

void ghi_copy_book(BST_book_copy &book_copy_data){
    const QString path = getDataFilePath("data/Book_copies.csv");
    QDir().mkpath(QFileInfo(path).absolutePath()); // tạo thư mục data nếu chưa có

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Khong the mo file de ghi:" << path;
        return;
    }
    QTextStream out(&file);
    book_copy_data.write_book_copy(out); // cần overload với QTextStream (bên dưới)
    qDebug() << "Ghi file thanh cong:" << path;
}

void doc_the_loai(BST_The_loai &the_loai_data){
    const QString path = getDataFilePath("data/The_loai.csv");
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
        The_loai b;
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
                b.set_id(to_int(res));
                break;
            case 1:
                b.set_name(res);
                break;
            default:
                break;
            }
            idx++;
        }
        the_loai_data.insert(b);
    }
    file.close();
}

void ghi_the_loai(BST_The_loai &the_loai_){
    const QString path = getDataFilePath("data/The_loai.csv");
    QDir().mkpath(QFileInfo(path).absolutePath()); // tạo thư mục data nếu chưa có

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Khong the mo file de ghi:" << path;
        return;
    }
    QTextStream out(&file);
    //the_loai_.write_the_loai(out); // cần overload với QTextStream (bên dưới)
    qDebug() << "Ghi file thanh cong:" << path;
}

void doc_chuyen_nganh(BST_Chuyen_nganh& chuyen_nganh_){
    const QString path = getDataFilePath("data/Chuyen_nganh.csv");
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
        Chuyen_nganh b;
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
                b.set_id(to_int(res));
                break;
            case 1:
                b.set_name(res);
                break;
            default:
                break;
            }
            idx++;
        }
        chuyen_nganh_.insert(b);
    }
    file.close();
}

void ghi_chuyen_nganh(BST_Chuyen_nganh &chuyen_nganh_){
    const QString path = getDataFilePath("data/Chuyen_nganh.csv");
    QDir().mkpath(QFileInfo(path).absolutePath()); // tạo thư mục data nếu chưa có

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Khong the mo file de ghi:" << path;
        return;
    }
    QTextStream out(&file);
    //chuyen_nganh_.write_chuyen_nganh(out); // cần overload với QTextStream (bên dưới)
    qDebug() << "Ghi file thanh cong:" << path;
}

void copy_file(const string& file1, const string& file2){
    ifstream source(file1, ios::binary);
    ofstream dest(file2, ios::binary);
    dest << source.rdbuf();
    source.close();
    dest.close();
}
void doc_borrow(BST_Borrow &borrow_data){
    const QString path = getDataFilePath("data/Borrow.csv");
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
        borrow b;
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
            my_time tmp;
            switch (idx)
            {
            case 0:
                b.set_id(to_long_long(res));
                break;
            case 1:
                b.set_book_id(to_long_long(res));
                break;
            case 2:
                b.set_book_copy_id(to_long_long(res));
                break;
            case 3:
                b.set_user_id(to_long_long(res));
                break;
            case 4:
                tmp.set_time_datetime(res);
                b.set_ngay_dat(tmp);
                break;
            case 5:
                tmp.set_time_datetime(res);
                b.set_ngay_muon(tmp);
                break;
            case 6:
                tmp.set_time_datetime(res);
                b.set_ngay_phai_tra(tmp);
                break;
            case 7:
                tmp.set_time_datetime(res);
                b.set_ngay_tra(tmp);
                break;
            case 8:
                b.set_status(res);
                break;
            case 9:
                b.set_lan_gia_han(to_int(res));
                break;
            
            case 10:
                b.set_ghi_chu(res);
                break;
            case 11:
                b.set_tien_phat(to_int(res));
                break;
            default:
                break;
            }
            idx++;
        }
        borrow_data.insert(b);
    }
    file.close();
}
void ghi_borrow(BST_Borrow &borrow_data){
    const QString path = getDataFilePath("data/Borrow.csv");
    QDir().mkpath(QFileInfo(path).absolutePath()); // tạo thư mục data nếu chưa có

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Khong the mo file de ghi:" << path;
        return;
    }
    QTextStream out(&file);
    borrow_data.write_borrow(out); // cần overload với QTextStream (bên dưới)
    qDebug() << "Ghi file thanh cong:" << path;
}

void open_file_PDF(const string& file_path){
    QString qfile_path = getDataFilePath(file_path);

    if (!QFile::exists(qfile_path)) {
        QMessageBox::warning(nullptr, "Lỗi", "Không tìm thấy file PDF!");
        return;
    }

    bool ok = QDesktopServices::openUrl(QUrl::fromLocalFile(qfile_path));
    if (!ok) {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể mở file PDF!");
    }
}
void download_pdf(const string& file_path, const string& save_path){
    QString sourceFile = getDataFilePath(file_path);

    // Kiểm tra file nguồn trước
    if (!QFile::exists(sourceFile)) {
        QMessageBox::warning(nullptr, "Lỗi", "Không tìm thấy file PDF!");
        return;
    }

    // Chọn nơi lưu file
    QString saveFilePath = QFileDialog::getSaveFileName(
        nullptr,
        QObject::tr("Lưu file PDF"),
        QDir::homePath() + "/" + QString::fromStdString(save_path) + ".pdf",
        QObject::tr("PDF (*.pdf);;Tất cả (*)")
    );

    if (saveFilePath.isEmpty()) return;

    // Nếu file đích đã tồn tại thì xóa đi
    if (QFile::exists(saveFilePath)) {
        QFile::remove(saveFilePath);
    }

    // Copy file
    if (QFile::copy(sourceFile, saveFilePath)) {
        QMessageBox::information(nullptr, "Thành công", "Đã lưu file PDF tại: " + saveFilePath);
    } else {
        QMessageBox::warning(nullptr, "Lỗi", "Không thể lưu file PDF!");
    }
}
