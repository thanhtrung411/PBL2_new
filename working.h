#ifndef WORKING_H
#define WORKING_H
#include "tree.h"

class working : public BST_Book, BST_Accout, BST_Borrow
{
public:
    static void muon_sach(string id_book_, string id_user_, string booking_date, string pay_date);
    void them_sach();
    void them_user();
    void them_admin();
    void update();
    working();
};

#endif // WORKING_H
