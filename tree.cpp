#include "tree.h"
#include "my_string.h"
#include <iostream>
#include <QTextStream>
#include <QString>
#include <QDebug>
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
    void destroy_account(Node_Accout* node) {
        if (!node) return;
        destroy_account(node->getLeft());
        destroy_account(node->getRight());
        delete node;
    }
    void destroy_book(Node_Book* node) {
        if (!node) return;
        destroy_book(node->getLeft());
        destroy_book(node->getRight());
        delete node;
    }
    void destroy_borrow(Node_Borrow* node) {
        if (!node) return;
        destroy_borrow(node->getLeft());
        destroy_borrow(node->getRight());
        delete node;
    }
}


BST_Book::~BST_Book() {
    destroy_book(root);
}

BST_Accout::~BST_Accout() {
    destroy_account(root);
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
    out << QString::fromStdString(a.getDate_created())<< '\n';
    write(node->getRight(), out);
}
void BST_Accout::write_accout(QTextStream &out) const {
    write(root, out);
}

///////////////////////////////////////////////////////////////////\


Node_Book* BST_Book::add_Book(Node_Book* node, book &value,int &ok){
    if (node == nullptr){
        ok = 1;
        return new Node_Book(value);
    }
    if (value.get_id_book() < node->getData().get_id_book()){
        node->setLeft(add_Book(node->getLeft(), value,ok));
    } else if (value.get_id_book() > node->getData().get_id_book()){
        node->setRight(add_Book(node->getRight(), value,ok));
    } else {
        ok = 0;
    }
    return node;
}

Node_Book* BST_Book::search_Book(Node_Book* node, string id, int &ok, book &a){
    if (node == nullptr){
        ok = 0;
        return nullptr;
    }
    if (id == node->getData().get_id_book()){
        ok = 1;
        a = node->getData();
        return node;
    }
    if (id < node->getData().get_id_book()){
        return search_Book(node->getLeft(), id, ok, a);
    } else{
        return search_Book(node->getRight(), id, ok, a);
    }
}

Node_Book* BST_Book::delete_Book(Node_Book* node, book data, int &ok){
    if (node == nullptr){
        ok = 0;
        return nullptr;
    }
    if (data.get_id_book() < node->getData().get_id_book()){
        node->setLeft(delete_Book(node->getLeft(), data, ok));
    } else if (data.get_id_book() > node->getData().get_id_book()){
        node->setRight(delete_Book(node->getRight(), data, ok));
    } else{
        ok = 1;
        if (node->getLeft() == nullptr){
            Node_Book* temp = node->getRight();
            delete node;
            return temp;
        } else if (node->getRight() == nullptr){
            Node_Book* temp = node->getLeft();
            delete node;
            return temp;
        } else {
            Node_Book* successor = node->getRight();
            while (successor->getLeft() != nullptr){
                successor = successor->getLeft();
            }
            node->setData(successor->getData());
            node->setRight(delete_Book(node->getRight(), successor->getData(), ok));
        }
    }
    return node;
}

bool BST_Book::insert_Book(book &value){
    int ok = 0;
    root = add_Book(root, value,ok);
    return ok == 1;
}

bool BST_Book::remove_Book(book &value){
    int ok = 0;
    root = delete_Book(root, value, ok);
    return ok == 1;
}

bool BST_Book::find_Book(string id, book &a){
    int ok = 0;
    search_Book(root, id, ok, a);
    return ok == 1;
}

bool BST_Book::update_Book(book &old_, book &new_){
    int ok = 0;
    Node_Book* node = search_Book(root, old_.get_id_book(), ok, old_);
    if (ok == 1) {
        node->setData(new_);
        return true;
    }
    return false;
}

int BST_Book::count(Node_Book* node) const{
    if (node == nullptr) {
        return 0;
    }
    return 1 + count(node->getLeft()) + count(node->getRight());
}

int BST_Book::count_book(){
    return count(root);
}

int BST_Book::count_book() const{
    return count(root); 
}

