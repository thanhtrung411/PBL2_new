#include "tree.h"
#include "global.h"
#include "my_string.h"
#include "history_record.h"
#include "settings_file.h"
#include <iostream>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <fstream>

namespace{
    BST_Chuyen_nganh* chuyen_nganh_tree = nullptr;
    BST_The_loai* the_loai_tree = nullptr;
}

namespace KeyGetters{
    int getAccoutID(const accout& a) {
        return a.get_ID();
    }
    long long getBookID(const book& b) {
        return b.get_ID();
    }
    long long getBookCopiesID(const Book_copies& bc) {
        return bc.get_id();
    }
    int getAuthorID(const Author& au) {
        return au.get_ID();
    }
    int getTheLoaiID(const The_loai& tl) {
        return tl.get_id();
    }
    int getChuyenNganhID(const Chuyen_nganh& cn) {
        return cn.get_id();
    }
    long long getBorrowID(const borrow& br) {
        return br.get_id();
    }
    string getStringID(const string& s) {
        return s;
    }
    string getNameBook(const book& b) {
        return b.get_Name();
    }
    string getAuthorName(const book& b){
        return b.get_Author();
    }
    my_time getMyTimeID(const history_record& t){
        return t.date_action;
    }
    inline string lower(string s){
        for(char &c: s) c = std::tolower((unsigned char)c);
        return s;
    }
    std::pair<string,long long> getKey_Name_ID   (const book& b) { return { lower(b.get_Name()),              b.get_ID() }; }
    std::pair<string,long long> getKey_Author_ID (const book& b) { return { lower(b.get_Author()),            b.get_ID() }; }
    std::pair<string,long long> getKey_TL_ID     (const book& b) { return { lower(b.get_The_loai_name()),     b.get_ID() }; }
    std::pair<string,long long> getKey_CN_ID     (const book& b) { return { lower(b.get_Chuyen_nganh_name()), b.get_ID() }; }
    std::pair<int,long long>    getKey_DoCX_ID   (const book& b) { return { b.get_do_chinh_xac(),             b.get_ID() }; }
    std::pair<my_time,long long>getKey_DateCreated_ID   (const book& b) { return { b.get_Date_created(),      b.get_ID() }; }
}

template<typename T, typename Key>
int BST<T, Key>::height(Node<T>* node) const {
    if (node == nullptr) {
        return 0;
    }
    return node->getHeight();
}
template<typename T, typename Key>
int BST<T, Key>::getBalanceFactor(Node<T>* node) const {
    if (node == nullptr) {
        return 0;
    }
    return height(node->getLeft()) - height(node->getRight());
}
template<typename T, typename Key>
void BST<T, Key>::updateHeight(Node<T>* node) {
    if (node != nullptr) {
        int leftHeight = height(node->getLeft());
        int rightHeight = height(node->getRight());
        node->setHeight(1 + std::max(leftHeight, rightHeight));
    }
}
template<typename T, typename Key>
Node<T>* BST<T, Key>::rightRotate(Node<T>* y) {
    Node<T>* x = y->getLeft();
    Node<T>* T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2);

    updateHeight(y);
    updateHeight(x);

    return x;
}
template<typename T, typename Key>
Node<T>* BST<T, Key>::leftRotate(Node<T>* x) {
    Node<T>* y = x->getRight();
    Node<T>* T2 = y->getLeft();

    y->setLeft(x);
    x->setRight(T2);

    updateHeight(x);
    updateHeight(y);

    return y;
}
template<typename T, typename Key>
Node<T>* BST<T, Key>::balance(Node<T>* node) {
    if (node == nullptr) {
        return node;
    }
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (getBalanceFactor(node->getLeft()) < 0) {
            node->setLeft(leftRotate(node->getLeft()));
        }
        return rightRotate(node);
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->getRight()) > 0) {
            node->setRight(rightRotate(node->getRight()));
        }
        return leftRotate(node);
    }
    return node;
}

template <typename T, typename Key>
void BST<T, Key>::destroy_Node(Node<T>* node) {
    if (node != nullptr) {
        destroy_Node(node->getLeft());
        destroy_Node(node->getRight());
        delete node;
    }
}

template <typename T, typename Key>
BST<T, Key>::~BST() {
    destroy_Node(root);
}

template<typename T, typename Key>
Node<T>* BST<T, Key>::add_Node(Node<T>* node, const T& value, int &ok) {
    if (node == nullptr) {
        ok = 1;
        return new Node<T>(value);
    }
    Key key = getKey(value);
    if (key < getKey(node->getData())) {
        node->setLeft(add_Node(node->getLeft(), value, ok));
    } else if (key > getKey(node->getData())) {
        node->setRight(add_Node(node->getRight(), value, ok));
    } else {
        ok = 0;
        return node;
    }
    return balance(node);
}
template<typename T, typename Key>
bool BST<T, Key>::insert(const T& value) {
    int ok = 0;
    root = add_Node(root, value, ok);
    return ok == 1;
}
template<typename T, typename Key>
Node<T>* BST<T, Key>::delete_Node(Node<T>* node, T data, int &ok) {
    if (node == nullptr) {
        ok = 0;
        return node;
    }
    Key key = getKey(data);
    if (key < getKey(node->getData())) {
        node->setLeft(delete_Node(node->getLeft(), data, ok));
    } else if (key > getKey(node->getData())) {
        node->setRight(delete_Node(node->getRight(), data, ok));
    } else {
        ok = 1;
        if (node->getLeft() == nullptr || node->getRight() == nullptr) {
            Node<T>* temp = node->getLeft() ? node->getLeft() : node->getRight();
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node<T>* temp = node->getRight();
            while (temp->getLeft() != nullptr) {
                temp = temp->getLeft();
            }
            node->setData(temp->getData());
            node->setRight(delete_Node(node->getRight(), temp->getData(), ok));
        }
    }
    if (node == nullptr) {
        return node;
    }
    return balance(node);
}
template<typename T, typename Key>
Node<T>* BST<T, Key>::copy_tree(Node<T>* node) {
    if (node == nullptr) {
        return nullptr;
    }
    Node<T>* new_node = new Node<T>(node->getData());
    new_node->setLeft(copy_tree(node->getLeft()));
    new_node->setRight(copy_tree(node->getRight()));
    updateHeight(new_node);
    return new_node;
}

