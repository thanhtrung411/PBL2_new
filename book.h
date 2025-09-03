#ifndef BOOK_H
#define BOOK_H
#include <iostream>

using namespace std;
class book
{
    private:
        string ma_sach;
        string anh_sach;
        string ten_sach;
        string tac_gia;
        string nha_xuat_ban;
        string nam_xuat;
        string hinh_thuc;
        string so_trang;
        string ma_Deway;
        string vi_tri_luu_tru;
        string loai_tai_lieu;
        string ISBN;
        string don_gia;
        string ngon_ngu;
        string tu_khoa;
        string chu_de;
        string chuyen_nganh;
        string mo_ta;
    public:
        book(string ma_sach, string anh_sach, string ten_sach, string tac_gia, string nha_xuat_ban,
             string nam_xuat, string hinh_thuc, string so_trang, string ma_Deway, string vi_tri_luu_tru,
             string loai_tai_lieu, string ISBN, string don_gia, string ngon_ngu, string tu_khoa,
             string chu_de, string chuyen_nganh, string mo_ta) {
            this->ma_sach = ma_sach;
            this->anh_sach = anh_sach;
            this->ten_sach = ten_sach;
            this->tac_gia = tac_gia;
            this->nha_xuat_ban = nha_xuat_ban;
            this->nam_xuat = nam_xuat;
            this->hinh_thuc = hinh_thuc;
            this->so_trang = so_trang;
            this->ma_Deway = ma_Deway;
            this->vi_tri_luu_tru = vi_tri_luu_tru;
            this->loai_tai_lieu = loai_tai_lieu;
            this->ISBN = ISBN;
            this->don_gia = don_gia;
            this->ngon_ngu = ngon_ngu;
            this->tu_khoa = tu_khoa;
            this->chu_de = chu_de;
            this->chuyen_nganh = chuyen_nganh;
            this->mo_ta = mo_ta;
        }
        book() {}
        void setMa_sach(string ma_sach) {
            this->ma_sach = ma_sach;
        }
        string getMa_sach() {
            return ma_sach;
        }
        void setAnh_sach(string anh_sach) {
            this->anh_sach = anh_sach;
        }
        string getAnh_sach() {
            return anh_sach;
        }
        void setTen_sach(string ten_sach) {
            this->ten_sach = ten_sach;
        }
        string getTen_sach() {
            return ten_sach;
        }
        void setTac_gia(string tac_gia) {
            this->tac_gia = tac_gia;
        }
        string getTac_gia() {
            return tac_gia;
        }
        void setNha_xuat_ban(string nha_xuat_ban) {
            this->nha_xuat_ban = nha_xuat_ban;
        }
        string getNha_xuat_ban() {
            return nha_xuat_ban;
        }
        void setNam_xuat(string nam_xuat) {
            this->nam_xuat = nam_xuat;
        }
        string getNam_xuat() {
            return nam_xuat;
        }
        void setHinh_thuc(string hinh_thuc) {
            this->hinh_thuc = hinh_thuc;
        }
        string getHinh_thuc() {
            return hinh_thuc;
        }
        void setSo_trang(string so_trang) {
            this->so_trang = so_trang;
        }
        string getSo_trang() {
            return so_trang;
        }
        void setMa_Deway(string ma_Deway) {
            this->ma_Deway = ma_Deway;
        }
        string getMa_Deway() {
            return ma_Deway;
        }
        void setVi_tri_luu_tru(string vi_tri_luu_tru) {
            this->vi_tri_luu_tru = vi_tri_luu_tru;
        }
        string getVi_tri_luu_tru() {
            return vi_tri_luu_tru;
        }
        void setLoai_tai_lieu(string loai_tai_lieu) {
            this->loai_tai_lieu = loai_tai_lieu;
        }
        string getLoai_tai_lieu() {
            return loai_tai_lieu;
        }
        void setISBN(string ISBN) {
            this->ISBN = ISBN;
        }
        string getISBN() {
            return ISBN;
        }
        void setDon_gia(string don_gia) {
            this->don_gia = don_gia;
        }
        string getDon_gia() {
            return don_gia;
        }
        void setNgon_ngu(string ngon_ngu) {
            this->ngon_ngu = ngon_ngu;
        }
        string getNgon_ngu() {
            return ngon_ngu;
        }
        void setTu_khoa(string tu_khoa) {
            this->tu_khoa = tu_khoa;
        }
        string getTu_khoa() {
            return tu_khoa;
        }
        void setChu_de(string chu_de) {
            this->chu_de = chu_de;
        }
        string getChu_de() {
            return chu_de;
        }
        void setChuyen_nganh(string chuyen_nganh) {
            this->chuyen_nganh = chuyen_nganh;
        }
        string getChuyen_nganh() {
            return chuyen_nganh;
        }
        void setMo_ta(string mo_ta) {
            this->mo_ta = mo_ta;
        }
        string getMo_ta() {
            return mo_ta;
        }
};


#endif // BOOK_H
