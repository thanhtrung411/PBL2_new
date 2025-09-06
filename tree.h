#ifndef TREE_H
#define TREE_H
#include <iostream>
#include "accout.h"
#include "book.h"
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
    void write_book(Node_Book* node, fstream &file);
    int count_book() const;
    void write_book(fstream &file) const;
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
    void write(Node_Accout* node,std::fstream &file) const;
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
    void write_accout(fstream &file) const;
};
    
#endif // TREE_H