template<typename T, typename Key>
bool BST<T, Key>::remove_by_Key(const Key& id) {
    T temp;
    if (!find(id, temp)) {
        return false;
    }
    int ok = 0;
    root = delete_Node(root, temp, ok);
    return ok == 1;
}

template<typename T, typename Key>
Node<T>* BST<T, Key>::search_Node(Node<T>* node, const Key& key) {
    if (node == nullptr || getKey(node->getData()) == key) {
        return node;
    }
    if (key < getKey(node->getData())) {
        return search_Node(node->getLeft(), key);
    }
    return search_Node(node->getRight(), key);
}

template<typename T, typename Key>
Key BST<T, Key>::find_max_key(Node<T>* node) const {
    if (node == nullptr) {
        return Key{};
    }
    Node<T>* current = node;
    while (current->getRight() != nullptr) {
        current = current->getRight();
    }
    return getKey(current->getData());
}

template<typename T, typename Key>
bool BST<T, Key>::find(Key id, T& result) {
    Node<T>* node = search_Node(root, id);
    if (node != nullptr) {
        result = node->getData();
        return true;
    }
    return false;
}

template<typename T, typename Key>
bool BST<T, Key>::update(T &old_, T &new_) {
    int ok = 0;
    root = delete_Node(root, old_, ok);
    if (ok == 0) {
        return false;
    }
    ok = 0;
    root = add_Node(root, new_, ok);
    return ok == 1;
}
template<typename T, typename Key>
int BST<T, Key>::count(Node<T>* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + count(node->getLeft()) + count(node->getRight());
}

template<typename T, typename Key>
int BST<T, Key>::count_data() const {
    return count(root);
}
template<typename T, typename Key>
T BST<T, Key>::operator[](int index) {
    if (index < 0 || index >= count_data()){
        qDebug() << "Loi index";
        T u = T();
        return u;
    }
    Node<T>* result = root;
    int tmp = 0;
    while (result) {
        int leftCount = count(result->getLeft());
        if (index < tmp + leftCount){
            result = result->getLeft();
        } 
        else if (index > tmp + leftCount){
            tmp += leftCount + 1;
            result = result->getRight();
        } 
        else{
            return result->getData();
        }
    }
    T u = T();
    qDebug() << "Loi khong xac dinh";
    return u;
}

template<typename T, typename Key>
Key BST<T, Key>::find_max_id() const{
    if (root == nullptr) {
        return Key{};
    }
    Key max_key = find_max_key(root);
    return max_key;
}
template <typename T, typename Key>
void BST<T, Key>::in_order_recursive(Node<T>* node, std::function<void(T&)> visit_func) {
    if (!node) return;
    in_order_recursive(node->getLeft(), visit_func);
    visit_func(node->getData());
    in_order_recursive(node->getRight(), visit_func);
}
template <typename T, typename Key>
void BST<T, Key>::pre_order_recursive(Node<T>* node, std::function<void(T&)> visit_func) {
    if (!node) return;
    visit_func(node->getData());
    pre_order_recursive(node->getLeft(), visit_func);
    pre_order_recursive(node->getRight(), visit_func);
}

/*
template <typename T, typename Key>

void BST<T, Key>::write_data_recursive(Node<T>* node, QTextStream &out, void (*writer)(const T&, QTextStream&)) const {
    if (!node) return; write_data_recursive(node->getLeft(), out, writer); writer(node->getData(), out); write_data_recursive(node->getRight(), out, writer);
}
    */
/*
template <typename T, typename Key>

Key BST<T, Key>::find_max_key_help(Node<T>* node) const {
    if (node == nullptr) {
        // Giả định Key có thể được khởi tạo với giá trị nhỏ nhất (e.g., 0)
        return (Key)0;
    }
    // Trong BST, khóa lớn nhất luôn ở node xa nhất bên phải
    Node<T>* current = node;
    while (current->getRight() != nullptr) {
        current = current->getRight();
    }
    return key_getter(current->getData());
}

template <typename T, typename Key>
Key BST<T, Key>::find_max_id() const{
    if (root == nullptr) {
        return Key(0);
    }
    Key max_key = find_max_key_help(root);
    return max_key;
}
template <typename T, typename Key>
Key BST<T, Key>::find_new_id() const {
    if (root == nullptr) {
        return (Key)1; // ID đầu tiên luôn là 1
    }
    Key max_key = find_max_key_help(root);
    return max_key + (Key)1;
}
    */
