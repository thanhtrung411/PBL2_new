#include "history.h"
#include "my_file.h"
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <QString>

using namespace std;

// ==========================================
// IMPLEMENTATION CLASS history_record
// ==========================================

history_record::history_record() 
    : date_action(), user_name(""), action_type(UNKNOWN), book_id(0), ghi_chu("") {}

history_record::history_record(my_time date, const string& user, ActionType action, long long book, const string& note)
    : date_action(date), user_name(user), action_type(action), book_id(book), ghi_chu(note) {}

// --- GETTERS ---
my_time history_record::get_date_action() const { return date_action; }
string history_record::get_user_name() const { return user_name; }
ActionType history_record::get_action_type() const { return action_type; }
long long history_record::get_book_id() const { return book_id; }
string history_record::get_ghi_chu() const { return ghi_chu; }
string history_record::get_action_type_string() const {
    switch (action_type) {
        case LOGIN: return "LOGIN";
        case REGISTER: return "REGISTER";
        case RESET_PASSWORD: return "RESET_PASSWORD";
        case VIEW_BOOK: return "VIEW_BOOK";
        case DOWNLOAD_BOOK: return "DOWNLOAD_BOOK";
        case READ_ONLINE: return "READ_ONLINE";
        case RESERVE_BOOK: return "RESERVE_BOOK";
        case BORROW_BOOK: return "BORROW_BOOK";
        case LIKE_BOOK: return "LIKE_BOOK";
        case DISLIKE_BOOK: return "DISLIKE_BOOK";
        case CONFIRM_BOOK: return "CONFIRM_BOOK";
        case RETURN_BOOK: return "RETURN_BOOK";
        case RETURN_OVERDUE: return "RETURN_OVERDUE";
        case REMOVE_BOOK: return "REMOVE_BOOK";
        case ADD_BOOK: return "ADD_BOOK";
        case UPDATE_BOOK: return "UPDATE_BOOK";
        case ADD_BOOK_COPY: return "ADD_BOOK_COPY";
        case REMOVE_BOOK_COPY: return "REMOVE_BOOK_COPY";
        case ADJ_BOOK: return "ADJ_BOOK";
        case ADJ_USER: return "ADJ_USER";
        case EXTEND_BORROW: return "EXTEND_BORROW";
        default: return "UNKNOWN";
    }
}

// --- SETTERS ---
void history_record::set_date_action(const my_time& date) { date_action = date; }
void history_record::set_user_name(const string& user) { user_name = user; }
void history_record::set_action_type(ActionType action) { action_type = action; }
void history_record::set_book_id(long long id) { book_id = id; }
void history_record::set_ghi_chu(const string& note) { ghi_chu = note; }
void history_record::set_action_type_string(const string& action_str) {
    if (action_str == "LOGIN") action_type = LOGIN;
    else if (action_str == "REGISTER") action_type = REGISTER;
    else if (action_str == "RESET_PASSWORD") action_type = RESET_PASSWORD;
    else if (action_str == "VIEW_BOOK") action_type = VIEW_BOOK;
    else if (action_str == "DOWNLOAD_BOOK") action_type = DOWNLOAD_BOOK;
    else if (action_str == "READ_ONLINE") action_type = READ_ONLINE;
    else if (action_str == "RESERVE_BOOK") action_type = RESERVE_BOOK;
    else if (action_str == "BORROW_BOOK") action_type = BORROW_BOOK;
    else if (action_str == "LIKE_BOOK") action_type = LIKE_BOOK;
    else if (action_str == "DISLIKE_BOOK") action_type = DISLIKE_BOOK;
    else if (action_str == "CONFIRM_BOOK") action_type = CONFIRM_BOOK;
    else if (action_str == "RETURN_BOOK") action_type = RETURN_BOOK;
    else if (action_str == "RETURN_OVERDUE") action_type = RETURN_OVERDUE;
    else if (action_str == "REMOVE_BOOK") action_type = REMOVE_BOOK;
    else if (action_str == "ADD_BOOK") action_type = ADD_BOOK;
    else if (action_str == "UPDATE_BOOK") action_type = UPDATE_BOOK;
    else if (action_str == "ADD_BOOK_COPY") action_type = ADD_BOOK_COPY;
    else if (action_str == "REMOVE_BOOK_COPY") action_type = REMOVE_BOOK_COPY;
    else if (action_str == "ADJ_BOOK") action_type = ADJ_BOOK;
    else if (action_str == "EXTEND_BORROW") action_type = EXTEND_BORROW;
    else if (action_str == "ADJ_USER") action_type = ADJ_USER;
    else action_type = UNKNOWN;
}

// ==========================================
// IMPLEMENTATION CLASS history
// ==========================================

// history::history() {
//     // load_from_file(); 
// }

// string history::get_filename() const { return filename; }
// void history::set_filename(const string& name) { filename = name; }

// string history::action_to_string(ActionType action) {
//     switch (action) {
//         case LOGIN: return "LOGIN";
//         case REGISTER: return "REGISTER";
//         case RESET_PASSWORD: return "RESET_PASSWORD";
//         case VIEW_BOOK: return "VIEW_BOOK";
//         case DOWNLOAD_BOOK: return "DOWNLOAD_BOOK";
//         case READ_ONLINE: return "READ_ONLINE";
//         case LIKE_BOOK: return "LIKE_BOOK";
//         case DISLIKE_BOOK: return "DISLIKE_BOOK";
//         case RESERVE_BOOK: return "RESERVE_BOOK";
//         case BORROW_BOOK: return "BORROW_BOOK";
//         case CONFIRM_BOOK: return "CONFIRM_BOOK";
//         case RETURN_BOOK: return "RETURN_BOOK";
//         case RETURN_OVERDUE: return "RETURN_OVERDUE";
//         default: return "UNKNOWN";
//     }
// }

