#ifndef SETTINGS_FILE_H
#define SETTINGS_FILE_H

#include <iostream>
using namespace std;

class settings_file
{
private:
    static settings_file* instance;
    settings_file();
    int so_lan_gia_han;
    int so_ngay_gia_han;
    int so_sach_moi;
    int so_sach_goi_y;
    int so_ngay_dat_sach;

    long long tien_phat_mat;
    long long tien_phat_hu_hong;
    long long phi_phat_moi_ngay;

    string mat_khau_quen;

public:
    static settings_file* getInstance();
    int get_so_lan_gia_han() const;
    int get_so_sach_moi() const;
    int get_so_sach_goi_y() const;
    int get_so_ngay_dat_sach() const;
    long long get_tien_phat_mat() const;
    long long get_tien_phat_hu_hong() const;
    long long get_phi_phat_moi_ngay() const;
    string get_mat_khau_quen() const;
    int get_so_ngay_gia_han() const;
    void set_so_ngay_gia_han(int x);
    void set_so_lan_gia_han(int x);
    void set_so_sach_moi(int x);
    void set_so_sach_goi_y(int x);
    void set_so_ngay_dat_sach(int x);
    void set_tien_phat_mat(long long x);
    void set_tien_phat_hu_hong(long long x);
    void set_phi_phat_moi_ngay(long long x);
    void doc_file_settings();
    void ghi_file_settings() const;
    void set_mat_khau_quen(const string& x);

};

#endif // SETTINGS_FILE_H
