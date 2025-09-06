#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <iostream>

using namespace std;
class description{
    private:
        string sumary;
        string vi_tri_luu_tru;
        string language;
        string page_number;
        string key_word;
        string don_gia;
    public:
        description();
        description(string sumary, string vi_tri_luu_tru, string language, string page_number, string key_word, string don_gia);
        ~description();
        void set_sumary(string sumary);
        void set_vi_tri_luu_tru(string vi_tri_luu_tru);
        void set_language(string language);
        void set_page_number(string page_number);
        void set_key_word(string key_word);
        void set_don_gia(string don_gia);
        string get_sumary();
        string get_vi_tri_luu_tru();
        string get_language();
        string get_page_number();
        string get_key_word();
        string get_don_gia();
};








#endif 