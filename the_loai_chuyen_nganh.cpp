#include "the_loai_chuyen_nganh.h"
#include <iostream>
using namespace std;
The_loai::The_loai(){
    ID = 0;
    name = "";
}
The_loai::The_loai(int ID, string name){
    this->ID = ID;
    this->name = name;
}
The_loai::~The_loai(){}

void The_loai::set_id(int ID){
    this->ID = ID;
}
void The_loai::set_name(string name){
    this->name = name;
}
int The_loai::get_id() const{
    return ID;
}
string The_loai::get_name() const{
    return name;
}
Chuyen_nganh::Chuyen_nganh(){
    ID = 0;
    name = "";
}
Chuyen_nganh::Chuyen_nganh(int ID, string name){
    this->ID = ID;
    this->name = name;
}
Chuyen_nganh::~Chuyen_nganh(){}

void Chuyen_nganh::set_id(int ID){
    this->ID = ID;
}
void Chuyen_nganh::set_name(string name){
    this->name = name;
}
int Chuyen_nganh::get_id() const{
    return ID;
}
string Chuyen_nganh::get_name() const{
    return name;
}

