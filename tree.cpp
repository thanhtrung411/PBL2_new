#include "tree.h"
#include "global.h"
#include "my_string.h"
#include <iostream>
#include <QTextStream>
#include <QString>
#include <QDebug>
#include <fstream>

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
bool BST<T, Key>::remove(const T& value) {
    int ok = 0;
    root = delete_Node(root, value, ok);
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

////////////--for BST_string--//////////////
BST_string::~BST_string() {
    destroy_string(root);
}
void BST_string::destroy_string(Node_string* node) {
    if (!node) return;
    destroy_string(node->getLeft());
    destroy_string(node->getRight());
    delete node;
}

int BST_string::count(Node_string* node) const{
    if (node == nullptr) {
        return 0;
    }
    return 1 + count(node->getLeft()) + count(node->getRight());
}
int BST_string::count_string() const{
    return count(root);
}
Node_string* BST_string::add_string(Node_string* node, string &value, int &ok) {
    if (!node) {
        int vt_new = count_string();
        Node_string* newNode = new Node_string(value, vt_new);
        ok = 1;
        return newNode;
    }
    node->setRight(add_string(node->getRight(), value, ok));
    return node;
}
bool BST_string::insert_string(string &value) {
    int ok = 0;
    root = add_string(root, value, ok);
    return ok == 1;
}
Node_string* BST_string::search_string(Node_string* node, string id, int &ok, string &a) {
    if (!node) {
        ok = 0;
        return nullptr;
    }
    if (id == node->getData()) {
        ok = 1;
        a = node->getData();
        return node;
    }
    return search_string(node->getRight(), id, ok, a);
}
bool BST_string::find_string(string id, string &a) {
    int ok = 0;
    search_string(root, id, ok, a);
    return ok == 1;
}
Node_string* BST_string::delete_string(Node_string* node, string data, int &ok) {
    if (!node) return nullptr;
    if (node->getData() == data) {
        ok = 1;
        Node_string* right = node->getRight();
        delete node;
        Node_string* nextNode = right;
        while (nextNode) {
            nextNode->setVt(nextNode->getVt() - 1);
            nextNode = nextNode->getRight();
        }
        return right;
    }
    node->setRight(delete_string(node->getRight(), data, ok));
    return node;
}
bool BST_string::remove_string(string &value) {
    int ok = 0;
    root = delete_string(root, value, ok);
    return ok == 1;
}
void BST_string::write(Node_string* node, QTextStream &out) const {
    if (!node) return;
    write(node->getLeft(), out);
    string& a = node->getData();
    out << QString::fromStdString(a) << '\n';
    write(node->getRight(), out);
}
void BST_string::write_string(QTextStream &out) const {
    write(root, out);
}
string BST_string::operator[](int index) {
    if (index < 0 || index >= count_string()) {
        qDebug() << "Loi index";
        return "";
    }
    
    Node_string* current = root;
    while (current) {
        if (current->getVt() == index) {
            return current->getData();
        }
        current = current->getRight();
    }
    
    qDebug() << "Khong tim thay node voi index:" << index;
    return "";
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

int BST_Chuyen_nganh::return_id(string name){
    int ok = 0;
    int id = -1;
    Node<Chuyen_nganh>* node = return_id_helper(root, name, ok, id);
    if (ok == 1){
        return id;
    }
    return -1;
}
string BST_Chuyen_nganh::return_name(int id){
    int ok = 0;
    string name = "";
    Node<Chuyen_nganh>* node = return_name_helper(root, id, ok, name);
    if (ok == 1){
        return name;
    }
    return "";
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

int BST_The_loai::return_id(string name){
    int ok = 0;
    int id = -1;
    Node<The_loai>* node = return_id_helper(root, name, ok, id);
    if (ok == 1){
        return id;
    }
    return -1;
}
string BST_The_loai::return_name(int id){
    int ok = 0;
    string name = "";
    Node<The_loai>* node = return_name_helper(root, id, ok, name);
    if (ok == 1){
        return name;
    }
    return "";
}