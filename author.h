#ifndef AUTHOR_H
#define AUTHOR_H
#include <iostream>
using namespace std;

class Author{
private:
    int ID;
    string name;
    string biography;
public:
    Author();
    Author(int ID, string name, string biography);
    ~Author();
    void set_ID(int ID);
    int get_ID() const;
    void set_name(string name);
    string get_name() const;
    void set_biography(string biography);
    string get_biography() const;
};


#endif // AUTHOR_H
