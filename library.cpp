#include "library.h"
#include "settings_file.h"
#include "global.h"
#include "exception.h"
#include "tree.h"
#include <iostream>
#include <QMessageBox>

Library::Library() {
    load_data();
}
Library::~Library() {

}


//Ham muon sach
/*
Tra ve:
0: muon sach thanh cong
1: khong tim thay sach
2: tai khoan khong hop le
3: da dat muon qua so luong cho phep
4: toan bo ban sao cua sach deu dang duoc muon
5: ban da muon cuon sach nay roi
6: ban dang co sach qua han chua tra
*/

BST_Book& Library::get_book_data(){
    return book_data;
}
BST_book_copy& Library::get_book_copy_data(){
    return book_copy_data;
}
BST_Chuyen_nganh& Library::get_chuyen_nganh_data(){
    return chuyen_nganh_data;
}
BST_The_loai& Library::get_the_loai_data(){
    return the_loai_data;
}
BST_Borrow& Library::get_borrow_data(){
    return borrow_data;
}
BST_Account& Library::get_account_data(){
    return account_data;
}
BST_Yeu_thich& Library::get_yeu_thich_data(){
    return yeu_thich_data;
}
Account& Library::get_acc_sign_in(){
    return acc_sign_in;
}
int& Library::get_is_sign_in(){
    return is_sign_in;
}
BST_Borrow& Library::get_borrow_user_data(){
    return borrow_user_data;
}
int& Library::get_tong_sach_muon(){
    return tong_sach_muon;
}


void Library::load_data(){
    doc_book(book_data);
    doc_copy_book(book_copy_data);
    doc_chuyen_nganh(chuyen_nganh_data);
    doc_the_loai(the_loai_data);
    doc_borrow(borrow_data);
    doc_Account(account_data);
    yeu_thich_data.load_from_file();
}

void Library::save_data(){
    ghi_book(book_data);
    ghi_copy_book(book_copy_data);
    ghi_chuyen_nganh(chuyen_nganh_data);
    ghi_the_loai(the_loai_data);
    ghi_borrow(borrow_data);
    ghi_Account(account_data);
    yeu_thich_data.write_to_file();
}

void Library::dat_sach(long long id_book_, int id_user_, my_time booking_date, int limit_borrow_day, int score_user){
    book b;
    long long id_book_copy;
    my_time current_date = my_time::now();
    if (!book_data.find(id_book_, b)) {
        throw AppException("Lỗi", "Không tìm thấy sách."); // khong tim thay sach
    }
    Account a;
    if (!account_data.find(id_user_, a)) {
        throw AppException("Lỗi", "Tài khoản không tồn tại."); // tai khoan khong hop le
    }
    if (a.get_score() < 0){
        throw AppException("Từ chối", "Tài khoản của bạn bị khóa hoặc không đủ điểm."); // tai khoan khong hop le
    }
    if (a.max_book_borrow() <= borrow_data.sach_dang_muon(id_user_) + borrow_data.sach_dang_dat(id_user_)){
        throw AppException("Lỗi", "Đã đặt mượn quá số lượng cho phép."); // da dat muon qua so luong cho phep
    }
    id_book_copy = book_copy_data.find_id_available_copy(id_book_);
    if (id_book_copy == -1){
        throw AppException("Lỗi", "Toàn bộ bản sao của sách đều đang được mượn."); // toan bo ban sao cua sach deu dang duoc muon
    }
    if (borrow_data.check_borrowed(id_user_, id_book_)){
        throw AppException("Lỗi", "Bạn đang mượn cuốn sách này."); // ban da muon cuon sach nay roi
    }
    BST_Borrow qua_han_borrows;
    borrow_user_data.sach_qua_han(id_user_, current_date, qua_han_borrows);
    qua_han_borrows.traverse_ascending([&](borrow &br){
        throw AppException("Từ chối", "Bạn đang có sách quá hạn chưa trả."); // ban dang co sach qua han chua tra
    });
    borrow br;
    long long new_id_borrow = borrow_data.find_new_id_borrow();
    my_time due_date = current_date + my_time(0,0,limit_borrow_day,0,0,0);
    br.set_id(new_id_borrow);
    br.set_book_id(id_book_);
    br.set_user_id(id_user_);
    br.set_ngay_dat(booking_date);
    br.set_status("XU_LY");
    borrow_data.insert(br);
    b.set_tong_sach_dang_dat(b.get_tong_sach_dang_dat() + 1);
    b.set_tong_sach_ranh(b.get_tong_sach_ranh() - 1);
    book_data.update(b, b);
    record.log_action(
        a.get_ten_dang_nhap(),
        ActionType::RESERVE_BOOK,
        br.get_id(),
        "Đặt sách ID: " + to_stringll_(br.get_book_id()) + ", Bản sao ID: " + to_stringll_(id_book_copy)
    );
    ghi_borrow(borrow_data);
    ghi_book(book_data);
}

