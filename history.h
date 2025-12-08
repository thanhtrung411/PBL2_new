#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <string>
#include <fstream>
#include "my_time.h"
//#include "global.h"

using namespace std;


enum ActionType{
    LOGIN, // đăng nhập
    REGISTER, // đăng ký
    RESET_PASSWORD, // đặt lại mật khẩu
    VIEW_BOOK,      // xem sách
    DOWNLOAD_BOOK,  // tải sách
    READ_ONLINE,    // đọc trực tuyến
    RESERVE_BOOK,   // đặt sách
    BORROW_BOOK,    // mượn sách
    EXTEND_BORROW,  // gia hạn mượn sách
    LIKE_BOOK,      // thích sách
    DISLIKE_BOOK,   // không thích sách
    CONFIRM_BOOK,   // xác nhận sách
    RETURN_BOOK,    // trả sách
    RETURN_OVERDUE, // trả sách quá hạn
    REMOVE_BOOK,    // xoá sách
    ADD_BOOK,       // thêm sách
    UPDATE_BOOK,    // cập nhật sách
    ADD_BOOK_COPY,  // thêm bản sao sách
    REMOVE_BOOK_COPY, // xoá bản sao sách
    ADJ_BOOK, // điều chỉnh sách
    ADJ_USER, // điều chỉnh thông tin
    UNKNOWN
};

class history_record
{
private:
    my_time date_action;
    string user_name;
    ActionType action_type;
    long long book_id;
    string ghi_chu;

public:
    history_record();
    history_record(my_time date, const string& user, ActionType action, long long book, const string& note);

    // --- GETTERS ---
    my_time get_date_action() const;
    string get_user_name() const;
    ActionType get_action_type() const;
    string get_action_type_string() const;
    long long get_book_id() const;
    string get_ghi_chu() const;

    // --- SETTERS ---
    void set_date_action(const my_time& date);
    void set_user_name(const string& user);
    void set_action_type(ActionType action);
    void set_action_type_string(const string& action_str);
    void set_book_id(long long id);
    void set_ghi_chu(const string& note);
};

#include "tree.h"

// Forward declaration if BST_History is not yet defined
// --- PHẦN ĐỊNH NGHĨA CLASS QUẢN LÝ ---

// class history
// {
// private:
//     string filename = "data/history.csv";
//     string action_to_string(ActionType action);
//     ActionType string_to_action(const string& action_str);

// public:
//     history();

//     // Get/Set cho filename (nếu cần đổi file log)
//     string get_filename() const;
//     void set_filename(const string& name);

//     void log_action(const string& user_name, ActionType action_type, long long book_id, const string& ghi_chu);
//     void save_to_file(const history_record& data);
//     void luot_xem_muon_tai_thang(int month, int year, int &so_luot_xem, int &so_luot_muon, int &so_luot_tai);
//     void loc_user(string user_name, BST_History &b);
    
//     void load_from_file();
//     void load_from_file(string user_name, BST_History &b);
// };

#endif // HISTORY_H