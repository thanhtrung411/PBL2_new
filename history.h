#ifndef HISTORY_H
#define HISTORY_H
#include <fstream>
#include <iostream>
#include "tree.h"
#include "my_time.h"
class history
{
private:
    BST_History record;
    string filename = "data/history.csv";
    string action_to_string(ActionType action);
    ActionType string_to_action(const string& action_str);
public:
    history();
    void log_action(const string& user_name, ActionType action_type, long long book_id, const string& ghi_chu);
    void save_to_file(const history_record& data);
    void load_from_file();
};

#endif // HISTORY_H