void Library::muon_sach(borrow &br,long long id_book_, long long id_user_, long long id_copy_book_, my_time borrow_date, my_time due_date, bool is_xu_ly){
    book b;
    long long id_book_copy;
    my_time current_date = my_time::now();
    if (id_book_ == 0 || !book_data.find(id_book_, b)) {
        throw AppException("Lỗi", "Không tìm thấy sách."); // khong tim thay sach
    }
    Account a;
    if (id_user_ == 0 || !account_data.find(id_user_, a)) {
        throw AppException("Lỗi", "Tài khoản không tồn tại."); // tai khoan khong hop le
    }
    if (a.get_score() < 0 || a.get_doi_tuong() == -1){
        throw AppException("Từ chối", "Tài khoản bị khóa hoặc không đủ điểm."); // tai khoan khong hop le
    }
    if (a.max_book_borrow() <= borrow_data.sach_dang_muon(id_user_)){
        throw AppException("Lỗi", "Đã mượn quá số lượng cho phép."); // da dat muon qua so luong cho phep
    }
    id_book_copy = book_copy_data.find_id_available_copy(id_book_);
    if (id_book_copy == -1){
        throw AppException("Lỗi", "Toàn bộ bản sao của sách đều đang được mượn."); // toan bo ban sao cua sach deu dang duoc muon
    }
    BST_Borrow qua_han_borrows;
    borrow_user_data.sach_qua_han(id_user_, current_date, qua_han_borrows);
    qua_han_borrows.traverse_ascending([&](borrow &br){
        throw AppException("Từ chối", "Bạn đang có sách quá hạn chưa trả."); // ban dang co sach qua han chua tra
    });
    if (br.get_book_id() == 0){
        if (borrow_data.check_borrowed(id_user_, id_book_)){
            throw AppException("Lỗi", "Bạn đã mượn cuốn sách này rồi."); // ban da muon cuon sach nay roi
        }
        long long new_id_borrow = borrow_data.find_new_id_borrow();
        br.set_id(new_id_borrow);
        br.set_book_id(id_book_);
        br.set_book_copy_id(id_book_copy);
        br.set_user_id(id_user_);
        br.set_ngay_muon(borrow_date);
        br.set_ngay_phai_tra(due_date);
        br.set_status("DANG_MUON");
        borrow_data.insert(br);

    }
    else{
        br.set_book_copy_id(id_book_copy);
        br.set_ngay_muon(borrow_date);
        br.set_ngay_phai_tra(due_date);
        br.set_status("DANG_MUON");
        borrow_data.update(br, br);
    }
    if (!is_xu_ly){
        b.set_tong_sach_dang_muon(b.get_tong_sach_dang_muon() + 1);
        b.set_tong_sach_ranh(b.get_tong_sach_ranh() - 1);
    }
    b.set_luot_muon(b.get_luot_muon() + 1);
    book_data.update(b, b);
    Book_copies bc;
    if (book_copy_data.find(id_book_copy, bc)) {
        bc.set_status("DA_MUON");
        book_copy_data.update(bc, bc);
    }
    record.log_action(
        a.get_ten_dang_nhap(),
        ActionType::BORROW_BOOK,
        br.get_id(),
        "Mượn sách ID: " + to_stringll_(br.get_book_id()) + ", Bản sao ID: " + to_stringll_(br.get_book_copy_id())
    );
    save_data();
}