template class BST<accout, int>;
template class BST<book, long long>;
template class BST<Book_copies, long long>;
template class BST<Author, int>;
template class BST<Chuyen_nganh, int>;
template class BST<The_loai, int>;
template class BST<borrow, long long>;
template class BST<string, string>;
template class BST<history_record, my_time>;
template class BST<book, std::pair<string,long long>>;
template class BST<book, std::pair<my_time,long long>>;

////////////--for BST_string--//////////////
bool BST_string::co_chua_string(string& key_word) {
    return co_chua_string_helper(root, key_word);
}
bool BST_string::co_chua_string_helper(Node<string>* node, const string& key_word) {
    if (!node) return false;
    if (co_chua_string_helper(node->getLeft(), key_word)) return true;

    const string& word = node->getData();
    if (word.find(key_word) != string::npos) {
        return true;
    }

    return co_chua_string_helper(node->getRight(), key_word);
}

void BST_string::search_co_chua_helper(Node<string>* node, BST_string &full, int &count_) {
    if (!node) return;
    search_co_chua_helper(node->getLeft(), full, count_);
    string& a = node->getData();
    if (full.co_chua_string(a)) {
        count_++;
    }
    search_co_chua_helper(node->getRight(), full, count_);
}

 void BST_string::search_co_chua(BST_string &key, BST_string &full, int &count_){
    count_ = 0;
    Node<string>* node = key.root;
    if (!node) return;
    search_co_chua_helper(node, full, count_);
}

/////////////--for BST_Accout--//////////////

bool BST_Accout::check_accout(string ten_dang_nhap, string pass, accout& a){
    int ok = 0;
    accout_data.traverse_ascending([&](accout &ac){
        if (ac.get_ten_dang_nhap() == ten_dang_nhap && ac.get_pass() == pass){
            ok = 1;
            a = ac;
        }
    });
    return ok == 1;
}

void BST_Accout::write_csv(Node<accout>* node, QTextStream &out) const {
    if (!node) return;
    write_csv(node->getLeft(), out);
    accout& a = node->getData();
    out << a.get_ID() << "," 
        << QString::fromStdString(a.get_ten_dang_nhap()) << "," 
        << QString::fromStdString(a.get_ten_tai_khoan()) << "," 
        << a.get_gioi_tinh() << ","
        << QString::fromStdString(a.get_ngay_sinh().get_date()) << ","
        << QString::fromStdString(a.get_email()) << "," 
        << a.get_doi_tuong() << ","
        << QString::fromStdString(a.get_phone_number()) << "," 
        << QString::fromStdString(a.get_pass()) << "," 
        << QString::fromStdString(a.get_level()) << ","
        << QString::fromStdString(a.get_date_created().get_datetime()) << "\n";
    write_csv(node->getRight(), out);
}

void BST_Accout::write_accout(QTextStream &out) const {
    out << "ID, Ten_dang_nhap, Ten_tai_khoan, Email, Phone_number, Gioi_tinh, Date_created, Pass\n";
    Node<accout>* node = root;
    write_csv(node, out);
}

int BST_Accout::count_doc_gia_helper(Node<accout>* node) {
    if (!node) return 0;
    int count = 0;
    if (node->getData().get_doi_tuong() == 1) {
        count = 1;
    }
    return count + count_doc_gia_helper(node->getLeft()) + count_doc_gia_helper(node->getRight());
}
int BST_Accout::count_thu_thu_helper(Node<accout>* node) {
    if (!node) return 0;
    int count = 0;
    if (node->getData().get_doi_tuong() == 2) {
        count = 1;
    }
    return count + count_thu_thu_helper(node->getLeft()) + count_thu_thu_helper(node->getRight());
}
int BST_Accout::count_doc_gia(){
    return count_doc_gia_helper(root);
}
int BST_Accout::count_thu_thu(){
    return count_thu_thu_helper(root);
}
bool BST_Accout::check_ten_dang_nhap(string ten_dang_nhap){
    int ok = 0;
    accout_data.traverse_ascending([&](accout &a){
        if (a.get_ten_dang_nhap() == ten_dang_nhap){
            ok = 1;
        }
    });
    return ok;
}
bool BST_Accout::check_quen_mat_khau(string so_dien_thoai, string email, accout &a){
    int ok = 0;
    accout_data.traverse_ascending([&](accout &ac){
        if (ac.get_phone_number() == so_dien_thoai && ac.get_email() == email){
            ok = 1;
            ac.set_pass(ma_hoa_str_(settings_file::getInstance()->get_mat_khau_quen()));
            a = ac;
        }
    });
    return ok;
}

/////////////--for BST_Borrow--//////////////

void BST_Borrow::write_csv(Node<borrow>* node, QTextStream &out) const {
    if (!node) return;
    write_csv(node->getLeft(), out);
    borrow& a = node->getData();
    out << a.get_id() << ","
        << a.get_book_id() << ","
        << a.get_book_copy_id() << ","
        << a.get_user_id() << ","
        << QString::fromStdString(a.get_ngay_dat().get_datetime()) << ","
        << QString::fromStdString(a.get_ngay_muon().get_datetime()) << ","
        << QString::fromStdString(a.get_ngay_phai_tra().get_datetime()) << ","
        << QString::fromStdString(a.get_ngay_tra().get_datetime()) << ","
        << QString::fromStdString(a.get_status_string()) << ","
        << a.get_lan_gia_han() << ","
        << QString::fromStdString(a.get_ghi_chu()) << ","
        << a.get_tien_phat() << "\n";
    write_csv(node->getRight(), out);
}
void BST_Borrow::write_borrow(QTextStream &out) const {
    out << "ID, Book_ID, Book_Copy_ID, User_ID, Ngay_dat, Ngay_muon, Ngay_phai_tra, Ngay_tra, Status,Lan_gia_han, Ghi_chu, Tien_phat\n";
    write_csv(root, out);
}

