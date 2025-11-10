#include "tree.h"
#include "global.h"
#include "my_string.h"
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
    inline string lower(string s){
        for(char &c: s) c = std::tolower((unsigned char)c);
        return s;
    }
    std::pair<string,long long> getKey_Name_ID   (const book& b) { return { lower(b.get_Name()),              b.get_ID() }; }
    std::pair<string,long long> getKey_Author_ID (const book& b) { return { lower(b.get_Author()),            b.get_ID() }; }
    std::pair<string,long long> getKey_TL_ID     (const book& b) { return { lower(b.get_The_loai_name()),     b.get_ID() }; }
    std::pair<string,long long> getKey_CN_ID     (const book& b) { return { lower(b.get_Chuyen_nganh_name()), b.get_ID() }; }
    std::pair<int,long long>    getKey_DoCX_ID   (const book& b) { return { b.get_do_chinh_xac(),             b.get_ID() }; }
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
        return (Key)0;
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
        return Key(0);
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

////////////--for BST_string--//////////////
bool BST_string::co_chua_string(string& key_word) {
    Node<string>* node = search_Node(root, key_word);
    return node != nullptr;
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


Node<accout>* BST_Accout::check_accout_helper(Node<accout>* node, string ten_dang_nhap, string pass, int &ok, accout &a){
    if (node == nullptr){
        ok = 0;
        return nullptr;
    }
    if (ten_dang_nhap < node->getData().get_ten_dang_nhap()){
        return check_accout_helper(node->getLeft(), ten_dang_nhap, pass, ok, a);
    }
    if (ten_dang_nhap == node->getData().get_ten_dang_nhap() && pass == node->getData().get_pass()){
        ok = 1;
        a = node->getData();
        return node;
    }
    if (ten_dang_nhap > node->getData().get_ten_dang_nhap()){
        return check_accout_helper(node->getRight(), ten_dang_nhap, pass, ok, a);
    }
    ok = 0;
    return nullptr;
}


bool BST_Accout::check_accout(string ten_dang_nhap, string pass, accout& a){
    int ok = 0;
    Node<accout>* node = check_accout_helper(root, ten_dang_nhap, pass, ok, a);
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

/////////////--for BST_Borrow--//////////////

void BST_Borrow::write_csv(Node<borrow>* node, QTextStream &out) const {
    if (!node) return;
    write_csv(node->getLeft(), out);
    borrow& a = node->getData();
    write_csv(node->getRight(), out);
}
void BST_Borrow::write_borrow(QTextStream &out) const {
    out << "ID, Book_copy_id, User_id, Admin_id, Booking_date, Borrow_date, Due_date, Return_date, Status, Tien_phat\n";
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
    switch (type_bieu_ghi)
    {
    case 0:{
        
        break;
    }
    case 1:{
        if (type_tuy_chon == 0) {
            int count_temp = tim_kiem_co_chua(key_word, a.get_Name());
            if (!count_temp) {
                return false;
            }
            if (count_temp > a.get_do_chinh_xac()) count = count_temp;
            a.set_do_chinh_xac(count);
            return true;
            break;
        }
        else if (type_tuy_chon == 1) {
            count = tim_kiem_chinh_xac(key_word, a.get_Name());
            if (!count) {
                return false;
            }
            a.set_do_chinh_xac(count);
            return true;
            break;
        }
        else if (type_tuy_chon == 2) {
            count = tim_kiem_bat_dau_bang(key_word, a.get_Name());
            if (!count) {
                return false;
            }
            a.set_do_chinh_xac(count);
            return true;
            break;
        }
    }
    case 2:{
        /* code */
        break;
    }
    case 3:{
        /* code */
        break;
    }
    case 4:{
        /* code */
        break;
    }
    case 5:{
        /* code */
        break;
    }
    case 6:{
        /* code */
        break;
    }
    case 7:{
        /* code */
        break;
    }
    case 8:{
        /* code */
        break;
    }
    default:
        break;
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
    book& a = node->getData();
    if (type_the_loai != 0){
        if (a.get_The_loai_ID() == type_the_loai){

            
        }
            return nullptr;
        
    }
    search_help(type_the_loai, type_tuy_chon, type_bieu_ghi, key_word, node->getLeft(), kq_return);
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
        << QString::number(a.get_ID()) << "," 
        << QString::fromStdString(a.get_Name()) << "," << "\""
        << QString::fromStdString(a.get_Author()) << "\"" << "," 
        << QString::fromStdString(a.get_NXB()) << ","
        << QString::number(a.get_NamXB()) << ","
        << QString::number(a.get_So_trang()) << ","
        << QString::fromStdString(a.get_ISBN()) << ","
        << QString::fromStdString(a.get_Language()) << "," << " \""
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
BST_Book& BST_Book::author_of_book(int author_id){
    BST_Book* b = new BST_Book();
    author_of_book_helper(author_id, root, *b);
    return *b;
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
BST_Book& BST_Book::the_loai_of_book(int the_loai_id){
    BST_Book* b = new BST_Book();
    the_loai_of_book_helper(the_loai_id, root, *b);
    return *b;
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
BST_Book& BST_Book::chuyen_nganh_of_book(int chuyen_nganh_id){
    BST_Book* b = new BST_Book();
    chuyen_nganh_of_book_helper(chuyen_nganh_id, root, *b);
    return *b;
}

///////////////--for BST_Book_copies--///////////////


/////////////--for BST_Author--/////////////

Node<Author>* BST_Author::return_name_helper(Node<Author>* node, int id, int &ok, string &name) {
    if (node == nullptr) {
        ok = 0;
        return nullptr;
    }
    Node<Author>* found = nullptr;
    if (node->getData().get_ID() == id) {
        ok = 1;
        name = node->getData().get_name();
        return node;
    }
    found = return_name_helper(node->getLeft(), id, ok, name);
    if (ok == 1) return found;
    return return_name_helper(node->getRight(), id, ok, name);
}
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
    int ok = 0;
    name = "";
    Node<Author>* node = return_name_helper(root, id, ok, name);
    return ok == 1;
}

/////////////--for BST_Chuyen_nganh--//////////////

Node<Chuyen_nganh>* BST_Chuyen_nganh::return_name_helper(Node<Chuyen_nganh>* node, int id, int &ok, string &name) {
    if (node == nullptr) {
        ok = 0;
        return nullptr;
    }
    Node<Chuyen_nganh>* found = nullptr;
    if (node->getData().get_id() == id) {
        ok = 1;
        name = node->getData().get_name();
        return node;
    }
    found = return_name_helper(node->getLeft(), id, ok, name);
    if (ok == 1) return found;
    return return_name_helper(node->getRight(), id, ok, name);
}

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
    int ok = 0;
    name = "";
    Node<Chuyen_nganh>* node = return_name_helper(root, id, ok, name);
    return ok == 1;
}

////////////--for BST_The_loai--//////////////

Node<The_loai>* BST_The_loai::return_name_helper(Node<The_loai>* node, int id, int &ok, string &name) {
    if (node == nullptr) {
        ok = 0;
        return nullptr;
    }
     Node<The_loai>* found = nullptr;
    if (node->getData().get_id() == id) {
        ok = 1;
        name = node->getData().get_name();
        return node;
    }
    found = return_name_helper(node->getLeft(), id, ok, name);
    if (ok == 1) return found;
    return return_name_helper(node->getRight(), id, ok, name);
    
}

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
    int ok = 0;
    name = "";
    Node<The_loai>* node = return_name_helper(root, id, ok, name);
    return ok == 1;
}