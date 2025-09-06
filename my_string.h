#ifndef MY_STRING_H
#define MY_STRING_H
#include <iostream>
using namespace std;
#define KEY_STR "PBL2By-Do_Tran_Hoai_Nhi-Nguyen_Thanh_Trung"

void getline(std::istream& is, std::string& str);

int do_dai_str(string str);
static string ma_hoa_str_(const string& mat_khau){
    int len = do_dai_str(mat_khau);
    int key_len = do_dai_str(KEY_STR);
    string ma_hoa;
    for (int i = 0; i < len; i++) {
        unsigned char code = mat_khau[i] ^ KEY_STR[i % key_len];
        char buf[3];
        sprintf(buf, "%02X", code);
        ma_hoa += buf;
    }
    return ma_hoa;
}

#endif // MY_STRING_H
