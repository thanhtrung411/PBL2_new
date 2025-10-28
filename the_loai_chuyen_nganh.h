#ifndef THE_LOAI_CHUYEN_NGANH_H
#define THE_LOAI_CHUYEN_NGANH_H
#include <iostream>
using namespace std;
class The_loai{
private:
    int ID;
    string name;
public:
    The_loai();
    The_loai(int ID, string name);
    ~The_loai();
    void set_id(int ID);
    void set_name(string name);

    int get_id() const;
    string get_name() const;
};
class Chuyen_nganh{
private:
    int ID;
    string name;
public:
    Chuyen_nganh();
    Chuyen_nganh(int ID, string name);
    ~Chuyen_nganh();
    void set_id(int ID);
    void set_name(string name);

    int get_id() const;
    string get_name() const;
};

#endif // THE_LOAI_CHUYEN_NGANH_H
