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


// ship plan errors
#define ERROR_STRING_FLOOR_OVERFLOW    "ship plan: a position has an equal number of floors, or more, than the number of floors provided in the first line"  // 0
#define ERROR_STRING_XY_EXCEEDED       "ship plan: a given position exceeds the X/Y ship limits" // 1
#define ERROR_STRING_BAD_FORMAT        "ship plan: bad line format after first line or duplicate x,y appearance with same data" // 2
#define ERROR_STRING_BAD_PLAN_FILE     "ship plan: travel error - bad first line or file cannot be read altogether"  // 3
#define ERROR_STRING_XY_DUPLICATE      "ship plan: travel error - duplicate x,y appearance with different data" // 4
// port file errors //
#define ERROR_STRING_DUPLICATE_PORT    "travel route: a port appears twice or more consecutively" // 5
#define ERROR_STRING_BAD_PORT          "travel route: bad port symbol format" // 6
#define ERROR_STRING_BAD_ROUTE_FILE    "travel route: travel error - empty file or file cannot be read altogether"  // 7
#define ERROR_STRING_ONE_PORT          "travel route: travel error - file with only a single valid port"  // 8
// container errors //
#define ERROR_STRING_DUPLICATE_PORT_ID "containers at port: duplicate ID on port" // 10
#define ERROR_STRING_ID_ON_SHIP        "containers at port: ID already on ship" // 11
#define ERROR_STRING_BAD_WEIGHT        "containers at port: bad line format, missing or bad weight" // 12
#define ERROR_STRING_BAD_CARGO_PORT    "containers at port: bad line format, missing or bad port dest" // 13
#define ERROR_STRING_CANT_READ_ID      "containers at port: bad line format, ID cannot be read" // 14
#define ERROR_STRING_BAD_ID_FORMAT     "containers at port: illegal ID check ISO 6346" // 15
#define ERROR_STRING_BAD_CARGO_FILE    "containers at port: file cannot be read altogether" // 16
#define ERROR_STRING_BAD_LAST_PORT     "containers at port: last port has waiting containers" // 17
#define ERROR_STRING_TOO_MUCH_CARGO    "containers at port: total containers amount exceeds ship capacity" // 18

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

inline void errorVar(int& e, int code){ e |= (int)std::pow(2, code);}
