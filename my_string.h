#ifndef MY_STRING_H
#define MY_STRING_H
#include <iostream>
using namespace std;
#define KEY_STR "PBL2By-Do_Tran_Hoai_Nhi-Nguyen_Thanh_Trung"

void getline(std::istream& is, std::string& str);

int do_dai_str(string str);

static string my_substr(const string& s, int pos, int len){
    string result;
    int n = s.size();
    if (pos < 0 || pos >= n || len <= 0) return result;
    for (int i = pos; i < n && i < pos + len; ++i) {
        result += s[i];
    }
    return result;
}

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

static string giai_ma_str_(const string& ma_hoa) {
    int key_len = do_dai_str(KEY_STR);
    int len = do_dai_str(ma_hoa);
    string giai_ma;
    for (int i = 0; i < len; i += 2) {
        string code_hex = my_substr(ma_hoa, i, 2);
        unsigned int code;
        sscanf(code_hex.c_str(), "%02X", &code);
        char ch = static_cast<char>(code ^ KEY_STR[(i / 2) % key_len]);
        giai_ma += ch;
    }
    return giai_ma;
}
#endif // MY_STRING_H
