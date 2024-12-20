/*#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class DatabaseException : public std::exception {
private:
    std::string message;
public:
    DatabaseException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class AuthenticationException : public DatabaseException {
public:
    AuthenticationException(const std::string& msg) : DatabaseException(msg) {}
};

class DataException : public DatabaseException {
public:
    DataException(const std::string& msg) : DatabaseException(msg) {}
};
#endif
*/
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QString>
#include <QtGlobal>
#include <type_traits>
#include <exception>
#include <string>

class DatabaseException : public std::exception {
private:
    std::string message;

public:
    DatabaseException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class AuthenticationException : public DatabaseException {
public:
    AuthenticationException(const std::string& msg) : DatabaseException(msg) {}
};

class DataException : public DatabaseException {
public:
    DataException(const std::string& msg) : DatabaseException(msg) {}
};

#endif
