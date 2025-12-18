#ifndef GLOBAL_H
#define GLOBAL_H
#include "my_file.h"
#include <iostream>
#include <QPixmap>
using namespace std;
extern FILE *peoples;
extern BST_Accout accout_data;
extern BST_Book book_data;
extern BST_book_copy book_copy_data;
extern BST_Borrow borrow_data;
extern BST_Borrow borrow_user_data;
extern BST_The_loai the_loai_data;
extern BST_Chuyen_nganh chuyen_nganh_data;
extern BST_History record;
extern BST_Yeu_thich yeu_thich_data;
extern accout acc_sign_in;
extern int is_sign_in;

void box_thong_bao(std::string s);
#endif // GLOBAL_H