int Library::gia_han_muon_sach(long long id_borrow_) {
    try {
        borrow br;
        if (!borrow_data.find(id_borrow_, br)) {
            return 1; // Khong tim thay ban ghi muon sach
        }

        book b;
        if (book_data.find(br.get_book_id(), b)) {
            if (b.get_tong_sach_ranh() <= 0) {
                return 2; // LOI_KHAN_HIEM
            }
        }

        my_time current_date = my_time::now();
        if (br.get_ngay_phai_tra() < current_date) {
            return 3; // LOI_QUA_HAN
        }

        if (br.get_lan_gia_han() >= settings_file::getInstance()->get_so_lan_gia_han()) {
            return 4; // LOI_HET_LUOT
        }

        my_time new_due_date =
            br.get_ngay_phai_tra().extend_date(settings_file::getInstance()->get_so_ngay_gia_han());
        br.set_ngay_phai_tra(new_due_date);
        br.set_lan_gia_han(br.get_lan_gia_han() + 1);
        borrow_data.update(br, br);
        ghi_borrow(borrow_data);

        return 0;
    } catch (...) {
        return -1; // LOI_HE_THONG
    }
    save_data();
}

void Library::gia_han_muon_sach_(long long id_borrow_){
 borrow br;
    if (!borrow_data.find(id_borrow_, br)) {
        throw AppException("Lỗi", "Không tìm thấy bản ghi mượn sách.");
    }

    book b;
    if (!book_data.find(br.get_book_id(), b)) {
        throw AppException("Lỗi", "Không tìm thấy đầu sách.");
    }

    // Không cho gia hạn nếu không còn sách rảnh
    if (b.get_tong_sach_ranh() <= 0) {
        throw AppException(
            "Từ chối",
            "Không thể gia hạn vì không còn sách rảnh."
        );
    }

    my_time current_date = my_time::now();

    // Không cho gia hạn nếu đã quá hạn
    if (br.get_ngay_phai_tra() < current_date) {
        throw AppException(
            "Từ chối",
            "Sách đã quá hạn, không thể gia hạn."
        );
    }

    // Hết lượt gia hạn
    if (br.get_lan_gia_han() >=
        settings_file::getInstance()->get_so_lan_gia_han())
    {
        throw AppException(
            "Từ chối",
            "Đã hết số lần gia hạn cho phép."
        );
    }

    // Gia hạn
    my_time new_due =
        br.get_ngay_phai_tra()
            .extend_date(settings_file::getInstance()->get_so_ngay_gia_han());

    br.set_ngay_phai_tra(new_due);
    br.set_lan_gia_han(br.get_lan_gia_han() + 1);

    borrow_data.update(br, br);

    record.log_action(
        acc_sign_in.get_ten_dang_nhap(),
        ActionType::EXTEND_BORROW,
        br.get_id(),
        "Gia hạn mượn sách ID: " + to_stringll_(br.get_id())
    );

    save_data();
}


