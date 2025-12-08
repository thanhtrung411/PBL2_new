#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <QTextStream>
#include <functional>
#include "accout.h"
#include "book.h"
#include "the_loai_chuyen_nganh.h"
#include "author.h"
#include "book_copies.h"
#include "borrow.h"
#include "history.h"
#include "description.h"
#include "yeu_thich.h"
using namespace std;

class accout;
class book;
class Book_copies;
class Author;
class Chuyen_nganh;
class The_loai;
class borrow;
class my_time;

class BST_Book_by_Name;
class BST_Book_by_Author;
class BST_Book_by_The_loai;
class BST_Book_by_Chuyen_nganh;

class BST_The_loai;
class BST_Chuyen_nganh;

template <typename T>

class Node{
private:
    T data;
    Node<T>* left;
    Node<T>* right;
    int height;
    int size;
public:
    explicit Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1), size(1) {}
    void setData(const T& value) {
        data = value;
    }
    void setLeft(Node<T>* left) {
        this->left = left;
    }
    void setRight(Node<T>* right) {
        this->right = right;
    }
    void setHeight(int h) {
        height = h;
    }
    T& getData() {
        return data;
    }
    Node<T>*& getLeft() {
        return left;
    }
    Node<T>*& getRight() {
        return right;
    }
    int getHeight() const {
        return height;
    }
    int getSize() const {
        return size;
    }
    void setSize(int s) {
        size = s;
    }

};

template <typename T, typename Key>
class BST{
protected:
    Node<T>* root;
    Key (*getKey)(const T&);
    int height(Node<T>* node) const;
    int size(Node<T>* node) const;
    int getBalanceFactor(Node<T>* node) const;
    void updateHeight(Node<T>* node);
    Node<T>* rightRotate(Node<T>* y);
    Node<T>* leftRotate(Node<T>* x);
    Node<T>* balance(Node<T>* node);

    Node<T>* add_Node(Node<T>* node, const T& value, int &ok);
    Node<T>* search_Node(Node<T>* node, const Key& key);
    Node<T>* delete_Node(Node<T>* node, T data, int &ok);
    Node<T>* copy_tree(Node<T>* node);

    void in_order_recursive(Node<T>* node, std::function<void(T&)> visit_func);
    void pre_order_recursive(Node<T>* node, std::function<void(T&)> visit_func);
    void in_order_reverse_recursive(Node<T>* node, std::function<void(T&)> visit_func);
    int count(Node<T>* node) const;
    void destroy_Node(Node<T>* node);
    Key find_max_key(Node<T>* node) const;
public:
    BST(Key (*getter)(const T&)): root(nullptr), getKey(getter) {}
    BST(const BST& other): getKey(other.getKey) {
        root = copy_tree(other.root);
    }
    BST& operator=(const BST& other) {
        if (this != &other) {
            destroy_Node(root);
            root = copy_tree(other.root);
            getKey = other.getKey;
        }
        return *this;
    }
    ~BST();
    bool insert(const T& value);
    bool remove_by_Key(const Key& id);
    bool find(Key id, T& result);
    bool update(T &old_, T &new_);
    Key find_max_id() const;
    int count_data() const;
    T operator[](int index);
    void clear(){
        destroy_Node(root);
        root = nullptr;
    }
    void traverse_ascending(std::function<void(T&)> visit_func) {
        in_order_recursive(root, visit_func);
    }
    void traverse_descending(std::function<void(T&)> visit_func) {
        in_order_reverse_recursive(root, visit_func);
    }
};
namespace KeyGetters {
    int getAccoutID(const accout& a);
    long long getBookID(const book& b);
    long long getBookCopiesID(const Book_copies& bc);
    int getAuthorID(const Author& au);
    int getTheLoaiID(const The_loai& tl); 
    int getChuyenNganhID(const Chuyen_nganh& cn);
    long long getBorrowID(const borrow& br);
    string getStringID(const string& s);
    string getNameBook(const book& b);
    string getAuthorName(const book& b);
    my_time getMyTimeID(const history_record& t);
    inline string lower(string s);
    std::pair<string,long long> getKey_Name_ID   (const book& b);
    std::pair<string,long long> getKey_Author_ID (const book& b);
    std::pair<string,long long> getKey_TL_ID     (const book& b);
    std::pair<string,long long> getKey_CN_ID     (const book& b);
    std::pair<int,long long>    getKey_DoCX_ID   (const book& b);
    std::pair<my_time,long long> getKey_History_ID(const history_record& h);
    std::pair<my_time,long long>getKey_DateCreated_ID   (const book& b);
    std::pair<long long, long long> getKey_YeuThich_ID(const yeu_thich& yt);
    std::pair<int,long long> getKey_LuotXem_ID(const book& b);
    std::pair<int,long long> getKey_LuotMuon_ID(const book& b);

}

