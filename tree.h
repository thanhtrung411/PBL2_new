#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <QTextStream>
#include "accout.h"
using namespace std;
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
    
#endif // TREE_H
