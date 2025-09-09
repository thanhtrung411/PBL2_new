#include"DESCRIPTION.H"

description::description()
{
    sumary="";
    vi_tri_luu_tru="";
    language="";
    key_word="";
}

description::description(string sumary, string vi_tri_luu_tru, string language, string key_word)
{
    this->sumary=sumary;
    this->vi_tri_luu_tru=vi_tri_luu_tru;
    this->language=language;
    this->key_word=key_word;
}


description::~description()
{
}
void description::set_sumary(string sumary)
{
    this->sumary=sumary;
}
void description::set_vi_tri_luu_tru(string vi_tri_luu_tru)
{
    this->vi_tri_luu_tru=vi_tri_luu_tru;
}
void description::set_language(string language)
{
    this->language=language;
}

void description::set_key_word(string key_word)
{
    this->key_word=key_word;
}

string description::get_sumary()
{
    return sumary;
}
string description::get_vi_tri_luu_tru()
{
    return vi_tri_luu_tru;
}
string description::get_language()
{
    return language;
}

string description::get_key_word()
{
    return key_word;
}

