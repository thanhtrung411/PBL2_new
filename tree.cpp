#include "tree.h"
#include <iostream>
#include <QTextStream>
#include <QString>
#include <fstream>
using namespace std;
/*
Node_Accout* add_Accout(Node_Accout* node, accout &value,int ok);
    Node_Accout* search_Accout(Node_Accout* node, string id, int &ok, accout &a);
    Node_Accout* delete_Accout(Node_Accout* node, accout data, int &ok);
bool insert_Accout(accout &value);
    bool remove_Accout(accout &value);
    bool find_Accout(string id, accout &a);
    bool update_Accout(accout &old_, accout &new_);
*/

namespace{
    void destroy(Node_Accout* node) {
        if (!node) return;
        destroy(node->getLeft());
        destroy(node->getRight());
        delete node;
    }
}
BST_Accout::~BST_Accout() {
    destroy(root);
}

Node_Accout* BST_Accout::add_Accout(Node_Accout* node, accout &value,int &ok){
    if (node == nullptr){
        ok = 1;
        return new Node_Accout(value);
    }
    if (value.getAccout_id() < node->getData().getAccout_id()){
        node->setLeft(add_Accout(node->getLeft(), value,ok));
    } else if (value.getAccout_id() > node->getData().getAccout_id()){
        node->setRight(add_Accout(node->getRight(), value,ok));
    } else {
        ok = 0;
    }
    return node;
}

Node_Accout* BST_Accout::search_Accout(Node_Accout* node, string id, int &ok, accout &a){
    if (node == nullptr){
        ok = 0;
        return nullptr;
    }
    if (id == node->getData().getAccout_id()){
        ok = 1;
        a = node->getData();
        return node;
    }
    if (id < node->getData().getAccout_id()){
        return search_Accout(node->getLeft(), id, ok, a);
    } else{
        return search_Accout(node->getRight(), id, ok, a);
    }
}

Node_Accout* BST_Accout::delete_Accout(Node_Accout* node, accout data, int &ok){
    if (node == nullptr){
        ok = 0;
        return nullptr;
    }
    if (data.getAccout_id() < node->getData().getAccout_id()){
        node->setLeft(delete_Accout(node->getLeft(), data, ok));
    } else if (data.getAccout_id() > node->getData().getAccout_id()){
        node->setRight(delete_Accout(node->getRight(), data, ok));
    } else{
        ok = 1;
        if (node->getLeft() == nullptr){
            Node_Accout* temp = node->getRight();
            delete node;
            return temp;
        } else if (node->getRight() == nullptr){
            Node_Accout* temp = node->getLeft();
            delete node;
            return temp;
        } else {
            Node_Accout* successor = node->getRight();
            while (successor->getLeft() != nullptr){
                successor = successor->getLeft();
            }
            node->setData(successor->getData());
            node->setRight(delete_Accout(node->getRight(), successor->getData(), ok));
        }
    }
    return node;
}

bool BST_Accout::insert_Accout(accout &value){
    int ok = 0;
    root = add_Accout(root, value,ok);
    return ok == 1;
}
bool BST_Accout::remove_Accout(accout &value){
    int ok = 0;
    root = delete_Accout(root, value, ok);
    return ok == 1;
}

bool BST_Accout::find_Accout(string id, accout &a){
    int ok = 0;
    search_Accout(root, id, ok, a);
    return ok == 1;
}

Node_Accout* BST_Accout::check_accout_helper(Node_Accout* node, string id, string pass, int &ok, accout &a){
    if (node == nullptr){
        ok = 0;
        return nullptr;
    }
    if (id == node->getData().getAccout_id() && pass == node->getData().getPass()){
        ok = 1;
        a = node->getData();
        return node;
    }
    if (id < node->getData().getAccout_id()){
        return check_accout_helper(node->getLeft(), id, pass, ok, a);
    } else{
        return check_accout_helper(node->getRight(), id, pass, ok, a);
    }
}

bool BST_Accout::check_accout(string id, string pass, accout &a){
    int ok = 0;
    check_accout_helper(root, id, pass, ok, a);
    return ok == 1;
}

bool BST_Accout::update_Accout(accout &old_, accout &new_){
    int ok = 0;
    Node_Accout* node = search_Accout(root, old_.getAccout_id(), ok, old_);
    if (ok == 1) {
        node->setData(new_);
        return true;
    }
    return false;
}

int BST_Accout::count(Node_Accout* node) const{
    if (node == nullptr) {
        return 0;
    }
    return 1 + count(node->getLeft()) + count(node->getRight());
}

int BST_Accout::count_accout(){
    return count(root);
}
int BST_Accout::count_accout() const{
    return count(root); 
}
void BST_Accout::write(Node_Accout* node, QTextStream &out) const {
    if (!node) return;
    write(node->getLeft(), out);
    accout& a = node->getData();
    out << QString::fromStdString(a.getAccout_id())   << '\n';
    out << QString::fromStdString(a.getAccout_Name()) << '\n';
    out << QString::fromStdString(a.getEmail())       << '\n';
    out << QString::fromStdString(a.getPhonenumber()) << '\n';
    out << a.getGioi_tinh()                           << '\n';
    out << a.getDoi_tuong()                           << '\n';
    out << QString::fromStdString(a.getNgay_sinh())   << '\n';
    out << QString::fromStdString(a.getPass())        << '\n';
    out << QString::fromStdString(a.getlevel())       << '\n';
    write(node->getRight(), out);
}
void BST_Accout::write_accout(QTextStream &out) const {
    write(root, out);
}
