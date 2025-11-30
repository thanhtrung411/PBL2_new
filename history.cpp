#include "history.h"
#include "history_record.h"
#include "tree.h"
#include "my_file.h"
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

history::history() {}

string history::action_to_string(ActionType action) {
    switch (action) {
        case LOGIN: return "LOGIN";
        case REGISTER: return "REGISTER";
        case RESET_PASSWORD: return "RESET_PASSWORD";
        case VIEW_BOOK: return "VIEW_BOOK";
        case DOWNLOAD_BOOK: return "DOWNLOAD_BOOK";
        case READ_ONLINE: return "READ_ONLINE";
        case RESERVE_BOOK: return "RESERVE_BOOK";
        case BORROW_BOOK: return "BORROW_BOOK";
        case CONFIRM_BOOK: return "CONFIRM_BOOK";
        case RETURN_BOOK: return "RETURN_BOOK";
        case RETURN_OVERDUE: return "RETURN_OVERDUE";
        default: return "UNKNOWN";
    }
}

ActionType history::string_to_action(const string& action_str) {
    if (action_str == "LOGIN") return LOGIN;
    if (action_str == "REGISTER") return REGISTER;
    if (action_str == "RESET_PASSWORD") return RESET_PASSWORD;
    if (action_str == "VIEW_BOOK") return VIEW_BOOK;
    if (action_str == "DOWNLOAD_BOOK") return DOWNLOAD_BOOK;
    if (action_str == "READ_ONLINE") return READ_ONLINE;
    if (action_str == "RESERVE_BOOK") return RESERVE_BOOK;
    if (action_str == "BORROW_BOOK") return BORROW_BOOK;
    if (action_str == "CONFIRM_BOOK") return CONFIRM_BOOK;
    if (action_str == "RETURN_BOOK") return RETURN_BOOK;
    if (action_str == "RETURN_OVERDUE") return RETURN_OVERDUE;
    return UNKNOWN;
}

void history::log_action(const string& user_name, ActionType action_type, long long book_id, const string& ghi_chu) {
    my_time date = my_time::now();
    history_record record_entry(date, user_name, action_type, book_id, ghi_chu);
    save_to_file(record_entry);
}

void history::save_to_file(const history_record& data) {
    QString filepath =  getDataFilePath(filename);
    ofstream file(filepath.toStdString(), ios::app);
    if (file.is_open()) {
        file << data.date_action.get_datetime() << ","
             << data.user_name << ","
             << action_to_string(data.action_type) << ","
             << data.book_id << ","
             << data.ghi_chu << "\n";
        file.close();
    }
}

void history::load_from_file() {
    QString filepath =  getDataFilePath(filename);
    ifstream file(filepath.toStdString());
    if (file.is_open()) {
        string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            string date_str, user_name, action_str, book_id_str, ghi_chu;
            std::getline(ss, date_str, ',');
            std::getline(ss, user_name, ',');
            std::getline(ss, action_str, ',');
            std::getline(ss, book_id_str, ',');
            std::getline(ss, ghi_chu, ',');
            getline(ss, ghi_chu, ',');

            my_time date;
            date.set_time_datetime(date_str);
            ActionType action = string_to_action(action_str);
            long long book_id = stoll(book_id_str);

            history_record record_entry(date, user_name, action, book_id, ghi_chu);
            record.insert(record_entry);
        }
        file.close();
    }
}

void history::luot_xem_muon_tai_thang(int month, int year, int &so_luot_xem, int &so_luot_muon, int &so_luot_tai){
    so_luot_xem = 0;
    so_luot_muon = 0;
    so_luot_tai = 0;
    record.traverse_ascending([&](history_record& hr) {
        my_time date = hr.date_action;
        if (date.get_year() == year && date.get_month() == month) {
            if (hr.action_type == VIEW_BOOK) {
                so_luot_xem++;
            } else if (hr.action_type == BORROW_BOOK) {
                so_luot_muon++;
            } else if (hr.action_type == DOWNLOAD_BOOK) {
                so_luot_tai++;
            }
        }
    });
}