#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <QTextStream>
#include "accout.h"
#include "book.h"
#include "description.h"
using namespace std;

class Node_Book{
    private:
    book data;
    Node_Book* left;
    Node_Book* right;   
    public:
    explicit Node_Book(book &value):
        data(value),
        left(nullptr),
        right(nullptr){}
    Node_Book* getLeft(){
        return left;
    }
    Node_Book* getRight() {
        return right;
    }
    book& getData(){
        return data;
    }
    void setLeft(Node_Book* node){
        left = node;
    }
    void setRight(Node_Book* node){
        right = node;
    }
    void setData(const book& value){
        data = value;
    }

};

class BST_Book {
private:
    Node_Book* root;
    Node_Book* add_Book(Node_Book* node, book &value,int &ok);
    Node_Book* search_Book(Node_Book* node, string id, int &ok, book &a);
    Node_Book* delete_Book(Node_Book* node, book data, int &ok);
    int count(Node_Book* node) const;
    void write(Node_Book* node,std::fstream &file) const;
public:
    BST_Book(): root(nullptr) {}
    ~BST_Book();
    bool insert_Book(book &value);
    bool remove_Book(book &value);
    bool find_Book(string id, book &a);
    bool update_Book(book &old_, book &new_);
    int count_book();
    void write_csv(Node_Book* node, QTextStream &out) const;
    int count_book() const;
    void write_book(QTextStream &out) const;
    void tong_hop_sach_chung_Node(string &the_loai, string &chuyen_nganh, Node_Book* node, BST_Book &b);
    void tong_hop_sach_chung(string &the_loai, string &chuyen_nganh, const BST_Book &book_data_, BST_Book &b);
    book operator[](int index);
};

class Node_Accout {
private:
    accout data;
    Node_Accout* left;
    Node_Accout* right;
public:
    explicit Node_Accout(accout &value):
        data(value),
        left(nullptr),
        right(nullptr){}
    Node_Accout* getLeft(){
        return left;
    }
    Node_Accout* getRight() {
        return right;
    }
    accout& getData(){
        return data;
    }
    void setLeft(Node_Accout* node){
        left = node;
    }
    void setRight(Node_Accout* node){
        right = node;
    }
    void setData(const accout& value){
        data = value;
    }
};

class BST_Accout {
private:
    Node_Accout* root;
    Node_Accout* add_Accout(Node_Accout* node, accout &value,int &ok);
    Node_Accout* search_Accout(Node_Accout* node, string id, int &ok, accout &a);
    Node_Accout* check_accout_helper(Node_Accout* node, string id, string pass, int &ok, accout &a);
    Node_Accout* delete_Accout(Node_Accout* node, accout data, int &ok);
    int count(Node_Accout* node) const;
    void write(Node_Accout* node, QTextStream &out) const;
public:
    BST_Accout(): root(nullptr) {}
    ~BST_Accout();
    bool insert_Accout(accout &value);
    bool remove_Accout(accout &value);
    bool find_Accout(string id, accout &a);
    bool check_accout(string id, string pass, accout&a);
    bool update_Accout(accout &old_, accout &new_);
    int count_accout();
    void write_accout(Node_Accout* node, fstream &file);
    int count_accout() const;
    void write_accout(QTextStream &out) const;
};
    
class Node_string{
private:
    string data;
    int vt;
    Node_string* left;
    Node_string* right;
public:
    explicit Node_string(string &value, int v = 0):
        data(value),
        vt(v),
        left(nullptr),
        right(nullptr){}
    Node_string* getLeft(){
        return left;
    }
    Node_string* getRight() {
        return right;
    }
    string& getData(){
        return data;
    }
    int& getVt(){
        return vt;
    }
    void setLeft(Node_string* node){
        left = node;
    }
    void setRight(Node_string* node){
        right = node;
    }
    void setData(const string& value){
        data = value;
    }
    void setVt(const int& value){
        vt = value;
    }
};

class BST_string {
private:
    Node_string* root;
    Node_string* add_string(Node_string* node, string &value, int &ok);
    Node_string* search_string(Node_string* node, string id, int &ok, string &a);
    Node_string* delete_string(Node_string* node, string data, int &ok);
    int count(Node_string* node) const;
    void write(Node_string* node,QTextStream &file) const;
public:
    BST_string(): root(nullptr) {}
    ~BST_string();
    void destroy_string(Node_string* node);
    bool insert_string(string &value);
    bool remove_string(string &value);
    bool find_string(string id, string &a);
    int count_string();
    int count_string() const;
    void write_string(QTextStream &out) const;
    string operator[](int index);
};

#endif // TREE_H