class BST_Accout : public BST<accout, int> {
private:
    bool search_custom(int type_tuy_chon, string& type_bieu_ghi, string& key_word, accout& a);
    int count_doc_gia_helper(Node<accout>* node);
    int count_thu_thu_helper(Node<accout>* node);
    Node<accout>* check_accout_helper(Node<accout>* node, string ten_dang_nhap, string pass, int &ok, accout &a);
public:
    BST_Accout() : BST<accout, int>(KeyGetters::getAccoutID) {}
    int count_doc_gia();
    bool check_ten_dang_nhap(string ten_dang_nhap);
    bool check_quen_mat_khau(string so_dien_thoai, string email, accout &a);
    int count_thu_thu();
    void tim_thu_thu(BST_Accout &u);
    void tim_doc_gia(BST_Accout &u);
    bool check_accout(string ten_dang_nhap, string pass, accout& a); 
    void write_csv(Node<accout>* node, QTextStream &out) const;
    void write_accout(QTextStream &out) const;
};

class BST_Book : public BST<book, long long> {
private:
    bool search_custom_trung_gian(int type_tuy_chon, int& type_bieu_ghi, string& key_word, book& a);
    Node<book>* write_book_helper(Node<book>* node, QTextStream &out) const;
    Node<book>* search_help(int type_the_loai, int type_tuy_chon, int& type_bieu_ghi, string& key_word, Node<book>* node, BST_Book &kq_return);
    Node<book>* tong_hop_sach_TL_CN_Node(int The_loai_ID, int Chuyen_nganh_ID, Node<book>* node, BST_Book &b);
    Node<book>* author_of_book_helper(int author_id, Node<book>* node, BST_Book &b);
    Node<book>* the_loai_of_book_helper(int the_loai_id, Node<book>* node, BST_Book &b);
    Node<book>* chuyen_nganh_of_book_helper(int chuyen_nganh_id, Node<book>* node, BST_Book &b);
public:
    int count_sach_theo_the_loai(int the_loai_id);
    int count_sach_theo_chuyen_nganh(int chuyen_nganh_id);
    void author_of_book(int author_id, BST_Book &b);
    void the_loai_of_book(int the_loai_id, BST_Book &b);
    void chuyen_nganh_of_book(int chuyen_nganh_id, BST_Book &b);
    void search(int type_the_loai, int type_tuy_chon, int& type_bieu_ghi, string& key_word, BST_Book &book_data_, BST_Book &kq_return);
    void tong_hop_sach_TL_CN(int The_loai_ID, int Chuyen_nganh_ID, BST_Book &b, BST_Book &book_data_);
    long long tong_hop_sach_find_max_id(BST_Book &b);
    BST_Book() : BST<book, long long>(KeyGetters::getBookID) {}
    void write_book(QTextStream &out) const;
};

class BST_Book_by_Name : public BST<book, std::pair<string,long long>>{
private:
public:
    BST_Book_by_Name() : BST(KeyGetters::getKey_Name_ID) {}
};

class BST_Book_by_Author : public BST<book, std::pair<string,long long>>{
private:
public:
    BST_Book_by_Author() : BST(KeyGetters::getKey_Author_ID) {}
};

