#ifndef HISTORY_H
#define HISTORY_H
#include <fstream>
#include <iostream>
#include "tree.h"
#include "my_time.h"
#include "global.h"
class history
{
private:
    string filename = "data/history.csv";
    string action_to_string(ActionType action);
    ActionType string_to_action(const string& action_str);
public:
    history();
    void log_action(const string& user_name, ActionType action_type, long long book_id, const string& ghi_chu);
    void save_to_file(const history_record& data);
    void luot_xem_muon_tai_thang(int month, int year, int &so_luot_xem, int &so_luot_muon, int &so_luot_tai);
    void load_from_file();
};

#endif // HISTORY_H
