#include "my_string.h"
void getline(std::istream& is, std::string& str) {
    std::getline(is, str);
    if (!str.empty() && str.back() == '\r') {
        str.pop_back();
    }
}
int do_dai_str(string str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int tim_kiem_xau(string key, string full){
    int n = do_dai_str(key);
    int m = do_dai_str(full);
    int k = 0;//so chu tim thay trong key
    string temp = "";
    for (int i = 0 ; i <= n ; i++){
        if ((i < n) && (key[i]!=' ')){
            temp += key[i];
        }
        else if (!temp.empty()){
            string value = "";
            for (int j = 0 ; j < m ; j++){
                if ((j < m) && (full[j]!=' ')){
                    value += full[j];
                }
                else if (!value.empty()){
                    if (temp == value){
                        k++;
                        break;
                    }
                    value = "";
                }
            }
            temp = "";
        }
    }
    return k;
}

static inline void rtrim_inplace(string &s){
    while (!s.empty() && (s.back()==' '||s.back()=='\t'||s.back()=='\r')){
        s.pop_back();
    }
}
static inline void ltrim_inplace(string &s){
    int i = 0;
    while (i < s.size() && (s[i]==' '||s[i]=='\t')){
        i++;
    }
    if (i) s.erase(0, i);
}
static inline string trim_copy(string s){
    ltrim_inplace(s);
    rtrim_inplace(s);
    return s;
}

/*
static string my_substr(const string& s, int pos, int len) {
    string result;
    int n = s.size();
    if (pos < 0 || pos >= n || len <= 0) return result;
    for (int i = pos; i < n && i < pos + len; ++i) {
        result += s[i];
    }
    return result;
}
    */
