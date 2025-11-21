#include "library.h"
#include "global.h"
#include <iostream>

Library::Library() :
    books(KeyGetters::getBookID),
    book_copies(KeyGetters::getBookCopiesID),
    authors(KeyGetters::getAuthorID),
    chuyen_nganhs(KeyGetters::getChuyenNganhID),
    the_loais(KeyGetters::getTheLoaiID),
    borrows(KeyGetters::getBorrowID),
    accouts(KeyGetters::getAccoutID) {}

Library::~Library() {}

bool Library::add_book(const book& b) {
    return books.insert(b);
}
bool Library::add_author(const Author& a) {
    return authors.insert(a);
}
bool Library::add_accout(const accout& a) {
    return accouts.insert(a);
}
bool Library::add_book_copy(const Book_copies& bc) {
    return book_copies.insert(bc);
}
bool Library::add_chuyen_nganh(const Chuyen_nganh& cn) {
    return chuyen_nganhs.insert(cn);
}
bool Library::add_the_loai(const The_loai& tl) {
    return the_loais.insert(tl);
}
bool Library::add_borrow(const borrow& br) {
    return borrows.insert(br);
}
bool Library::remove_book(long long book_id) {
    return books.remove_by_Key(book_id);
}
bool Library::remove_author(int author_id) {
    return authors.remove_by_Key(author_id);
}
bool Library::remove_accout(int id) {
    return accouts.remove_by_Key(id);
}
bool Library::remove_book_copy(long long book_copy_id) {
    return book_copies.remove_by_Key(book_copy_id);
}
bool Library::remove_chuyen_nganh(int chuyen_nganh_id) {
    return chuyen_nganhs.remove_by_Key(chuyen_nganh_id);
}
bool Library::remove_the_loai(int the_loai_id) {
    return the_loais.remove_by_Key(the_loai_id);
    return false;
}
bool Library::remove_borrow(long long borrow_id) {
    return borrows.remove_by_Key(borrow_id);
}
int Library::get_total_books() const {
    return books.count_data();
}
int Library::get_total_authors() const {
    return authors.count_data();
}
int Library::get_total_accouts() const {
    return accouts.count_data();
}
int Library::get_total_book_copies() const {
    return book_copies.count_data();
}
int Library::get_total_chuyen_nganhs() const {
    return chuyen_nganhs.count_data();
}
int Library::get_total_the_loais() const {
    return the_loais.count_data();
}
int Library::get_total_borrows() const {
    return borrows.count_data();
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
int Library::dat_sach(long long id_book_, int id_user_, my_time booking_date, int limit_borrow_day, int score_user){
    book b;
    long long id_book_copy;
    my_time current_date = my_time::now();
    try{
        if (!book_data.find(id_book_, b)) {
            throw 1; // khong tim thay sach
        }
        accout a;
        if (!accout_data.find(id_user_, a)) {
            throw 2; // tai khoan khong hop le
        }
        if (a.get_score() == -1){
            throw 2; // tai khoan khong hop le
        }
        if (a.max_book_borrow() <= borrow_data.sach_dang_muon(id_user_)){
            throw 3; // da dat muon qua so luong cho phep
        }
        id_book_copy = book_copy_data.find_id_available_copy(id_book_);
        if (id_book_copy == -1){
            throw 4; // toan bo ban sao cua sach deu dang duoc muon
        }
        if (borrow_data.check_borrowed(id_user_, id_book_)){
            throw 5; // ban da muon cuon sach nay roi
        }
        BST_Borrow qua_han_borrows;
        borrow_user_data.sach_qua_han(id_user_, current_date, qua_han_borrows);
        qua_han_borrows.traverse_ascending([&](borrow &br){
            throw 6; // ban dang co sach qua han chua tra
        });
        borrow br;
        long long new_id_borrow = borrow_data.find_new_id_borrow();
        my_time due_date = current_date + my_time(0,0,limit_borrow_day,0,0,0);
        br.set_id(new_id_borrow);
        br.set_book_copy_id(id_book_copy);
        br.set_id_user(id_user_);
        br.set_id_admin(0); //mac dinh
        br.set_booking_date(current_date);
        br.set_status("Da dat");
        borrow_data.insert(br);
        b.set_tong_sach_dang_dat(b.get_tong_sach_dang_dat() + 1);
        b.set_tong_sach_ranh(b.get_tong_sach_ranh() - 1);
        book_data.update(b, b);
        ghi_borrow(borrow_data);
        ghi_book(book_data);
        return 0;
    }
    catch(int &e){
        return e;
    }
}

// qDebug() << tim_kiem_co_chua("Như bác ơi đó","Như có Bác Hồ trong Như hrhr Như ơi");
//     qDebug() << tim_kiem_chinh_xac("Như bác ơi đó","Như có Bác Hồ trong Như hrhr Như ơi");
//     qDebug() << tim_kiem_chinh_xac("Một hai ba","một hai ba");
//     qDebug() << tim_kiem_bat_dau_bang("Như bác ơi đó","Như bác ơi đó có Bác Hồ trong Như hrhr Như ơi");
/*
type_the_loai: tuy chon the loai
    - Neu type_the_loai == 0 : tim kiem theo tat ca the loai
    - Neu type_the_loai != 0 : tim kiem theo danh sach the loai [type_the_loai-1]
type_tuy_chon: tùy chọn vùng tìm kiếm
    - type_tuy_chon == 0: tìm kiếm sách có trường chứa key
    - type_tuy_chon == 1: tìm kiếm sách có trường chính xác trong key
    - type_tuy_chon == 2: tìm kiếm sách có trường bắt đầu bằng key
type_bieu_ghi: tùy chọn trường cần tìm kiếm
    - type_bieu_ghi == 0: tìm kiếm theo tất cả các trường
    - type_bieu_ghi == 1: tìm kiếm theo trường TÊN SÁCH
    - type_bieu_ghi == 2: tìm kiếm theo trường TÁC GIẢ
    - type_bieu_ghi == 3: tìm kiếm theo trường NHÀ XUẤT BẢN
    - type_bieu_ghi == 4: tìm kiếm theo trường NĂM XUẤT BẢN
    - type_bieu_ghi == 5: tìm kiếm theo trường ISBN
    - type_bieu_ghi == 6: tìm kiếm theo trường NGÔN NGỮ
    - type_bieu_ghi == 7: tìm kiếm theo trường TÓM TẮT
    - type_bieu_ghi == 8: tìm kiếm theo trường CHUYÊN NGÀNH
*/
void search(int type_the_loai, int type_tuy_chon, int& type_bieu_ghi, string& key_word, BST_Book &book_data_, BST_Book &kq_return){
    book_data_.traverse_ascending([&](book &a){
        if (type_the_loai != 0){

        }
    });
}
