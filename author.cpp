#include "author.h"
#include <iostream>
using namespace std;

Author::Author() : ID(0), name(""), biography("") {}
Author::Author(int ID, string name, string biography) {
    this->ID = ID;
    this->name = name;
    this->biography = biography;
}
Author::~Author() {}
void Author::set_ID(int ID) {
    this->ID = ID;
}
int Author::get_ID() const {
    return ID;
}
void Author::set_name(string name) {
    this->name = name;
}
string Author::get_name() const {
    return name;
}
void Author::set_biography(string biography) {
    this->biography = biography;
}
string Author::get_biography() const {
    return biography;
}