/////////////--for BST_Book--//////////////

Node<book>* BST_Book::tong_hop_sach_TL_CN_Node(int The_loai_ID, int Chuyen_nganh_ID, Node<book>* node, BST_Book &b){
    if (!node) return nullptr;
    tong_hop_sach_TL_CN_Node(The_loai_ID, Chuyen_nganh_ID, node->getLeft(), b);
    book& a = node->getData();
    if (a.get_The_loai_ID() == The_loai_ID && a.get_Chuyen_nganh_ID() == Chuyen_nganh_ID){
        b.insert(a);
    }
    tong_hop_sach_TL_CN_Node(The_loai_ID, Chuyen_nganh_ID, node->getRight(), b);
    return nullptr;
}

void BST_Book::tong_hop_sach_TL_CN(int The_loai_ID, int Chuyen_nganh_ID, BST_Book &b, BST_Book &book_data_){
    tong_hop_sach_TL_CN_Node(The_loai_ID, Chuyen_nganh_ID, book_data_.root, b);
}

long long BST_Book::tong_hop_sach_find_max_id(BST_Book &b){
    return b.find_max_id();
}

/*
void BST_Book::tong_hop_sach_chung_Node(string &the_loai, string &chuyen_nganh, Node<book>* node, BST_Book &b){
    if (!node) return;
    tong_hop_sach_chung_Node(the_loai, chuyen_nganh, node->getLeft(), b);
    book& a = node->getData();
    //int check1 = tim_kiem_xau(the_loai, the_loai_data.return_name(a.get_The_loai_ID()));
    //int check2 = tim_kiem_xau(chuyen_nganh, chuyen_nganh_data.return_name(a.get_Chuyen_nganh_ID()));
    //if (check1 == count_string(the_loai) && check2 == count_string(chuyen_nganh)){
    //    b.insert(a);
    //}
    //tong_hop_sach_chung_Node(the_loai, chuyen_nganh, node->getRight(), b);
}

void BST_Book::tong_hop_sach_chung(string &the_loai, string &chuyen_nganh,const BST_Book &book_data_, BST_Book &b){
    tong_hop_sach_chung_Node(the_loai, chuyen_nganh, book_data_.root, b);
}

void BST_Book::find_some_id_book_Node(string& id_, Node<book>* Node){
    if (!Node) return;
    find_some_id_book_Node(id_, Node->getLeft());
    string a = to_string(Node->getData().get_ID());
    if (is_chua_chuoi(id_, a)){
        this->insert(Node->getData());
    }
    find_some_id_book_Node(id_, Node->getRight());
}

void BST_Book::find_some_id_book(string& id_chuoi, const BST_Book &book_data_){
    find_some_id_book_Node(id_chuoi, book_data_.root);
}
    */

