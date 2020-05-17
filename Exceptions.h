#pragma once 

#include <string>
#include <stdexcept>
#include <cmath>

// ship plan errors
#define ERROR_FLOOR_OVERFLOW    0
#define ERROR_XY_EXCEEDED       1
#define ERROR_BAD_FORMAT        2
#define ERROR_BAD_PLAN_FILE     3 // critical
#define ERROR_XY_DUPLICATE      4 // critical
// port file errors
#define ERROR_DUPLICATE_PORT    5
#define ERROR_BAD_PORT          6
#define ERROR_BAD_ROUTE_FILE    7 // critical
#define ERROR_ONE_PORT          8 // critical
// container errors
#define ERROR_DUPLICATE_PORT_ID 10
#define ERROR_ID_ON_SHIP        11
#define ERROR_BAD_WEIGHT        12
#define ERROR_BAD_CARGO_PORT    13
#define ERROR_CANT_READ_ID      14
#define ERROR_BAD_ID_FORMAT     15
#define ERROR_BAD_CARGO_FILE    16
#define ERROR_BAD_LAST_PORT     17
#define ERROR_TOO_MUCH_CARGO    18

using std::string;

class Error : public std::runtime_error {
private:
	int errorCode = 0;
public:
	Error(const string& message, int code) : runtime_error(message), errorCode(code) {}
	Error(const string& message) : runtime_error(message) {}
	int getError() { return errorCode; }
	virtual ~Error() {}
};

class FatalError : public Error {
public:
	FatalError(const string& m, int code) : Error(m, code) {};
	FatalError(const string& m) : Error(m) {};
	virtual ~FatalError() {}
};
class NonFatalError : public Error {
public:
	NonFatalError(const string& m, int code) : Error(m, code) {};
	virtual ~NonFatalError() {}
};

inline void errorVar(int& e, int code) { e |= (int)std::pow(2, code); }
