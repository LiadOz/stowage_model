#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>
#include <cmath>

#define ERROR_FLOOR_OVERFLOW    0
#define ERROR_XY_EXCEEDED       1
#define ERROR_BAD_FORMAT        2
#define ERROR_BAD_PLAN_FILE     3
#define ERROR_XY_DUPLICATE      4
#define ERROR_DUPLICATE_PORT    5
#define ERROR_BAD_PORT          6
#define ERROR_BAD_FILE          7
#define ERROR_ONE_PORT          8

using std::string;
class Error : public std::runtime_error{
private:
    int errorCode = 0;
public:
    Error(const string& message, int code): runtime_error(message), errorCode(code){}
    int GetError(){ return errorCode;}
    virtual ~Error (){}
};

class FatalError: public Error {
public:
    FatalError(const string& m, int code): Error(m,code){};
    virtual ~FatalError(){}
};
class NonFatalError: public Error {
public:
    NonFatalError(const string& m, int code): Error(m,code){};
    virtual ~NonFatalError(){}
};

inline void errorVar(int& e, int code){ e |= (int)std::pow(2, code);}

#endif /* EXCEPTIONS_H */