bool BST_Book::search_custom_trung_gian(int type_tuy_chon, int& type_bieu_ghi, string& key_word, book& a){
    //type_tuy_chon: tùy chọn vùng tìm kiếm
    //    - type_tuy_chon == 0: tìm kiếm sách có trường chứa key
    //    - type_tuy_chon == 1: tìm kiếm sách có trường chính xác trong key
    //    - type_tuy_chon == 2: tìm kiếm sách có trường bắt đầu bằng key
    //type_bieu_ghi: tùy chọn trường cần tìm kiếm
    //    - type_bieu_ghi == 0: tìm kiếm theo tất cả các trường
    //    - type_bieu_ghi == 1: tìm kiếm theo trường TÊN SÁCH
    //    - type_bieu_ghi == 2: tìm kiếm theo trường TÁC GIẢ
    //    - type_bieu_ghi == 3: tìm kiếm theo trường NHÀ XUẤT BẢN
    //    - type_bieu_ghi == 4: tìm kiếm theo trường NĂM XUẤT BẢN
    //    - type_bieu_ghi == 5: tìm kiếm theo trường ISBN
    //    - type_bieu_ghi == 6: tìm kiếm theo trường NGÔN NGỮ
    //    - type_bieu_ghi == 7: tìm kiếm theo trường TÓM TẮT
    //    - type_bieu_ghi == 8: tìm kiếm theo trường CHUYÊN NGÀNH
    int count = 0;
    string check_str = "";
    switch (type_bieu_ghi)
    {
    case 0:{//tất cả các trường
        if (type_tuy_chon == 0) {
            count += tim_kiem_co_chua(key_word, a.get_Name());
            count += tim_kiem_co_chua(key_word, a.get_Author());
            count += tim_kiem_co_chua(key_word, a.get_NXB());
            count += tim_kiem_co_chua(key_word, to_string_(a.get_NamXB()));
            count += tim_kiem_co_chua(key_word, a.get_ISBN());
            count += tim_kiem_co_chua(key_word, a.get_Language());
            count += tim_kiem_co_chua(key_word, a.get_Tom_tat());
            count += tim_kiem_co_chua(key_word, a.get_Chuyen_nganh_name());
            if (!count) {
                return false;
            }
        }
        else if (type_tuy_chon == 1) {
            count += tim_kiem_chinh_xac(key_word, a.get_Name());
            count += tim_kiem_chinh_xac(key_word, a.get_Author());
            count += tim_kiem_chinh_xac(key_word, a.get_NXB());
            count += tim_kiem_chinh_xac(key_word, to_string_(a.get_NamXB()));
            count += tim_kiem_chinh_xac(key_word, a.get_ISBN());
            count += tim_kiem_chinh_xac(key_word, a.get_Language());
            count += tim_kiem_chinh_xac(key_word, a.get_Tom_tat());
            count += tim_kiem_chinh_xac(key_word, a.get_Chuyen_nganh_name());
            if (!count) {
                return false;
            }
        }
        else if (type_tuy_chon == 2) {
            count += tim_kiem_bat_dau_bang(key_word, a.get_Name());
            count += tim_kiem_bat_dau_bang(key_word, a.get_Author());
            count += tim_kiem_bat_dau_bang(key_word, a.get_NXB());
            count += tim_kiem_bat_dau_bang(key_word, to_string_(a.get_NamXB()));
            count += tim_kiem_bat_dau_bang(key_word, a.get_ISBN());
            count += tim_kiem_bat_dau_bang(key_word, a.get_Language());
            count += tim_kiem_bat_dau_bang(key_word, a.get_Tom_tat());
            count += tim_kiem_bat_dau_bang(key_word, a.get_Chuyen_nganh_name());
            if (!count) {
                return false;
            }
        }
        a.set_do_chinh_xac(count);
        return true;
        break;
    }
    case 1:{//tên sách
        check_str = a.get_Name();
        break;
    }
    case 2:{//tác giả
        check_str = a.get_Author();
        break;
    }
    case 3:{//nhà xuất bản
        check_str = a.get_NXB();
        break;
    }
    case 4:{//năm xuất bản
        check_str = to_string_(a.get_NamXB());
        break;
    }
    case 5:{//ISBN
        check_str = a.get_ISBN();
        break;
    }
    case 6:{//ngôn ngữ
        check_str = a.get_Language();
        break;
    }
    case 7:{//tóm tắt
        check_str = a.get_Tom_tat();
        break;
    }
    case 8:{//chuyên ngành
        check_str = a.get_Chuyen_nganh_name();
        break;
    }
    default:
        return false;
    }
    if (type_tuy_chon == 0) {
        count = tim_kiem_co_chua(key_word, check_str);
    }
    else if (type_tuy_chon == 1) {
        count = tim_kiem_chinh_xac(key_word, check_str);
    }
    else if (type_tuy_chon == 2) {
        count = tim_kiem_bat_dau_bang(key_word, check_str);
    }
    if (count) {
        a.set_do_chinh_xac(count);
        return true;
    }
    return false;
}

Node<book>* BST_Book::search_help(int type_the_loai, int type_tuy_chon, int& type_bieu_ghi, string& key_word, Node<book>* node, BST_Book &kq_return){
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

    if (!node) return nullptr;
    search_help(type_the_loai, type_tuy_chon, type_bieu_ghi, key_word, node->getLeft(), kq_return);
    book& a = node->getData();
    if (type_the_loai != 0){
        if (a.get_The_loai_ID() == type_the_loai){
            if (search_custom_trung_gian(type_tuy_chon, type_bieu_ghi, key_word, a)){
                kq_return.insert(a);
            }  
        }
    }
    else{
        if (search_custom_trung_gian(type_tuy_chon, type_bieu_ghi, key_word, a)){
            kq_return.insert(a);
        }
    }
    search_help(type_the_loai, type_tuy_chon, type_bieu_ghi, key_word, node->getRight(), kq_return);
    return nullptr;
}

void BST_Book::search(int type_the_loai, int type_tuy_chon, int& type_bieu_ghi, string& key_word, BST_Book &book_data_, BST_Book &kq_return){
    Node<book>* node = book_data_.root;
    if (key_word.empty()) return;
    if (!node) return;
    search_help(type_the_loai, type_tuy_chon, type_bieu_ghi, key_word, node, kq_return);
}

Node<book>* BST_Book::write_book_helper(Node<book>* node, QTextStream &out) const {
    if (!node) return nullptr;
    write_book_helper(node->getLeft(), out);
    book& a = node->getData();
    out << a.get_ID() << "," 
        << QString::fromStdString(a.get_Name()) << "," << "\""
        << QString::fromStdString(a.get_Author()) << "\"" << "," 
        << QString::fromStdString(a.get_NXB()) << ","
        << QString::number(a.get_NamXB()) << ","
        << QString::number(a.get_So_trang()) << ","
        << QString::fromStdString(a.get_ISBN()) << ","
        << QString::fromStdString(a.get_Language()) << "," << "\""
        << QString::fromStdString(a.get_Tom_tat()) << "\","
        << QString::fromStdString(a.get_Link_png()) << ","
        << QString::fromStdString(a.get_Link_pdf()) << ","
        << QString::number(a.get_The_loai_ID()) << ","
        << QString::number(a.get_Chuyen_nganh_ID()) << ","
        << QString::number(to_int(a.get_is_Read_online())) << ","
        << QString::number(to_int(a.get_is_Download())) << ","
        << QString::number(to_int(a.get_is_Borrow())) << ","
        << QString::number(a.get_limit_borrow()) << ","
        << QString::number(a.get_luot_xem()) << ","
        << QString::number(a.get_luot_muon()) << ","
        << QString::number(a.get_luot_tai()) << ","
        << QString::number(a.get_tong_sach()) << ","
        << QString::number(a.get_tong_sach_dang_muon()) << ","
        << QString::number(a.get_tong_sach_dang_dat()) << ","
        << QString::number(a.get_tong_sach_ranh()) << ","
        << QString::fromStdString(a.get_Date_created().get_datetime()) << ","
        << QString::fromStdString(a.get_Created_by()) << "\n";
    write_book_helper(node->getRight(), out);
    return nullptr;
}

