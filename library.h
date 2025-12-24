#ifndef LIBRARY_H
#define LIBRARY_H

#include "tree.h"
#include "book.h"
#include "book_copies.h"
#include "the_loai_chuyen_nganh.h"
#include "borrow.h"
#include "Account.h"
#include "my_time.h"
#include "global.h"
#include "settings_file.h"

using namespace std;

class Library {
private:
    BST_Book         book_data;
    BST_book_copy    book_copy_data;
    BST_Chuyen_nganh chuyen_nganh_data;
    BST_The_loai     the_loai_data;
    BST_Borrow       borrow_data;
    BST_Account      account_data;
    BST_Yeu_thich    yeu_thich_data;
    FILE*            peoples;
    Account          acc_sign_in;
    BST_Borrow       borrow_user_data;
    int              is_sign_in = 0;
    int tong_sach_muon;
public:
    Library();
    ~Library();

    void load_data();
    void save_data();

    BST_Book& get_book_data();
    BST_book_copy& get_book_copy_data();
    BST_Chuyen_nganh& get_chuyen_nganh_data();
    BST_The_loai& get_the_loai_data();
    BST_Borrow& get_borrow_data();
    BST_Account& get_account_data();
    BST_Yeu_thich& get_yeu_thich_data();
    Account& get_acc_sign_in();
    int& get_is_sign_in();
    BST_Borrow& get_borrow_user_data();
    int& get_tong_sach_muon();

    //Xử lý sách
    void dat_sach(long long id_book_, int id_user_, my_time booking_date, int limit_borrow, int score_user);
    void muon_sach(borrow &br,long long id_book, long long id_user_, long long id_copy_book_, my_time borrow_date, my_time due_date, bool is_xu_ly);
    void tra_sach(long long id_borrow_, int tinh_trang_sach_, int tien_phat_1, int tien_phat_2, string ghi_chu = "");
    void them_sach(const book& b, int so_luong);
    void xoa_sach(long long id_book_);
    void sua_sach(book& b);
    int gia_han_muon_sach(long long id_borrow_);
    void gia_han_muon_sach_(long long id_borrow_);
    void xu_ly_sach(long long id_borrow_);
    void huy_dat_sach(long long id_borrow_);
    void xac_nhan_muon_sach(long long id_borrow_,my_time borrow_date, my_time due_date);

    //Xử lý bản sao
    void xoa_ban_sao_sach(long long id_copy_book_);

    void xoa_sach_va_ban_sao(long long id_book_);

    //Xử lý tài khoản
    void dang_ky_tai_khoan(Account& ac);
    bool dang_nhap_tai_khoan(Account& ac, string ten_dang_nhap_, string pass_);
    void dang_xuat_tai_khoan();
    void cap_nhat_tai_khoan(Account& a, string& old_pass);
    void quen_mat_khau(string email_, string so_dien_thoai_);
    void khoa_tai_khoan(long long id_account_);
    void mo_khoa_tai_khoan(long long id_account_);
    void khoi_phuc_diem(long long id_account_);
};

#endif // LIBRARY_H