class BST_Book_by_Chuyen_Nganh : public BST<book, std::pair<string,long long>>{
private:
public:
    BST_Book_by_Chuyen_Nganh() : BST(KeyGetters::getKey_CN_ID) {}
};
class BST_Book_by_The_loai : public BST<book, std::pair<string,long long>>{
private:
public:
    BST_Book_by_The_loai() : BST(KeyGetters::getKey_TL_ID) {}
};
class BST_Book_by_Do_chinh_xac : public BST<book, std::pair<int,long long>>{
private:
public:
    BST_Book_by_Do_chinh_xac() : BST(KeyGetters::getKey_DoCX_ID) {}
};
class BST_Book_by_DateCreated : public BST<book, std::pair<my_time,long long>>{
private:
public:
    BST_Book_by_DateCreated() : BST(KeyGetters::getKey_DateCreated_ID) {}
};

class BST_Book_by_DateCreated_10 : public BST<book, std::pair<my_time,long long>>{
private:
    static constexpr int MAX_SIZE = 10;
    std::pair<my_time,long long> min_key_in_tree(Node<book>* node) const {
        Node<book>* current = node;
        while (current && current->getLeft() != nullptr) {
            current = current->getLeft();
        }
        return current ? KeyGetters::getKey_DateCreated_ID(current->getData()) : std::pair<my_time,long long>{my_time(), 0};
    }
    void trim_to_size(){
        while (this->count_data() > MAX_SIZE){
            auto min_key = min_key_in_tree(this->root);
            this->remove_by_Key(min_key);
        }
    }
public:
    BST_Book_by_DateCreated_10() : BST(KeyGetters::getKey_DateCreated_ID) {}
    bool insert(const book& value) {
        bool inserted = BST<book, std::pair<my_time,long long>>::insert(value);
        if (inserted) {
            trim_to_size();
        }
        return inserted;
    }
};

class BST_Book_by_luot_xem : public BST<book, std::pair<int,long long>>{
private:
public:
    BST_Book_by_luot_xem() : BST(KeyGetters::getKey_LuotXem_ID) {}
    void find_5_most_viewed(BST_Book_by_luot_xem &b);
};

class BST_Book_by_luot_muon : public BST<book, std::pair<int,long long>>{
private:
public:
    BST_Book_by_luot_muon() : BST(KeyGetters::getKey_LuotMuon_ID) {}
    void find_5_most_borrowed(BST_Book_by_luot_muon &b);
};

class BST_book_copy : public BST<Book_copies, long long> {
private:
    Node<Book_copies>* remove_by_book_id_helper(long long book_id, Node<Book_copies>* node);
    Node<Book_copies>* copies_of_book_helper(long long book_id, Node<Book_copies>* node, BST_book_copy &b);
    Node<Book_copies>* find_available_copy_helper(long long book_id, Node<Book_copies>* node);
public:
    void copies_of_book(long long book_id, BST_book_copy &b);
    long long find_id_available_copy(long long book_id);
    BST_book_copy() : BST<Book_copies, long long>(KeyGetters::getBookCopiesID) {}
    void write_book_copy(QTextStream &out) const;
    bool remove_by_book_id(long long book_id);
};

class BST_Author : public BST<Author, int> {
private:
    Node<Author>* return_id_helper(Node<Author>* node, string name, int &ok, int &id);
public:
    BST_Author() : BST<Author, int>(KeyGetters::getAuthorID) {}
    //void write_author(QTextStream &out) const;
    bool return_name(int id, string &name);
    bool return_id(string name, int &id);
};


class BST_Chuyen_nganh : public BST<Chuyen_nganh, int> {
private:
    Node<Chuyen_nganh>* return_id_helper(Node<Chuyen_nganh>* node, string name, int &ok, int &id);
public:
    BST_Chuyen_nganh() : BST<Chuyen_nganh, int>(KeyGetters::getChuyenNganhID) {}
    bool return_name(int id, string &name);
    bool return_id(string name, int &id);
    void write_chuyen_nganh(QTextStream &out) const;
};

class BST_The_loai : public BST<The_loai, int> {
private:
    Node<The_loai>* return_id_helper(Node<The_loai>* node, string name, int &ok, int &id);
public:
    BST_The_loai() : BST<The_loai, int>(KeyGetters::getTheLoaiID) {}
    bool return_name(int id, string &name);
    bool return_id(string name, int &id);
    void write_the_loai(QTextStream &out) const;
};

