#include "account.h"
#include <iostream>
#include <fstream>
#include "my_string.h"
using namespace std;
#define KEY_STR "PBL2By-Do_Tran_Hoai_Nhi-Nguyen_Thanh_Trung"
#include "settings_file.h"

/*
void Account::ma_hoa_(Account &a){
    void ma_hoa_(Account &a){
    Cac thong tin duoc ma hoa:
    - Account_name
    - Ngay sinh
    - Email
    - Phone number
    - Password
    
    a.Account_name = ma_hoa_(a.Account_name);
    a.ngay_sinh = ma_hoa_(a.ngay_sinh);
    a.email = ma_hoa_(a.email);
    a.phone_number = ma_hoa_(a.phone_number);
    a.pass = ma_hoa_(a.pass);
    }
}
*/
void Account::ma_hoa_(){
    ten_dang_nhap = ma_hoa_str_(ten_dang_nhap);
    ten_tai_khoan = ma_hoa_str_(ten_tai_khoan);
    //ngay_sinh = ma_hoa_str_(ngay_sinh);
    email = ma_hoa_str_(email);
    phone_number = ma_hoa_str_(phone_number);
    pass = ma_hoa_str_(pass);
    level = ma_hoa_str_(level);
}

void Account::giai_ma_(){
    ten_dang_nhap = giai_ma_str_(ten_dang_nhap);
    ten_tai_khoan = giai_ma_str_(ten_tai_khoan);
    email = giai_ma_str_(email);
    phone_number = giai_ma_str_(phone_number);
    pass = giai_ma_str_(pass);
    level = giai_ma_str_(level);
}

int Account::max_book_borrow(){
    return settings_file::getInstance()->get_so_quyen_muon_toi_da();
}

/*
Account Account::check_Account(string id, string pass){
    FILE *Account = fopen("Account.txt","r");

}

void Account::insert(Account p){
    std::ofstream file("Account.txt", std::ios::app);
    if (!file.is_open()) {
        cout << "Loi khi doc file" << endl;
        return;
    }
    file << p.Account_id << endl;
    file << p.Account_name << endl;
    file << p.getGioi_tinh() << endl;
    file << p.getNgay_sinh() << endl;
    file << p.getEmail() << endl;
    file << p.getDoi_tuong() << endl;
    file << p.getPhonenumber() << endl;
    file << p.getPass() << endl;
    file << endl;
    file.close();
}
    */
