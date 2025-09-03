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