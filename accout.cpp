#include "accout.h"
#include <iostream>
#include <fstream>
#include "my_string.h"
using namespace std;
#define KEY_STR "PBL2By-Do_Tran_Hoai_Nhi-Nguyen_Thanh_Trung"

/*
void accout::ma_hoa_(accout &a){
    void ma_hoa_(accout &a){
    Cac thong tin duoc ma hoa:
    - Accout_name
    - Ngay sinh
    - Email
    - Phone number
    - Password
    
    a.accout_name = ma_hoa_(a.accout_name);
    a.ngay_sinh = ma_hoa_(a.ngay_sinh);
    a.email = ma_hoa_(a.email);
    a.phone_number = ma_hoa_(a.phone_number);
    a.pass = ma_hoa_(a.pass);
    }
}
*/
void accout::ma_hoa_(){
    ten_dang_nhap = ma_hoa_str_(ten_dang_nhap);
    ten_tai_khoan = ma_hoa_str_(ten_tai_khoan);
    //ngay_sinh = ma_hoa_str_(ngay_sinh);
    email = ma_hoa_str_(email);
    phone_number = ma_hoa_str_(phone_number);
    pass = ma_hoa_str_(pass);
    level = ma_hoa_str_(level);
}

void accout::giai_ma_(){
    ten_dang_nhap = giai_ma_str_(ten_dang_nhap);
    ten_tai_khoan = giai_ma_str_(ten_tai_khoan);
    email = giai_ma_str_(email);
    phone_number = giai_ma_str_(phone_number);
    pass = giai_ma_str_(pass);
    level = giai_ma_str_(level);
}
/*
accout accout::check_accout(string id, string pass){
    FILE *accout = fopen("accout.txt","r");

}

void accout::insert(accout p){
    std::ofstream file("accout.txt", std::ios::app);
    if (!file.is_open()) {
        cout << "Loi khi doc file" << endl;
        return;
    }
    file << p.accout_id << endl;
    file << p.accout_name << endl;
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
