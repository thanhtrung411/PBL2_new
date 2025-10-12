#ifndef GLOBAL_H
#define GLOBAL_H
#include "my_file.h"
#include <iostream>
using namespace std;
extern FILE *peoples;
extern BST_Accout accout_data;
extern BST_Book book_data;
extern BST_Borrow borrow_data;
extern BST_string the_loai_, chuyen_nganh_;
extern accout acc_sign_in;
extern int is_sign_in;

void box_thong_bao(std::string s);
#endif // GLOBAL_H