// ActionType history::string_to_action(const string& action_str) {
//     if (action_str == "LOGIN") return LOGIN;
//     if (action_str == "REGISTER") return REGISTER;
//     if (action_str == "RESET_PASSWORD") return RESET_PASSWORD;
//     if (action_str == "VIEW_BOOK") return VIEW_BOOK;
//     if (action_str == "LIKE_BOOK") return LIKE_BOOK;
//     if (action_str == "DISLIKE_BOOK") return DISLIKE_BOOK;
//     if (action_str == "DOWNLOAD_BOOK") return DOWNLOAD_BOOK;
//     if (action_str == "READ_ONLINE") return READ_ONLINE;
//     if (action_str == "RESERVE_BOOK") return RESERVE_BOOK;
//     if (action_str == "BORROW_BOOK") return BORROW_BOOK;
//     if (action_str == "CONFIRM_BOOK") return CONFIRM_BOOK;
//     if (action_str == "RETURN_BOOK") return RETURN_BOOK;
//     if (action_str == "RETURN_OVERDUE") return RETURN_OVERDUE;
//     return UNKNOWN;
// }

// void history::log_action(const string& user_name, ActionType action_type, long long book_id, const string& ghi_chu) {
//     my_time date = my_time::now();
//     history_record record_entry(date, user_name, action_type, book_id, ghi_chu);
    
//     save_to_file(record_entry);
//     record.insert(record_entry);
// }

// void history::save_to_file(const history_record& data) {
//     QString filepath = getDataFilePath(filename); 
//     ofstream file(filepath.toStdString(), ios::app); 
    
//     if (file.is_open()) {
//         // Vì data là object history_record, giờ các biến là private
//         // nên phải dùng Getter để lấy dữ liệu ra ghi file
//         file << data.get_date_action().get_datetime() << ","
//              << data.get_user_name() << ","
//              << action_to_string(data.get_action_type()) << ","
//              << data.get_book_id() << ","
//              << data.get_ghi_chu() << "\n";
//         file.close();
//     }
// }

// void history::load_from_file() {
//     QString filepath = getDataFilePath(filename);
//     ifstream file(filepath.toStdString());
    
//     record.clear(); 

//     if (file.is_open()) {
//         string line;
//         while (std::getline(file, line)) {
//             std::stringstream ss(line);
//             string date_str, user_name, action_str, book_id_str, ghi_chu;
            
//             std::getline(ss, date_str, ',');
//             std::getline(ss, user_name, ',');
//             std::getline(ss, action_str, ',');
//             std::getline(ss, book_id_str, ',');
//             std::getline(ss, ghi_chu, ','); 
            
//             my_time date;
//             date.set_time_datetime(date_str); 
//             ActionType action = string_to_action(action_str);
//             long long book_id = 0;
//             try {
//                 if (!book_id_str.empty()) book_id = stoll(book_id_str);
//             } catch (...) { book_id = 0; }

//             // Constructor sẽ tự gán vào private member
//             history_record record_entry(date, user_name, action, book_id, ghi_chu);
//             record.insert(record_entry);
//         }
//         file.close();
//     }
// }

// void history::luot_xem_muon_tai_thang(int month, int year, int &so_luot_xem, int &so_luot_muon, int &so_luot_tai){
//     so_luot_xem = 0;
//     so_luot_muon = 0;
//     so_luot_tai = 0;
    
//     record.traverse_ascending([&](history_record& hr) {
//         // Dùng Getter thay vì truy cập trực tiếp
//         my_time date = hr.get_date_action();
//         ActionType act = hr.get_action_type();

//         if (date.get_year() == year && date.get_month() == month) {
//             if (act == VIEW_BOOK) {
//                 so_luot_xem++;
//             } else if (act == BORROW_BOOK) {
//                 so_luot_muon++;
//             } else if (act == DOWNLOAD_BOOK) {
//                 so_luot_tai++;
//             }
//         }
//     });
// }

// void history::loc_user(string user_name, BST_History &b){
//     b.clear();
//     record.traverse_ascending([&](history_record& hr) {
//         // Dùng Getter
//         if (hr.get_user_name() == user_name) {
//             b.insert(hr);
//         }
//     });
// }

// void history::load_from_file(string user_name_filter, BST_History &b){
//     QString filepath = getDataFilePath(filename);
//     ifstream file(filepath.toStdString());
    
//     b.clear();

//     if (file.is_open()) {
//         string line;
//         while (std::getline(file, line)) {
//             std::stringstream ss(line);
//             string date_str, user_name_file, action_str, book_id_str, ghi_chu;
            
//             std::getline(ss, date_str, ',');
//             std::getline(ss, user_name_file, ',');
//             std::getline(ss, action_str, ',');
//             std::getline(ss, book_id_str, ',');
//             std::getline(ss, ghi_chu, ',');
            
//             if (user_name_file != user_name_filter) {
//                 continue; 
//             }

//             my_time date;
//             date.set_time_datetime(date_str);
//             ActionType action = string_to_action(action_str);
//             long long book_id = 0;
//             try {
//                 if (!book_id_str.empty()) book_id = stoll(book_id_str);
//             } catch (...) { book_id = 0; }

//             history_record record_entry(date, user_name_file, action, book_id, ghi_chu);
//             b.insert(record_entry);
//         }
//         file.close();
//     }
// }