void BST_Book::write_book(QTextStream &out) const {
    out << "ID, Name, Author, NXB, NamXB, So_Trang, ISBN, Language, Tom_tat, Link_png, Link_pdf, The_loai_ID, Chuyen_nganh_ID, is_Read_online, is_Download, is_Borrow, limit_borrow, luot_xem, luot_muon, luot_tai, tong_sach, tong_sach_dang_muon, tong_sach_dang_dat, tong_sach_ranh, Date_created, Created_by\n";
    write_book_helper(root, out);
}

Node<book>* BST_Book::author_of_book_helper(int author_id, Node<book>* node, BST_Book &b) {
    if (!node) return nullptr;
    author_of_book_helper(author_id, node->getLeft(), b);
    book& a = node->getData();
    //if (a.get_Author_ID() == author_id){
    //    b.insert(a);
    //}
    author_of_book_helper(author_id, node->getRight(), b);
    return nullptr;
}
void BST_Book::author_of_book(int author_id, BST_Book &b){
    author_of_book_helper(author_id, root, b);
}
Node<book>* BST_Book::the_loai_of_book_helper(int the_loai_id, Node<book>* node, BST_Book &b) {
    if (!node) return nullptr;
    the_loai_of_book_helper(the_loai_id, node->getLeft(), b);
    book& a = node->getData();
    if (a.get_The_loai_ID() == the_loai_id){
        b.insert(a);
    }
    the_loai_of_book_helper(the_loai_id, node->getRight(), b);
    return nullptr;
}
void BST_Book::the_loai_of_book(int the_loai_id, BST_Book &b){
     the_loai_of_book_helper(the_loai_id, root, b);
}
Node<book>* BST_Book::chuyen_nganh_of_book_helper(int chuyen_nganh_id, Node<book>* node, BST_Book &b) {
    if (!node) return nullptr;
    chuyen_nganh_of_book_helper(chuyen_nganh_id, node->getLeft(), b);
    book& a = node->getData();
    if (a.get_Chuyen_nganh_ID() == chuyen_nganh_id){
        b.insert(a);
    }
    chuyen_nganh_of_book_helper(chuyen_nganh_id, node->getRight(), b);
    return nullptr;
}
void BST_Book::chuyen_nganh_of_book(int chuyen_nganh_id, BST_Book &b){
     chuyen_nganh_of_book_helper(chuyen_nganh_id, root, b);
}

///////////////--for BST_Book_copies--///////////////
long long BST_book_copy::find_id_available_copy(long long book_id){
    long long id_found = -1;
    book_copy_data.traverse_ascending([&book_id, this,&id_found](Book_copies& a) {
        if (a.get_status() == "available" && a.get_id_book() == book_id){
            id_found = a.get_id();
        }
        if (id_found != -1) return;
    });
    return id_found;
}

void BST_book_copy::write_book_copy(QTextStream &out) const {
    out << "ID, Book_id,Status,ghi_chu" << "\n";
    book_copy_data.traverse_ascending([&out](Book_copies& a) {
        out << a.get_id() << ","
            << a.get_id_book() << ","
            << QString::fromStdString(a.get_status()) << "," << "\""
            << QString::fromStdString(a.get_ghi_chu()) << "\"\n";
    });
}

/////////////--for BST_Author--/////////////
Node<Author>* BST_Author::return_id_helper(Node<Author>* node, string name, int &ok, int &id) {
    if (node == nullptr) {
        ok = 0;
        return nullptr;
    }
     Node<Author>* found = nullptr;
    if (node->getData().get_name() == name) {
        ok = 1;
        id = node->getData().get_ID();
        return node;
    }
    found = return_id_helper(node->getLeft(), name, ok, id);
    if (ok == 1) return found;
    return return_id_helper(node->getRight(), name, ok, id);
}

bool BST_Author::return_id(string name, int &id){
    int ok = 0;
    id = -1;
    Node<Author>* node = return_id_helper(root, name, ok, id);
    return ok == 1;
}
bool BST_Author::return_name(int id, string &name){
    Author temp;
    if (this->find(id, temp)){
        name = temp.get_name();
        return true;
    }
    name = "";
    return false;
}

/////////////--for BST_Chuyen_nganh--//////////////

Node<Chuyen_nganh>* BST_Chuyen_nganh::return_id_helper(Node<Chuyen_nganh>* node, string name, int &ok, int &id) {
    if (node == nullptr) {
        ok = 0;
        return nullptr;
    }
     Node<Chuyen_nganh>* found = nullptr;
    if (node->getData().get_name() == name) {
        ok = 1;
        id = node->getData().get_id();
        return node;
    }
    found = return_id_helper(node->getLeft(), name, ok, id);
    if (ok == 1) return found;
    return return_id_helper(node->getRight(), name, ok, id);
}