void Library::tra_sach(long long id_borrow_, int tinh_trang_sach_, int tien_phat_1, int tien_phat_2, string ghi_chu){
    borrow br;
    if (!borrow_data.find(id_borrow_, br)) {
        throw AppException("Lỗi", "Không tìm thấy bản ghi mượn sách."); // khong tim thay ban ghi muon sach
    }

    switch (tinh_trang_sach_) {
        case 0: { // tot
            br.set_tinh_trang_sach(TOT);
            break;
        }
        case 1: { //binh thuong
            br.set_tinh_trang_sach(BINH_THUONG);
            break;
        }
        case 2: { //hu hong
            br.set_tinh_trang_sach(HONG);
            break;
        }
        case 3: { //mat sach
            br.set_tinh_trang_sach(MAT);
            break;
        }
        default:
            throw AppException("Lỗi", "Tình trạng sách không hợp lệ."); // tinh trang sach khong hop le
            break;
    }
    
    if (tien_phat_1 > 0){
        br.set_status(TRA_QUA_HAN);
    } else {
        br.set_status(TRA_DUNG_HAN);
    }
    book b;
    if (book_data.find(br.get_book_id(), b)) {
        b.set_tong_sach_dang_muon(b.get_tong_sach_dang_muon() - 1);
        b.set_tong_sach_ranh(b.get_tong_sach_ranh() + 1);
        book_data.update(b, b);
    }
    else {
        throw AppException("Lỗi", "Không tìm thấyđầu sách."); // khong tim thay sach
    }
    Book_copies bc;
    if (book_copy_data.find(br.get_book_copy_id(), bc)) {
        bc.set_status("RANH");
        book_copy_data.update(bc, bc);
    }
    else {
        throw AppException("Lỗi", "Không tìm thấy bản sao sách."); // khong tim thay ban sao sach
    }
    my_time current_date = my_time::now();
    br.set_ngay_tra(current_date);
    long long tong_tien_phat = tien_phat_1 + tien_phat_2;
    br.set_tien_phat(tong_tien_phat);
    br.set_ghi_chu(ghi_chu);
    borrow_data.update(br, br);
    if (tong_tien_phat > 0){
        Account a;
        if (account_data.find(br.get_user_id(), a)) {
            a.set_score(a.get_score() - 2);
            account_data.update(a, a);
        }
    }
    else {
        Account a;
        if (account_data.find(br.get_user_id(), a)) {
            a.set_score(a.get_score() + 1);
            account_data.update(a, a);
        }
    }
    save_data();
}

void Library::them_sach(const book& b, int so_luong){
    book_data.insert(b);
    for (int i = 0; i < so_luong; i++){
        Book_copies bc;
        long long id_copy = book_copy_data.find_max_id() + 1;
        bc.set_id(id_copy);
        bc.set_id_book(b.get_ID());
        bc.set_status("available");
        book_copy_data.insert(bc);
    }
    record.log_action(lib.get_acc_sign_in().get_ten_dang_nhap(), ActionType::ADD_BOOK, b.get_ID(), "Đã thêm sách " + to_stringll_(b.get_ID()) + " - " + b.get_Name());
    save_data();
}

void Library::xoa_sach(long long id_book_){
    book b;
    if (!book_data.find(id_book_, b)) {
        throw AppException("Lỗi", "Không tìm thấy sách."); // khong tim thay sach
    }
    book_data.remove_by_Key(id_book_);
    book_copy_data.remove_by_book_id(id_book_);
    save_data();
}

void Library::sua_sach(book& b){
    book old_b;
    if (!book_data.find(b.get_ID(), old_b)) {
        throw AppException("Lỗi", "Không tìm thấy sách."); // khong tim thay sach
    }
    book_data.update(old_b, b);
    record.log_action(lib.get_acc_sign_in().get_ten_dang_nhap(), ActionType::ADJ_BOOK, b.get_ID(), "Đã sửa thông tin sách " + to_stringll_(b.get_ID()) + " - " + b.get_Name());
    save_data();
}

void Library::xoa_ban_sao_sach(long long id_copy_book_){
    Book_copies bc;
    if (!book_copy_data.find(id_copy_book_, bc)) {
        throw AppException("Lỗi", "Không tìm thấy bản sao sách."); // khong tim thay ban sao sach
    }
    book_copy_data.remove_by_Key(id_copy_book_);
    save_data();
}

void Library::xoa_sach_va_ban_sao(long long id_book_){
    book b;
    if (!book_data.find(id_book_, b)) {
        throw AppException("Lỗi", "Không tìm thấy sách."); // khong tim thay sach
    }
    if (b.get_tong_sach_dang_muon() > 0 || b.get_tong_sach_dang_dat() > 0){
        throw AppException("Lỗi", "Không thể xóa sách đang có người mượn hoặc đặt."); // khong the xoa sach dang co nguoi muon hoac dat
    }
    book_data.remove_by_Key(id_book_);
    book_copy_data.remove_by_book_id(id_book_);
    record.log_action(lib.get_acc_sign_in().get_ten_dang_nhap(), ActionType::ADJ_BOOK, b.get_ID(), "Đã xóa sách " + to_stringll_(b.get_ID()) + " - " + b.get_Name());
    save_data();
}

