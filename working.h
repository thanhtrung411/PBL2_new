#ifndef WORKING_H
#define WORKING_H
#include "tree.h"

class working : public BST_Book, BST_Accout
{
public:
    void them_sach();
    void them_user();
    void them_admin();
    void update();
    working();
};

#endif // WORKING_H