bool BST_Chuyen_nganh::return_id(string name, int &id){
    int ok = 0;
    id = -1;
    Node<Chuyen_nganh>* node = return_id_helper(root, name, ok, id);
    return ok == 1;
}
bool BST_Chuyen_nganh::return_name(int id, string &name){
    Chuyen_nganh temp;
    if (this->find(id, temp)){
        name = temp.get_name();
        return true;
    }
    name = "";
    return false;
}

////////////--for BST_The_loai--//////////////

Node<The_loai>* BST_The_loai::return_id_helper(Node<The_loai>* node, string name, int &ok, int &id) {
    if (node == nullptr) {
        ok = 0;
        return nullptr;
    }
    Node<The_loai>* found = nullptr;
    if (node->getData().get_name() == name) {
        ok = 1;
        id = node->getData().get_id();
        return node;
    }
    found = return_id_helper(node->getLeft(), name, ok, id);
    if (ok == 1) return found;
    return return_id_helper(node->getRight(), name, ok, id);
}

bool BST_The_loai::return_id(string name, int &id){
    int ok = 0;
    id = -1;
    Node<The_loai>* node = return_id_helper(root, name, ok, id);
    return ok == 1;
}
bool BST_The_loai::return_name(int id, string &name){
    The_loai temp;
    if (this->find(id, temp)){
        name = temp.get_name();
        return true;
    }
    name = "";
    return false;
}
//////////////--for BST_Borrow--//////////////

Node<borrow>* BST_Borrow::sach_dang_muon_helper(int user_id, Node<borrow>* node, int &count){
    if (!node) return nullptr;
    sach_dang_muon_helper(user_id, node->getLeft(), count);
    borrow& a = node->getData();
    if (a.get_user_id() == user_id && a.get_status() == StatusType::DANG_MUON){
        count++;
    }
    sach_dang_muon_helper(user_id, node->getRight(), count);
    return nullptr;
}
int BST_Borrow::sach_dang_muon(int user_id){
    int count = 0;
    sach_dang_muon_helper(user_id, root, count);
    return count;
}

Node<borrow>* BST_Borrow::check_book_copy_borrowed_helper(int id_user, long long id_book, Node<borrow>* node){
    if (!node) return nullptr;
    Node<borrow>* found = check_book_copy_borrowed_helper(id_user, id_book, node->getLeft());
    if (found) return found;
    borrow& a = node->getData();
    if (a.get_user_id() == id_user && a.get_book_copy_id() == id_book && a.get_status() == StatusType::DANG_MUON){
        return node;
    }
    return check_book_copy_borrowed_helper(id_user, id_book, node->getRight());
}

bool BST_Borrow::check_borrowed(int id_user, long long id_book){
    Node<borrow>* node = root;
    return check_book_copy_borrowed_helper(id_user,id_book, node);
}
Node<borrow>* BST_Borrow::info_user_helper(int user_id, Node<borrow>* node, BST_Borrow &b){
    if (!node) return nullptr;
    borrow& a = node->getData();
    if (a.get_user_id() == user_id){
        b.insert(a);
    }
    info_user_helper(user_id, node->getLeft(), b);
    info_user_helper(user_id, node->getRight(), b);
    return nullptr;
}
void BST_Borrow::info_user(int user_id, BST_Borrow &b){
    info_user_helper(user_id, root, b);
}

Node<borrow>* BST_Borrow::sach_qua_han_helper(int user_id, my_time current_date, Node<borrow>* node, BST_Borrow &b){
    if (!node) return nullptr;
    sach_qua_han_helper(user_id, current_date, node->getLeft(), b);
    borrow& a = node->getData();
    if (a.get_user_id() == user_id && a.get_status() == StatusType::DANG_MUON && current_date > a.get_ngay_phai_tra()){
        b.insert(a);
    }
    sach_qua_han_helper(user_id, current_date, node->getRight(), b);
    return nullptr;
}

void BST_Borrow::sach_qua_han(int user_id, my_time current_date, BST_Borrow &b){
    sach_qua_han_helper(user_id, current_date, root, b);
}

Node<borrow>* BST_Borrow::kiem_tra_sach_qua_han_helper(Node<borrow>* node, BST_Borrow &b, my_time current_date){
    if (!node) return nullptr;
    kiem_tra_sach_qua_han_helper(node->getLeft(), b, current_date);
    borrow& a = node->getData();
    if (a.get_status() == StatusType::DANG_MUON && current_date > a.get_ngay_phai_tra()){
        a.set_status(StatusType::QUA_HAN_MUON);
    }
    if ((a.get_status() == StatusType::XU_LY || a.get_status() == StatusType::SAN_SANG) && a.get_ngay_dat() + 4 < current_date){
        a.set_status(StatusType::QUA_HAN_DAT);
        book b;
        book_data.find(a.get_book_id(), b);
        b.set_tong_sach_ranh(b.get_tong_sach_ranh() + 1);
        b.set_tong_sach_dang_dat(b.get_tong_sach_dang_dat() - 1);
        book_data.update(b, b);
        ghi_book(book_data);
    }
    kiem_tra_sach_qua_han_helper(node->getRight(), b, current_date);
    return nullptr;
}
void BST_Borrow::kiem_tra_sach_qua_han(BST_Borrow &b){
    my_time current_date = my_time::now();
    kiem_tra_sach_qua_han_helper(root, b, current_date);
}