void Library::xu_ly_sach(long long id_borrow_){
    borrow br;
    if (!borrow_data.find(id_borrow_, br)) {
        throw AppException("Lỗi", "Không tìm thấy bản ghi mượn sách."); // khong tim thay ban ghi muon sach
    }
    if (br.get_status() != XU_LY){
        throw AppException("Lỗi", "Chỉ có thể xử lý sách đang trong trạng thái 'XU_LY'."); // chi xu ly duoc sach dang xu ly
    }
    br.set_status(SAN_SANG);
    borrow_data.update(br, br);
    book b;
    if (book_data.find(br.get_book_id(), b)) {
        b.set_tong_sach_dang_dat(b.get_tong_sach_dang_dat() - 1);
        b.set_tong_sach_dang_muon(b.get_tong_sach_dang_muon() + 1);
        book_data.update(b, b);
    }
    else {
        throw AppException("Lỗi", "Không tìm thấy đầu sách."); // khong tim thay sach
    }
    record.log_action(lib.get_acc_sign_in().get_ten_dang_nhap(), ActionType::CONFIRM_BOOK, br.get_id(), "Đã xử lý đặt sách ID: " + to_stringll_(br.get_id()));
    save_data();

}
void Library::huy_dat_sach(long long id_borrow_){
    borrow br;
    if (!borrow_data.find(id_borrow_, br)) {
        throw AppException("Lỗi", "Không tìm thấy bản ghi mượn sách."); // khong tim thay ban ghi muon sach
    }
    if (br.get_status() != XU_LY){
        throw AppException("Lỗi", "Chỉ có thể hủy đặt sách đang trong trạng thái 'XU_LY'."); // chi huy duoc dat sach dang xu ly
    }
    borrow_data.remove_by_Key(id_borrow_);
    book b;
    if (book_data.find(br.get_book_id(), b)) {
        b.set_tong_sach_dang_dat(b.get_tong_sach_dang_dat() - 1);
        b.set_tong_sach_ranh(b.get_tong_sach_ranh() + 1);
        book_data.update(b, b);
    }
    save_data();
}

void Library::xac_nhan_muon_sach(long long id_borrow_,my_time borrow_date, my_time due_date){
    borrow br;
    if (!borrow_data.find(id_borrow_, br)) {
        throw AppException("Lỗi", "Không tìm thấy yêu cầu đặt sách.");
    }

    if (br.get_status() != SAN_SANG && br.get_status() != XU_LY) {
        throw AppException("Lỗi", "Trạng thái yêu cầu không hợp lệ.");
    }

    // Gọi lại logic mượn sách có sẵn
    muon_sach(br,
              br.get_book_id(),
              br.get_user_id(),
              0,
              borrow_date,
              due_date,false);

    record.log_action(
        acc_sign_in.get_ten_dang_nhap(),
        ActionType::BORROW_BOOK,
        id_borrow_,
        "Xác nhận mượn sách từ yêu cầu đặt ID: " +
        to_stringll_(id_borrow_)
    );

    save_data();
}

bool Library::dang_nhap_tai_khoan(Account& ac, string ten_dang_nhap_, string pass_){
    if (ten_dang_nhap_.empty() || pass_.empty()){
        throw AppException("Lỗi", "Tên đăng nhập và mật khẩu không được để trống."); // ten dang nhap hoac mat khau rong
    }
    if (account_data.check_Account(ten_dang_nhap_, pass_, ac)) {
        ac.giai_ma_();
        if (ac.get_doi_tuong() == -1){
            throw AppException("Từ chối", "Tài khoản đã bị khóa.\nLiên hệ quản trị viên để biết thêm chi tiết."); // tai khoan bi khoa
        }
        acc_sign_in = ac;
        is_sign_in = 1;
        borrow_user_data.clear();
        borrow_data.info_user(acc_sign_in.get_ID(), borrow_user_data);
        account_data.traverse_ascending([&](Account &a){
                a.giai_ma_();
        });
        record.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::LOGIN, 0, "Đã đăng nhập vào hệ thống.");
        return true;
    } else {
        throw AppException("Lỗi", "Tên đăng nhập hoặc mật khẩu không đúng."); // ten dang nhap hoac mat khau sai
    }
}