class BST_string : public BST<string, string> {
private:
public:
    BST_string() : BST<string, string>(KeyGetters::getStringID) {}
    bool co_chua_string(string& key_word);
    bool co_chua_string_helper(Node<string>* node, const string& key_word);
    void search_co_chua(BST_string &key, BST_string &full, int &count_);
    void search_co_chua_helper(Node<string>* node, BST_string &full, int &count_);
};

class BST_Borrow : public BST<borrow, long long> {
private:
    Node<borrow>* sach_dang_muon_helper(int user_id, Node<borrow>* node, int &count);
    Node<borrow>* check_book_copy_borrowed_helper(int user_id, long long book_id, Node<borrow>* node);
    void info_user_helper(int user_id, Node<borrow>* node, BST_Borrow &b);
    Node<borrow>* sach_qua_han_helper(int user_id, my_time current_date, Node<borrow>* node, BST_Borrow &b);
    Node<borrow>* kiem_tra_sach_qua_han_helper(Node<borrow>* node, BST_Borrow &b, my_time current_date);
    Node<borrow>* tong_sach_dat_muon_qua_han_helper(Node<borrow>* node, int &tong_sach_dat, int &tong_sach_muon, int &tong_sach_qua_han, my_time current_date);
    public:
    BST_Borrow() : BST<borrow, long long>(KeyGetters::getBorrowID) {}
    ~BST_Borrow() = default;

    long long find_new_id_borrow() const {
        return find_max_id() + 1;
    }
    void tong_sach_dat_muon_qua_han(int &tong_sach_dat, int &tong_sach_muon, int &tong_sach_qua_han);
    void kiem_tra_sach_qua_han(BST_Borrow &b);
    bool find_Borrow(long long id, borrow &a) { return find(id, a); }
    bool update_Borrow(borrow &old_, borrow &new_) { return update(old_, new_); }
    borrow operator[](int index) { return BST::operator[](index); }
    int count_borrow() const { return count_data(); }
    void write_csv(Node<borrow>* node, QTextStream &out) const; // Cần thay đổi tham số
    void write_borrow(QTextStream &out) const;
    int sach_dang_muon(int user_id);
    bool check_borrowed(int user_id, long long book_id);
    void info_user(int user_id, BST_Borrow &b);

    void tim_sach_dat_thu_thu(BST_Borrow &b);
    void tim_sach_muon_thu_thu(BST_Borrow &b);
    void tim_sach_tra_thu_thu(BST_Borrow &b);

    void sach_qua_han(int user_id, my_time current_date, BST_Borrow &b);
    void thong_ke_sach_dat(int &xu_ly, int &san_sang, int &qua_han, BST_Borrow &b);
    void thong_ke_sach_muon(int &dang_muon, int &qua_han, BST_Borrow &b);
    void thong_ke_sach_tra(int &tong_luot_tra, int &tra_qua_han, int &hu_hong_mat, long long &tong_tien_phat, BST_Borrow &b);
};

class BST_History : public BST<history_record, my_time> {
private:
public:
    BST_History() : BST<history_record, my_time>(KeyGetters::getMyTimeID) {}
    ~BST_History() = default;
    void log_action(const string& user_name, ActionType action_type, long long book_id, const string& ghi_chu);
    void save_to_file(const history_record& data);
    void loc_lich_su_theo_ngay(my_time start, my_time end, BST_History &b);
    void luot_xem_muon_tai_thang(int month, int year, int &so_luot_xem, int &so_luot_muon, int &so_luot_tai);
    void loc_user(string user_name, BST_History &b);
    BST_History& tim_lich_su_user_ngay(string user_name, int ngay, int thang, int nam, BST_History &b);
    void load_from_file();
    void load_from_file(string user_name, BST_History &b);
};

class BST_Yeu_thich : public BST<yeu_thich, std::pair<long long, long long>> {
private:
public:
    BST_Yeu_thich() : BST<yeu_thich, std::pair<long long, long long>>(KeyGetters::getKey_YeuThich_ID) {}
    ~BST_Yeu_thich() = default;
    void load_from_file();
    void write_to_file();
    bool is_like_book(long long book_id, long long user_id);
    void add_like(long long book_id, long long user_id);
    void remove_like(long long book_id, long long user_id);
};

#endif // TREE_H
