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