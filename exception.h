#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class AppException : public exception {
private:
    string title;
    string message;
public:
    AppException(const string& t, const string& msg)
        : title(t), message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

    const string& getTitle() const noexcept {
        return title;
    }
};

#endif // EXCEPTION_H
