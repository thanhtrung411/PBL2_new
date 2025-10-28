#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <QTextStream>
#include "accout.h"
#include "book.h"
#include "the_loai_chuyen_nganh.h"
#include "author.h"
#include "book_copies.h"
#include "borrow.h"
#include "description.h"
using namespace std;

class accout;
class book;
class Book_copies;
class Author;
class Chuyen_nganh;
class The_loai;
class borrow;
class my_time;

template <typename T>

class Node{
private:
    T data;
    Node<T>* left;
    Node<T>* right;
    int height;
public:
    explicit Node(const T& value) : data(value), left(nullptr), right(nullptr), height(1) {}
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

};

template <typename T, typename Key>
class BST{
protected:
    Node<T>* root;
    Key (*getKey)(const T&);
    int height(Node<T>* node) const;
    int getBalanceFactor(Node<T>* node) const;
    void updateHeight(Node<T>* node);
    Node<T>* rightRotate(Node<T>* y);
    Node<T>* leftRotate(Node<T>* x);
    Node<T>* balance(Node<T>* node);

    Node<T>* add_Node(Node<T>* node, const T& value, int &ok);
    Node<T>* search_Node(Node<T>* node, const Key& key);
    Node<T>* delete_Node(Node<T>* node, T data, int &ok);
    int count(Node<T>* node) const;
    void destroy_Node(Node<T>* node);
    Key find_max_key(Node<T>* node) const;
public:
    BST(Key (*getter)(const T&)): root(nullptr), getKey(getter) {}
    ~BST();
    bool insert(const T& value);
    bool remove(const T& value);
    bool find(Key id, T& result);
    bool update(T &old_, T &new_);
    Key find_max_id() const;
    int count_data() const;
    T operator[](int index);
};
namespace KeyGetters {
    int getAccoutID(const accout& a);
    long long getBookID(const book& b);
    long long getBookCopiesID(const Book_copies& bc);
    int getAuthorID(const Author& au);
    int getTheLoaiID(const The_loai& tl); 
    int getChuyenNganhID(const Chuyen_nganh& cn);
    long long getBorrowID(const borrow& br);
}

class BST_Accout : public BST<accout, int> {
private:
    Node<accout>* check_accout_helper(Node<accout>* node, string ten_dang_nhap, string pass, int &ok, accout &a);
public:
    BST_Accout() : BST<accout, int>(KeyGetters::getAccoutID) {}
    bool check_accout(string ten_dang_nhap, string pass, accout& a); 
    void write_csv(Node<accout>* node, QTextStream &out) const;
    void write_accout(QTextStream &out) const;
};

class BST_Book : public BST<book, long long> {
private:
    Node<book>* tong_hop_sach_TL_CN_Node(int The_loai_ID, int Chuyen_nganh_ID, Node<book>* node, BST_Book &b);
public:
    void tong_hop_sach_TL_CN(int The_loai_ID, int Chuyen_nganh_ID, BST_Book &b, BST_Book &book_data_);
    long long tong_hop_sach_find_max_id(BST_Book &b);
    BST_Book() : BST<book, long long>(KeyGetters::getBookID) {}
    //void write_book(QTextStream &out) const;
};

class BST_book_copy : public BST<Book_copies, long long> {
public:
    BST_book_copy() : BST<Book_copies, long long>(KeyGetters::getBookCopiesID) {}
    //void write_book_copy(QTextStream &out) const;
};

class BST_Author : public BST<Author, int> {
public:
    BST_Author() : BST<Author, int>(KeyGetters::getAuthorID) {}
    //void write_author(QTextStream &out) const;
};

class BST_Chuyen_nganh : public BST<Chuyen_nganh, int> {
private:
    Node<Chuyen_nganh>* return_name_helper(Node<Chuyen_nganh>* node, int id, int &ok, string &name);
    Node<Chuyen_nganh>* return_id_helper(Node<Chuyen_nganh>* node, string name, int &ok, int &id);
public:
    BST_Chuyen_nganh() : BST<Chuyen_nganh, int>(KeyGetters::getChuyenNganhID) {}
    string return_name(int id);
    int return_id(string name);
    void write_chuyen_nganh(QTextStream &out) const;
};

class BST_The_loai : public BST<The_loai, int> {
private:
    Node<The_loai>* return_name_helper(Node<The_loai>* node, int id, int &ok, string &name);
    Node<The_loai>* return_id_helper(Node<The_loai>* node, string name, int &ok, int &id);
public:
    BST_The_loai() : BST<The_loai, int>(KeyGetters::getTheLoaiID) {}
    string return_name(int id);
    int return_id(string name);
    void write_the_loai(QTextStream &out) const;
};

class Node_string{
private:
    string data;
    int vt;
    Node_string* left;
    Node_string* right;
public:
    explicit Node_string(string &value, int v = 0): data(value), vt(v), left(nullptr), right(nullptr){}
    Node_string* getLeft() const { return left; }
    Node_string* getRight() const { return right; }
    string& getData(){ return data; }
    int& getVt(){ return vt; }
    void setLeft(Node_string* node){ left = node; }
    void setRight(Node_string* node){ right = node; }
    void setData(const string& value){ data = value; }
    void setVt(const int& value){ vt = value; }
};

class BST_string {
private:
    Node_string* root;
    Node_string* add_string(Node_string* node, string &value, int &ok);
    Node_string* search_string(Node_string* node, string id, int &ok, string &a);
    Node_string* delete_string(Node_string* node, string data, int &ok);
    int count(Node_string* node) const;
public:
    BST_string(): root(nullptr) {}
    ~BST_string();
    void destroy_string(Node_string* node);
    bool insert_string(string &value);
    bool remove_string(string &value);
    bool find_string(string id, string &a);
    int count_string() const;
    void write(Node_string* node, QTextStream &out) const;
    void write_string(QTextStream &out) const;
    string operator[](int index);
};

class BST_Borrow : public BST<borrow, long long> {
public:
    BST_Borrow() : BST<borrow, long long>(KeyGetters::getBorrowID) {}
    ~BST_Borrow() = default;

    long long find_new_id_borrow() const {
        return find_max_id() + 1;
    }

    bool find_Borrow(long long id, borrow &a) { return find(id, a); }
    bool update_Borrow(borrow &old_, borrow &new_) { return update(old_, new_); }
    
    borrow operator[](int index) { return BST::operator[](index); }
    int count_borrow() const { return count_data(); }
    void write_csv(Node<borrow>* node, QTextStream &out) const; // Cần thay đổi tham số
    void write_borrow(QTextStream &out) const;
};

#endif // TREE_H
