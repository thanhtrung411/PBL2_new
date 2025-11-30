#ifndef HISTORY_RECORD_H
#define HISTORY_RECORD_H
#include "my_time.h"
#include "my_string.h"
#include <iostream>
using namespace std;

enum ActionType{
    LOGIN,          // Đăng nhập
    REGISTER,       // Đăng ký
    RESET_PASSWORD, // Đặt lại mật khẩu
    VIEW_BOOK,      // Xem một sách
    DOWNLOAD_BOOK,  // Tải một sách
    READ_ONLINE,    // Đọc online
    RESERVE_BOOK,   // Đặt sách
    BORROW_BOOK,    // Mượn sách
    CONFIRM_BOOK,   // Xác nhận mượn
    RETURN_BOOK,    // Trả sách
    RETURN_OVERDUE, // Trả quá hạn
    UNKNOWN
};

class history_record
{
public:
    my_time date_action;
    string user_name;
    ActionType action_type;
    long long book_id;
    string ghi_chu;
    history_record() : date_action(), user_name(""), action_type(UNKNOWN), book_id(0), ghi_chu("") {}
    history_record(my_time date, const string& user, ActionType action, long long book, const string& note)
        : date_action(date), user_name(user), action_type(action), book_id(book), ghi_chu(note) {};
};

#endif // HISTORY_RECORD_H