Node<borrow>* BST_Borrow::tong_sach_dat_muon_qua_han_helper(Node<borrow>* node, int &tong_sach_dat, int &tong_sach_muon, int &tong_sach_qua_han, my_time current_date){
    if (!node) return nullptr;
    tong_sach_dat_muon_qua_han_helper(node->getLeft(), tong_sach_dat, tong_sach_muon, tong_sach_qua_han, current_date);
    borrow& a = node->getData();
    if (a.get_status() == StatusType::XU_LY || a.get_status() == StatusType::SAN_SANG){
        tong_sach_dat++;
    }
    if (a.get_status() == StatusType::DANG_MUON && current_date <= a.get_ngay_phai_tra()){
        tong_sach_muon++;
    }
    if (a.get_status() == StatusType::DANG_MUON && current_date > a.get_ngay_phai_tra()){
        tong_sach_qua_han++;
    }
    if (a.get_status() == StatusType::QUA_HAN_MUON){
        tong_sach_qua_han++;
    }
    tong_sach_dat_muon_qua_han_helper(node->getRight(), tong_sach_dat, tong_sach_muon, tong_sach_qua_han, current_date);
    return nullptr;
}

void BST_Borrow::tong_sach_dat_muon_qua_han(int &tong_sach_dat, int &tong_sach_muon, int &tong_sach_qua_han){
    tong_sach_dat = 0;
    tong_sach_muon = 0;
    tong_sach_qua_han = 0;
    my_time current_date = my_time::now();
    tong_sach_dat_muon_qua_han_helper(root, tong_sach_dat, tong_sach_muon, tong_sach_qua_han, current_date);
}

void BST_Borrow::tim_sach_dat_thu_thu(BST_Borrow &b){
    //xoa sach dat cua doc gia trong BST_borrow
    while (b.count_data() > 0){
        b.remove_by_Key(b.find_max_id());
    }
    borrow_data.traverse_ascending([&b](borrow& a) {
        if (a.get_status() == StatusType::XU_LY || a.get_status() == StatusType::SAN_SANG || a.get_status() == StatusType::QUA_HAN_DAT){
            b.insert(a);
        }
    });
}

void BST_Borrow::tim_sach_muon_thu_thu(BST_Borrow &b){
    //xoa sach muon cua doc gia trong BST_borrow
    while (b.count_data() > 0){
        b.remove_by_Key(b.find_max_id());
    }
    borrow_data.traverse_ascending([&b](borrow& a) {
        if (a.get_status() == StatusType::DANG_MUON || a.get_status() == StatusType::QUA_HAN_MUON){
            b.insert(a);
        }
    });
}

void BST_Borrow::tim_sach_tra_thu_thu(BST_Borrow &b){
    //xoa sach muon cua doc gia trong BST_borrow
    while (b.count_data() > 0){
        b.remove_by_Key(b.find_max_id());
    }
    borrow_data.traverse_ascending([&b](borrow& a) {
        if (a.get_status() == StatusType::TRA_DUNG_HAN || a.get_status() == StatusType::TRA_QUA_HAN){
            b.insert(a);
        }
    });
}
void BST_Borrow::thong_ke_sach_dat(int &xu_ly, int &san_sang, int &qua_han, BST_Borrow &b){
    xu_ly = 0;
    san_sang = 0;
    qua_han = 0;
    b.traverse_ascending([&xu_ly, &san_sang, &qua_han](borrow& a) {
        if (a.get_status() == StatusType::XU_LY){
            xu_ly++;
        }
        else if (a.get_status() == StatusType::SAN_SANG){
            san_sang++;
        }
        else if (a.get_status() == StatusType::QUA_HAN_DAT){
            qua_han++;
        }
    });
}
void BST_Borrow::thong_ke_sach_muon(int &dang_muon, int &qua_han, BST_Borrow &b){
    dang_muon = 0;
    qua_han = 0;
    b.traverse_ascending([&dang_muon, &qua_han](borrow& a) {
        if (a.get_status() == StatusType::DANG_MUON){
            dang_muon++;
        }
        else if (a.get_status() == StatusType::QUA_HAN_MUON){
            qua_han++;
        }
    });
}

void BST_Borrow::thong_ke_sach_tra(int &tong_luot_tra, int &tra_qua_han, int &hu_hong_mat, long long &tong_tien_phat, BST_Borrow &b){
    tong_luot_tra = 0;
    hu_hong_mat = 0;
    tra_qua_han = 0;
    tong_tien_phat = 0;
    b.traverse_ascending([&tong_luot_tra, &hu_hong_mat, &tra_qua_han, &tong_tien_phat](borrow& a) {
        if (a.get_status() == StatusType::TRA_DUNG_HAN || a.get_status() == StatusType::TRA_QUA_HAN){
            tong_luot_tra++;
            tong_tien_phat += a.get_tien_phat();
            if (a.get_status() == StatusType::TRA_QUA_HAN){
                tra_qua_han++;
            }
        }
        if (a.get_tinh_trang_sach() == TinhTrangsach::HONG || a.get_tinh_trang_sach() == TinhTrangsach::MAT){
            hu_hong_mat++;
        }
    });
}
