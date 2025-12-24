#include "settings_file.h"
#include "my_string.h"
#include <iostream>
#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QTextStream>
#include <QDir>
#include <QCoreApplication>

settings_file* settings_file::instance = nullptr;

settings_file* settings_file::getInstance() {
    if (instance == nullptr) {
        instance = new settings_file();
    }
    return instance;
}


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

settings_file::settings_file() {
    so_lan_gia_han = 2;
    so_sach_moi = 8;
    so_sach_goi_y = 8;
    so_ngay_dat_sach = 3;
    so_ngay_gia_han = 7;
    tien_phat_mat = 100000;
    tien_phat_hu_hong = 50000;
    phi_phat_moi_ngay = 5000;
    mat_khau_quen = "12345678";
    so_quyen_muon_toi_da = 2;
}
int settings_file::get_so_lan_gia_han() const {
    return so_lan_gia_han;
}
int settings_file::get_so_sach_moi() const {
    return so_sach_moi;
}
int settings_file::get_so_sach_goi_y() const {
    return so_sach_goi_y;
}
int settings_file::get_so_ngay_dat_sach() const {
    return so_ngay_dat_sach;
}
long long settings_file::get_tien_phat_mat() const {
    return tien_phat_mat;
}
long long settings_file::get_tien_phat_hu_hong() const {
    return tien_phat_hu_hong;
}
long long settings_file::get_phi_phat_moi_ngay() const {
    return phi_phat_moi_ngay;
}
string settings_file::get_mat_khau_quen() const {
    return mat_khau_quen;
}
int settings_file::get_so_ngay_gia_han() const {
    return so_ngay_gia_han;
}
void settings_file::set_so_ngay_gia_han(int x) {
    so_ngay_gia_han = x;
}
void settings_file::set_mat_khau_quen(const string& x) {
    mat_khau_quen = x;
}
void settings_file::set_so_lan_gia_han(int x) {
    so_lan_gia_han = x;
}
void settings_file::set_so_sach_moi(int x) {
    so_sach_moi = x;
}
void settings_file::set_so_sach_goi_y(int x) {
    so_sach_goi_y = x;
}
void settings_file::set_so_ngay_dat_sach(int x) {
    so_ngay_dat_sach = x;
}
void settings_file::set_tien_phat_mat(long long x) {
    tien_phat_mat = x;
}
void settings_file::set_tien_phat_hu_hong(long long x) {
    tien_phat_hu_hong = x;
}
void settings_file::set_phi_phat_moi_ngay(long long x) {
    phi_phat_moi_ngay = x;
}
void settings_file::set_so_quyen_muon_toi_da(int x) {
    so_quyen_muon_toi_da = x;
}
int settings_file::get_so_quyen_muon_toi_da() const {
    return so_quyen_muon_toi_da;
}
void settings_file::doc_file_settings() {
    const QString path = getDataFilePath("data/settings.csv");
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Khong the mo file de doc:" << path;
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        const QString qline = in.readLine().trimmed();
        if (qline.isEmpty()) continue;

        const QStringList parts = qline.split(',');
        if (parts.size() < 2) continue;

        const QString key = parts[0].trimmed();
        const QString value = parts[1].trimmed();

        if (key == "SO_LAN_GIA_HAN") {
            so_lan_gia_han = value.toInt();
        } else if (key == "SO_SACH_MOI") {
            so_sach_moi = value.toInt();
        } else if (key == "SO_SACH_GOI_Y") {
            so_sach_goi_y = value.toInt();
        } else if (key == "SO_NGAY_DAT_SACH") {
            so_ngay_dat_sach = value.toInt();
        } else if (key == "TIEN_PHAT_MAT") {
            tien_phat_mat = value.toLongLong();
        } else if (key == "TIEN_PHAT_HU_HONG") {
            tien_phat_hu_hong = value.toLongLong();
        } else if (key == "PHI_PHAT_MOI_NGAY") {
            phi_phat_moi_ngay = value.toLongLong();
        } else if (key == "SO_NGAY_GIA_HAN") {
            so_ngay_gia_han = value.toInt();
        } else if (key == "MAT_KHAU_QUEN") {
            mat_khau_quen = value.toStdString();
        } else if (key == "SO_QUYEN_MUON_TOI_DA") {
            so_quyen_muon_toi_da = value.toInt();
        }
    }
    file.close();
}

void settings_file::ghi_file_settings() const {
    const QString path = getDataFilePath("data/settings.csv");
    QDir().mkpath(QFileInfo(path).absolutePath());

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "Khong the mo file de ghi:" << path;
        return;
    }
    QTextStream out(&file);
    out << "SO_LAN_GIA_HAN," << so_lan_gia_han << "\n";
    out << "SO_SACH_MOI," << so_sach_moi << "\n";
    out << "SO_SACH_GOI_Y," << so_sach_goi_y << "\n";
    out << "SO_NGAY_DAT_SACH," << so_ngay_dat_sach << "\n";
    out << "TIEN_PHAT_MAT," << tien_phat_mat << "\n";
    out << "TIEN_PHAT_HU_HONG," << tien_phat_hu_hong << "\n";
    out << "PHI_PHAT_MOI_NGAY," << phi_phat_moi_ngay << "\n";
    out << "SO_NGAY_GIA_HAN," << so_ngay_gia_han << "\n";
    out << "MAT_KHAU_QUEN," << QString::fromStdString(mat_khau_quen) << "\n";
    out << "SO_QUYEN_MUON_TOI_DA," << so_quyen_muon_toi_da << "\n";
    file.close();
}

