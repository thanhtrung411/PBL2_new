#ifndef ACCOUT_H
#define ACCOUT_H
#include <iostream>
using namespace std;

class accout{
private:
    string accout_id;
    string accout_name;
    int gioi_tinh;
    string ngay_sinh;
    string email;
    int doi_tuong;
    string phone_number;
    string pass;
public:
    accout(string accout_id,string accout_name, int gioi_tinh,string ngay_sinh,string email,int doi_tuong, string phone_number,string pass){
        this->accout_id=accout_id;
        this->accout_name=accout_name;
        this->gioi_tinh=gioi_tinh;
        this->ngay_sinh=ngay_sinh;
        this->email=email;
        this->doi_tuong=doi_tuong;
        this->phone_number=phone_number;
        this->pass=pass;
    };
    accout() {}
    ~accout() {}
    void setAccout_id(string accout_id){
        this->accout_id=accout_id;
    }
    string getAccout_id(){
        return accout_id;
    }
    void setAccout_name(string accout_name){
        this->accout_name=accout_name;
    }
    string getAccout_Name(){
        return accout_name;
    }
    void setGioi_tinh(int gioi_tinh){
        if(gioi_tinh != 1 && gioi_tinh != 0){
            cout<<"khong hop le";
        }else{
            this->gioi_tinh=gioi_tinh;
        }
    }
    int getGioi_tinh(){
        return gioi_tinh;
    }
    void setNgay_sinh(string ngay_sinh){
        this->ngay_sinh=ngay_sinh;
    }
    string getNgay_sinh(){
        return ngay_sinh;
    }
    void setEmail(string email){
        this->email=email;
    }
    string getEmail(){
        return email;
    }
    void setDoi_tuong(int doi_tuong){
        this->doi_tuong=doi_tuong;
    }
    int getDoi_tuong(){
        return doi_tuong;
    }
    void setPhonenumber(string phone_number){
        this->phone_number=phone_number;
    }
    string getPhonenumber(){
        return phone_number;
    }
    void setPass(string pass){
        this->pass=pass;
    }
    string getPass(){
        return pass;
    }
    void ma_hoa_(accout &a);
    void ma_hoa_();
};

#endif // ACCOUT_H