void BST_Book::write_csv(Node_Book* node, QTextStream &out) const {
    if (!node) return;
    write_csv(node->getLeft(), out);
    book& a = node->getData();
    out << QString::fromStdString(a.get_id_book())      << ',' << '\"'
        << QString::fromStdString(a.get_name_book())    << '\"' << ',' << '\"'
        << QString::fromStdString(a.get_tac_gia())      << '\"' << ','
        << QString::fromStdString(a.get_the_loai())     << ','
        << QString::fromStdString(a.get_nha_xuat_ban()) << ','
        << QString::fromStdString(a.get_nam_xuat_ban()) << ','
        << QString::fromStdString(a.get_so_trang())     << ','
        << QString::fromStdString(a.get_ISBN())         << ','
        << QString::fromStdString(a.get_ngon_ngu())     << ',' << '\"'
        << QString::fromStdString(a.get_tu_khoa())      << '\"' << ','
        << QString::fromStdString(a.get_chuyen_nganh()) << ','
        << QString::fromStdString(a.get_don_gia())      << ',' << "\""
        << QString::fromStdString(a.get_tom_tat())      << '\"' << ','
        << QString::fromStdString(a.get_link_png())     << ','
        << QString::fromStdString(a.get_link_pdf())     << ','
        << QString::fromStdString(a.get_type_book())    << ','
        << QString::fromStdString(a.get_tinh_trang())   << ','
        << QString::fromStdString(a.get_date_created()) <<','
        << QString::fromStdString(a.get_admin_created())<< '\n';
    write_csv(node->getRight(), out);
}
void BST_Book::write_book(QTextStream &out) const {
    // Ghi dòng tiêu đề
    out << "ID_BOOK,Tên sách,Tên tác giả,Thể loại,Nhà xuất bản,Năm xuất bản,Số trang,ISBN,Ngôn ngữ,Từ khóa,Chuyên ngành,Đơn giá,Tóm tắt,link_png,link_pdf,type_book,Tình trạng,Date_created, By\n";
    write_csv(root, out);
}
book BST_Book::operator[](int index) {
    if (index < 0 || index >= count_book()) {
        qDebug() << "Loi index";
    }
    Node_Book* result = root;
    int tmp = 0;
    while (result) {
        int leftCount = count(result->getLeft());
        if (index < tmp + leftCount) {
            result = result->getLeft();
        } else if (index > tmp + leftCount) {
            tmp += leftCount + 1;
            result = result->getRight();
        } else {
            return result->getData();
        }
    }
}

void BST_Book::tong_hop_sach_chung_Node(string &the_loai, string &chuyen_nganh, Node_Book* node, BST_Book &b){
    if (!node) return;
    tong_hop_sach_chung_Node(the_loai, chuyen_nganh, node->getLeft(), b);
    book& a = node->getData();
    int check1 = tim_kiem_xau(the_loai, a.get_the_loai());
    int check2 = tim_kiem_xau(chuyen_nganh, a.get_chuyen_nganh());
    if (check1 == count_string(the_loai) && check2 == count_string(chuyen_nganh)){
        b.insert_Book(a);
    }
    tong_hop_sach_chung_Node(the_loai, chuyen_nganh, node->getRight(), b);
}

