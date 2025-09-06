#include"DESCRIPTION.H"

description::description()
{
    sumary="";
    vi_tri_luu_tru="";
    language="";
    page_number="";
    key_word="";
    don_gia="";
}
description::description(string sumary, string vi_tri_luu_tru, string language, string page_number, string key_word, string don_gia)
{
    this->sumary=sumary;
    this->vi_tri_luu_tru=vi_tri_luu_tru;
    this->language=language;
    this->page_number=page_number;
    this->key_word=key_word;
    this->don_gia=don_gia;
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
void description::set_page_number(string page_number)
{
    this->page_number=page_number;
}
void description::set_key_word(string key_word)
{
    this->key_word=key_word;
}
void description::set_don_gia(string don_gia)
{
    this->don_gia=don_gia;
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
string description::get_page_number()
{
    return page_number;
}
string description::get_key_word()
{
    return key_word;
}
string description::get_don_gia()
{
    return don_gia;
}