void Library::dang_ky_tai_khoan(Account& ac){
    account_data.insert(ac);
    if (is_sign_in){
    }
    else {
        acc_sign_in = ac;
        is_sign_in = 1;
        account_data.traverse_ascending([this](Account& a){
            a.giai_ma_();
        });
        borrow_user_data.clear();
        borrow_data.info_user(acc_sign_in.get_ID(), borrow_user_data);
    }
    record.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::REGISTER, ac.get_ID(), "Đã đăng ký tài khoản " + to_stringll_(ac.get_ID()) + " - " + ac.get_ten_tai_khoan());
    ghi_Account(account_data);
}

void Library::dang_xuat_tai_khoan(){
    record.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::REGISTER, 0, "Đã đăng xuất khỏi hệ thống.");
    acc_sign_in = Account();
    is_sign_in = 0;
    borrow_user_data.clear();
    account_data.traverse_ascending([this](Account& a){
        a.ma_hoa_();
    });
}
void Library::quen_mat_khau(string email_, string so_dien_thoai_){
    Account a;
    if (account_data.check_quen_mat_khau(so_dien_thoai_,email_, a)){
        account_data.traverse_ascending([this](Account& a){
            a.giai_ma_();
        });
         record.log_action(a.get_ten_dang_nhap(), ActionType::RESET_PASSWORD, a.get_ID(), "Đã yêu cầu đặt lại mật khẩu.");
        a.giai_ma_();
        acc_sign_in = a;
        is_sign_in = 1;
        borrow_user_data.clear();
        borrow_data.info_user(acc_sign_in.get_ID(), borrow_user_data);
        account_data.update(a, a);
        ghi_Account(account_data);
    }
    else {
        throw AppException("Lỗi", "Thông tin không hợp lệ."); // thong tin khong hop le
    }
}

void Library::khoa_tai_khoan(long long id_account_){
    Account a;
    if (!account_data.find(id_account_, a)) {
        throw AppException("Lỗi", "Không tìm thấy tài khoản."); // khong tim thay tai khoan
    }
    a.set_doi_tuong(-1);
    account_data.update(a, a);
    ghi_Account(account_data);
}
void Library::mo_khoa_tai_khoan(long long id_account_){
    Account a;
    if (!account_data.find(id_account_, a)) {
        throw AppException("Lỗi", "Không tìm thấy tài khoản."); // khong tim thay tai khoan
    }
    a.set_doi_tuong(0);
    account_data.update(a, a);
    ghi_Account(account_data);
}

void Library::cap_nhat_tai_khoan(Account& a, string& old_pass){

    // Kiểm tra mật khẩu cũ
    if (old_pass != acc_sign_in.get_pass()) {
        throw AppException("Lỗi", "Mật khẩu hiện tại không đúng.");
    }

    // Kiểm tra email
    if (!is_valid_email(a.get_email())) {
        throw AppException("Lỗi", "Email không đúng định dạng.");
    }

    // Kiểm tra số điện thoại
    const string& phone = a.get_phone_number();
    if (phone.size() < 10 || phone.size() > 11 || phone[0] != '0') {
        throw AppException("Lỗi", "Số điện thoại không hợp lệ.");
    }

    // Kiểm tra trùng tên đăng nhập (trừ chính mình)
    if (account_data.check_ten_dang_nhap(a.get_ten_dang_nhap()) &&
        a.get_ten_dang_nhap() != acc_sign_in.get_ten_dang_nhap())
    {
        throw AppException("Lỗi", "Tên đăng nhập đã tồn tại.");
    }

    // Cập nhật
    Account old_acc = acc_sign_in;
    acc_sign_in = a;

    account_data.update(old_acc, acc_sign_in);

    record.log_action(
        acc_sign_in.get_ten_dang_nhap(),
        ActionType::ADJ_USER,
        acc_sign_in.get_ID(),
        "Cập nhật thông tin cá nhân"
    );

    save_data();
}

void Library::khoi_phuc_diem(long long id_account_){
    Account a;
    if (!account_data.find(id_account_, a)) {
        throw AppException("Lỗi", "Không tìm thấy tài khoản."); // khong tim thay tai khoan
    }
    a.set_score(10);
    account_data.update(a, a);
    ghi_Account(account_data);
}
