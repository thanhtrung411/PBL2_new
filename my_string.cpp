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

int tim_kiem_xau(const string& key, const string& full) {
    int n = do_dai_str(key);
    int m = do_dai_str(full);
    int k = 0;                 // số từ của key tìm thấy trong full
    string temp = "";

    for (int i = 0; i < n; i++) {
        if (key[i] != ' ') {
            temp += key[i];
        }
        // Khi gặp khoảng trắng KẾT THÚC từ, hoặc là ký tự cuối chuỗi
        if ((key[i] == ' ' && !temp.empty()) || (i == n - 1 && !temp.empty())) {
            // Tìm temp trong full
            int j = 0;             // đặt về 0 để tìm ở bất kỳ đâu trong full
            string value = "";
            for (; j < m; j++) {
                if (full[j] != ' ') {
                    value += full[j];
                }
                if ((full[j] == ' ' && !value.empty()) || (j == m - 1 && !value.empty())) {
                    if (temp == value) {
                        k++;       // tìm thấy 1 lần cho từ temp
                        break;     // dừng tìm cho từ này
                    }
                    value.clear(); // chuẩn bị đọc từ kế tiếp trong full
                }
            }
            temp.clear();          // chuẩn bị đọc từ kế tiếp trong key
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