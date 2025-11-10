#include "my_string.h"
#include "my_time.h"
#include "tree.h"
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

int is_chua_chuoi(const string& key, const string& full){
    for (int i = 0; i < do_dai_str(key); i++){
        if (key[i] != full[i]) return 0;
    }
    return 1;
}

int tim_kiem_co_chua(const string& key, const string& full) {
    int count = 0;
    int key_len = do_dai_str(key);
    int full_len = do_dai_str(full);
    BST_string key_words;
    BST_string full_words;
    for (int i = 0 ; i < key_len ; i++){
        string res = "";
        while (i < key_len && key[i] != ' '){
            char c = key[i];
            if (c >= 'A' && c <= 'Z'){
                c = c - 'A' + 'a';
            }
            res += c;
            i++;
        }
        if (res != "") {

            key_words.insert(res); 
        }
    }

    for (int i = 0 ; i < full_len ; i++){
        string res = "";
        while (i < full_len && full[i] != ' '){
            char c = full[i];
            if (c >= 'A' && c <= 'Z'){
                c = c - 'A' + 'a';
            }
            res += c;
            i++;
        }
        if (res != "") {
            full_words.insert(res);
        }
    }
    full_words.search_co_chua(key_words, full_words, count);
    return count;
}

int tim_kiem_chinh_xac(const string& key, const string& full) {
    int count = tim_kiem_co_chua(key, full);
    if (count == count_string(key) && count == count_string(full)) return 1;
    return 0;
}
int tim_kiem_bat_dau_bang(const string& key, const string& full) {
    int key_len = do_dai_str(key);
    int full_len = do_dai_str(full);
    if (key_len > full_len) return 0;
    for (int i = 0; i < key_len; i++) {
        char c1 = key[i];
        char c2 = full[i];
        if (c1 >= 'A' && c1 <= 'Z') {
            c1 = c1 - 'A' + 'a';
        }
        if (c2 >= 'A' && c2 <= 'Z') {
            c2 = c2 - 'A' + 'a';
        }
        if (c1 != c2) {
            return 0;
        }
    }
    return 1;
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
string to_string_(int x){
    if (x == 0) return "0";
    string res = "";
    bool negative = false;
    if (x < 0) {
        negative = true;
        x = -x;
    }
    while (x > 0) {
        res = char((x % 10) + '0') + res;
        x /= 10;
    }
    if (negative) res = '-' + res;
    return res;
}

string to_stringll_(long long &x){
    if (x == 0) return "0";
    string res = "";
    bool negative = false;
    if (x < 0) {
        negative = true;
        x = -x;
    }
    while (x > 0) {
        res = char((x % 10) + '0') + res;
        x /= 10;
    }
    if (negative) res = '-' + res;
    return res;
}

string to_string_(bool x){
    return x ? "1" : "0";
}
string to_string_(my_time t){
    return t.get_datetime();
}
int to_int(const string& s) {
    int res = 0;
    bool negative = false;
    int i = 0;
    if (s[i] == '-') {
        negative = true;
        i++;
    }
    for (; i < s.size(); i++) {
        res = res * 10 + (s[i] - '0');
    }
    if (negative) res = -res;
    return res;
}

int to_int(const bool& s){
    return s ? 1 : 0;
}

long long to_long_long(const string& s) {
    long long res = 0;
    bool negative = false;
    int i = 0;
    if (s[i] == '-') {
        negative = true;
        i++;
    }
    for (; i < s.size(); i++) {
        res = res * 10 + (s[i] - '0');
    }
    if (negative) res = -res;
    return res;
}
bool to_bool(const string& s){
    return s == "1" || s == "true" || s == "True";
}
bool to_bool(const int& s){
    return s != 0;
}

string toFixedString(int index, int longs) {
    string result = "";
    int temp = index;
    if (temp == 0) {
        result = "0";
    } else {
        while (temp > 0) {
            char c = char('0' + (temp % 10));
            result = c + result;
            temp /= 10;
        }
    }
    while ((int)result.length() < longs) {
        result = "0" + result;
    }
    if ((int)result.length() > longs) {
        result = result.substr(result.length() - longs);
    }
    return result;
}
int count_string(const string &s){ // dem so tu trong 1 xau
    int count = 0;
    bool inWord = false;
    for (char c : s){
        if (c != ' ' && c != '\t' && c != '\n') { 
            if (!inWord) { 
                count++;
                inWord = true;
            }
        }
        else inWord = false;
    }

    return count;
}
string lay_n_chu_dau(const string& s, size_t n) {
    string result = "";
    for (size_t i = 0; i < n && i < s.size(); i++) {
        result += s[i];
    }
    return result;
}