void BST_Book::tong_hop_sach_chung(string &the_loai, string &chuyen_nganh,const BST_Book &book_data_, BST_Book &b){
    tong_hop_sach_chung_Node(the_loai, chuyen_nganh, book_data_.root, b);
}
/////////////////////////////////////////////////////////////////////////
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
int BST_string::count_string(){
    return count(root);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////
BST_Borrow::~BST_Borrow() {
    destroy_borrow(root);
}
string BST_Borrow::find_new_id_borrow(){
    int month_id = 0;
    int year_id = 0;
    int id_ = 0;
    Node_Borrow* node = root;  
    my_time t;
    t.set_time_now();
    month_id = t.get_thang();
    year_id = t.get_nam();
    while (node){
        if (node->getRight() == nullptr) break;
        node = node->getRight();
    }
    if (node){
        string id_borrow = node->getData().get_borrow_id();
        month_id = to_int(id_borrow.substr(0,2));
        year_id = to_int(id_borrow.substr(2,4));
        id_ = to_int(id_borrow.substr(6,4));
        if (month_id == t.get_thang() && year_id == t.get_nam()){
            id_++;
        }
        else{
            id_ = 1;
            month_id = t.get_thang();
            year_id = t.get_nam();
        }
        string month_str = toFixedString(month_id,2);
        string year_str = toFixedString(year_id,4);
        string id_str = toFixedString(id_,4);
        return month_str + year_str + id_str;
    }
    else{
        id_ = 1;
        month_id = t.get_thang();
        year_id = t.get_nam();
        string month_str = toFixedString(month_id,2);
        string year_str = toFixedString(year_id,4);
        string id_str = toFixedString(id_,4);
        return month_str + year_str + id_str;
    }

}
borrow BST_Borrow::operator[](int index) {
    if (index < 0 || index >= count_borrow()) {
        qDebug() << "Loi index";
    }
    Node_Borrow* result = root;
    int tmp = 0;
    while (result) {
        int leftCount = count(result->getLeft());
        if (index < tmp + leftCount) {
            result = result->getLeft();
        } else if (index > tmp + leftCount) {
            tmp += leftCount + 1;
            result = result->getRight();
        } else {
            return result->getData();
        }
    }
}
bool BST_Borrow::add_helper_1(const string& id_1, const string& id_2) {
    string year_1 = id_1.substr(2,4);
    string month_1 = id_1.substr(0,2);
    string STT_1 = id_1.substr(6,4);
    string year_2 = id_2.substr(2,4);
    string month_2 = id_2.substr(0,2);
    string STT_2 = id_2.substr(6,4);
    if (to_int(year_1) < to_int(year_2)) return true;
    if (to_int(year_1) == to_int(year_2) && to_int(month_1) < to_int(month_2)) return true;
    if (to_int(year_1) == to_int(year_2) && to_int(month_1) == to_int(month_2) && to_int(STT_1) < to_int(STT_2)) return true;
    return false;
}
bool BST_Borrow::add_helper_2(const string& id_1, const string& id_2) {
    string year_1 = id_1.substr(2,4);
    string month_1 = id_1.substr(0,2);
    string STT_1 = id_1.substr(6,4);
    string year_2 = id_2.substr(2,4);
    string month_2 = id_2.substr(0,2);
    string STT_2 = id_2.substr(6,4);
    if (to_int(year_1) > to_int(year_2)) return true;
    if (to_int(year_1) == to_int(year_2) && to_int(month_1) > to_int(month_2)) return true;
    if (to_int(year_1) == to_int(year_2) && to_int(month_1) == to_int(month_2) && to_int(STT_1) > to_int(STT_2)) return true;
    return false;
}


Node_Borrow* BST_Borrow::add_Borrow(Node_Borrow* node, borrow &value,int &ok){
    if (node == nullptr){
        ok = 1;
        return new Node_Borrow(value);
    }
    if (add_helper_1(value.get_borrow_id() , node->getData().get_borrow_id())){
        node->setLeft(add_Borrow(node->getLeft(), value,ok));
    } else if (add_helper_2(value.get_borrow_id() , node->getData().get_borrow_id())){
        node->setRight(add_Borrow(node->getRight(), value,ok));
    } else {
        ok = 0;
    }
    return node;
}
Node_Borrow* BST_Borrow::search_Borrow(Node_Borrow* node, string id, int &ok, borrow &a){
    if (node == nullptr){
        ok = 0;
        return nullptr;
    }
    if (id == node->getData().get_borrow_id()){
        ok = 1;
        a = node->getData();
        return node;
    }
    if (id < node->getData().get_borrow_id()){
        return search_Borrow(node->getLeft(), id, ok, a);
    } else{
        return search_Borrow(node->getRight(), id, ok, a);
    }
}
Node_Borrow* BST_Borrow::delete_Borrow(Node_Borrow* node, borrow data, int &ok){
    if (node == nullptr){
        ok = 0;
        return nullptr;
    }
    if (data.get_borrow_id() < node->getData().get_borrow_id()){
        node->setLeft(delete_Borrow(node->getLeft(), data, ok));
    } else if (data.get_borrow_id() > node->getData().get_borrow_id()){
        node->setRight(delete_Borrow(node->getRight(), data, ok));
    } else{
        ok = 1;
        if (node->getLeft() == nullptr){
            Node_Borrow* temp = node->getRight();
            delete node;
            return temp;
        } else if (node->getRight() == nullptr){
            Node_Borrow* temp = node->getLeft();
            delete node;
            return temp;
        } else {
            Node_Borrow* successor = node->getRight();
            while (successor->getLeft() != nullptr){
                successor = successor->getLeft();
            }
            node->setData(successor->getData());
            node->setRight(delete_Borrow(node->getRight(), successor->getData(), ok));
        }
    }
    return node;
}
int BST_Borrow::count(Node_Borrow* node) const{
    if (node == nullptr) {
        return 0;
    }
    return 1 + count(node->getLeft()) + count(node->getRight());
}
bool BST_Borrow::insert_Borrow(borrow &value){
    int ok = 0;
    root = add_Borrow(root, value,ok);
    return ok == 1;
}
bool BST_Borrow::remove_Borrow(borrow &value){
    int ok = 0;
    root = delete_Borrow(root, value, ok);
    return ok == 1;
}
bool BST_Borrow::find_Borrow(string id, borrow &a){
    int ok = 0;
    search_Borrow(root, id, ok, a);
    return ok == 1;
}
bool BST_Borrow::update_Borrow(borrow &old_, borrow &new_){
    int ok = 0;
    Node_Borrow* node = search_Borrow(root, old_.get_borrow_id(), ok, old_);
    if (ok == 1) {
        node->setData(new_);
        return true;
    }
    return false;
}
int BST_Borrow::count_borrow(){
    return count(root);
}
int BST_Borrow::count_borrow() const{
    return count(root); 
}
void BST_Borrow::write_csv(Node_Borrow* node, QTextStream &out) const {
    if (!node) return;
    write_csv(node->getLeft(), out);
    borrow& a = node->getData();
    out << QString::fromStdString(a.get_borrow_id())    << ','
        << QString::fromStdString(a.get_id_book())      << ','
        << QString::fromStdString(a.get_id_user())      << ',' << '\"'
        << QString::fromStdString(a.get_id_admin())     << '\"'<< ','
        << QString::fromStdString(a.get_booking_date()) << ','
        << QString::fromStdString(a.get_borrow_date())  << ','
        << QString::fromStdString(a.get_pay_date())     << ','
        << QString::fromStdString(a.get_status())       << ','
        << QString::fromStdString(a.get_return_date())  << ','
        << QString::fromStdString(a.get_tien_phat())    << '\n';

    write_csv(node->getRight(), out);
}
void BST_Borrow::write_borrow(QTextStream &out) const {
    // Ghi dòng tiêu đề
    out << "ID, ID_BOOK, ID_USER, ID_ADMIN, BOOKIND DATE, BORROW_DATE, PAY_DATE, STATUS, RETURN_DATE, TIEN_PHAT\n";
    write_csv(root, out);
}
