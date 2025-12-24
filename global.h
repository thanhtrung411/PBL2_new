#ifndef GLOBAL_H
#define GLOBAL_H
#include "my_file.h"
#include "library.h"
#include <iostream>
#include <QPixmap>
using namespace std;
class Library;
class History;
extern Library lib;
extern BST_History record;

void box_thong_bao(std::string s);
#endif // GLOBAL_H
