#include "my_string.h"
#include "my_time.h"
#include "tree.h"
#include <locale>
#include <codecvt>
#include <algorithm>
#include <cctype>
void getline(std::istream& is, std::string& str) {
    std::getline(is, str);
    if (!str.empty() && str.back() == '\r') {
        str.pop_back();
    }
}
int do_dai_str(string str) {
    return str.size();
}

int is_chua_chuoi(const string& key, const string& full){
    for (int i = 0; i < do_dai_str(key); i++){
        if (key[i] != full[i]) return 0;
    }
    return 1;
}

int tim_kiem_co_chua(const string& key, const string& full) {
    string key_lower = xoa_dau_lower(key);
    string full_lower = xoa_dau_lower(full);
    int count = 0;
    int key_len = do_dai_str(key_lower);
    int full_len = do_dai_str(full_lower);

    BST_string key_word;
    BST_string full_word;

    for (int i = 0 ; i < key_len; i++){
        string temp = "";
        while (i < key_len && key_lower[i] != ' '){
            temp += key_lower[i];
            i++;
        }
        if (temp != ""){
            key_word.insert(temp);
        }
    }

    for (int i = 0 ; i < full_len; i++){
        string temp = "";
        while (i < full_len && full_lower[i] != ' '){
            temp += full_lower[i];
            i++;
        }
        if (temp != ""){
            full_word.insert(temp);
        }
    }
    key_word.search_co_chua(key_word, full_word, count);
    return count;

}

int tim_kiem_chinh_xac(const string& key, const string& full) {
    string key_lower = xoa_dau_lower(key);
    string full_lower = xoa_dau_lower(full);
    if (key_lower == full_lower) {
        return 1;
    }
    return 0;
}
int tim_kiem_bat_dau_bang(const string& key, const string& full) {
    string key_lower = xoa_dau_lower(key);
    string full_lower = xoa_dau_lower(full);
    int key_len = do_dai_str(key_lower);
    int full_len = do_dai_str(full_lower);
    if (key_len == 0) return 0;
    if (full_len < key_len) return 0;
    if (full_lower.compare(0, key_len, key_lower) == 0) {
        return 1;
    }
    return 0;
}

wstring utf8_to_wstring(const string& str) {
    try{
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(str);
    }
    catch(...){
        return L"";
    }
}
string wstring_to_utf8(const wstring& wstr) {
    try{
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }
    catch(...){
        return "";
    }
}

string xoa_dau_lower(const string& s){
    wstring w_str = utf8_to_wstring(s);
    wstring w_kq = L"";
    std::locale loc;
    try {
        loc = std::locale("");
    } catch (const std::exception& e) {
        loc = std::locale::classic();
    }

    static const wstring VIET_NAM_CHARS =
        L"áàảãạăắằẳẵặâấầẩẫậéèẻẽẹêếềểễệíìỉĩịóòỏõọôốồổỗộơớờởỡợúùủũụưứừửữựýỳỷỹỵđ"
        L"ÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬÉÈẺẼẸÊẾỀỂỄỆÍÌỈĨỊÓÒỎÕỌÔỐỒỔỖỘƠỚỜỞỠỢÚÙỦŨỤƯỨỪỬỮỰÝỲỶỸỴĐ";
    static const wstring BASE_CHARS =
        L"aaaaaaaaaaaaaaaaaeeeeeeeeeeeiiiiiooooooooooooooooouuuuuuuuuuuyyyyyd"
        L"aaaaaaaaaaaaaaaaaeeeeeeeeeeeiiiiiooooooooooooooooouuuuuuuuuuuyyyyyd";
    for (wchar_t wc : w_str) {
        size_t pos = VIET_NAM_CHARS.find(wc);
        if (pos != wstring::npos) {
            w_kq += BASE_CHARS[pos];
        } else {
            w_kq += std::tolower(wc, loc);
        }
    }
    return wstring_to_utf8(w_kq);
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

string to_stringll_(const long long &x){
    if (x == 0) return "0";
    string res = "";
    bool negative = false;
    long long temp = x;
    if (temp < 0) {
        negative = true;
        temp = -temp;
    }
    while (temp > 0) {
        res = char((temp % 10) + '0') + res;
        temp /= 10;
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

string tien_te_vnd(long long amount) {
    string result = to_stringll_(amount);
    int len = result.length();
    if (len <= 3) return result;
    string formatted = "";
    int count = 0;
    for (int i = len - 1; i >= 0; i--) {
        formatted = result[i] + formatted;
        count++;
        if (count == 3 && i != 0) {
            formatted = '.' + formatted;
            count = 0;
        }
    }
    return formatted;
}

bool is_valid_email(const string& email) {
    const auto at_pos = email.find('@');
    if (at_pos == string::npos || at_pos == 0 || at_pos == email.size() - 1) {
        return false; 
    }

    const auto dot_pos = email.find('.', at_pos);
    if (dot_pos == string::npos || dot_pos == at_pos + 1 || dot_pos == email.size() - 1) {
        return false; 
    }

    for (char c : email) {
        if (!(isalnum(c) || c == '.' || c == '_' || c == '-' || c == '@')) {
            return false; 
        }
    }

    return true; 
}