#pragma once

#define OPERATION_LOAD "<L>"
#define OPERATION_UNLOAD "<U>"
#define OPERATION_MOVE "<M>"
#define OPERATION_REJECT "<R>"

#define CRANE_OPERATION_LOAD_NUM_OF_PARAM 5
#define CRANE_OPERATION_UNLOAD_NUM_OF_PARAM 5
#define CRANE_OPERATION_MOVE_NUM_OF_PARAM 8
#define CRANE_OPERATION_REJECT_NUM_OF_PARAM 2

#include <vector>
#include <string>
#include "ship.h"
#include "port.h"

using std::vector;
using std::string;

enum class Operations { undefined, load, unload, move, reject };

//base class, should not be initiated
class CraneOperation {
protected:
	Operations operation;
	string containerID;
public:
	virtual void DoOperation(Ship* ship, Port& port) = 0;
	static Operations GetOperationType(const string& str);
	CraneOperation() { operation = Operations::undefined; containerID = ""; };
	virtual ~CraneOperation() {};
	Operations GetOperation() { return operation; }
};

//the operation to load a cargo from the port to the ship
class LoadCraneOperation : public CraneOperation {
private:
	int row;
	int col;
	int height;
public:
	LoadCraneOperation(vector<string>& params);
	virtual void DoOperation(Ship* ship, Port& port);
	virtual ~LoadCraneOperation() {};
};

//the operation to unload a cargo from the ship to the port
class UnloadCraneOperation : public CraneOperation {
private:
	int row;
	int col;
	int height;
public:
	UnloadCraneOperation(vector<string>& params);
	virtual void DoOperation(Ship* ship, Port& port);
	virtual ~UnloadCraneOperation() {};
};

//the operation to move a cargo inside the ship
class MoveCraneOperation : public CraneOperation {
private:
	int rowFrom;
	int colFrom;
	int heightFrom;
	int rowTo;
	int colTo;
	int heightTo;
public:
	MoveCraneOperation(vector<string>& params);
	virtual void DoOperation(Ship* ship, Port& port);
	virtual ~MoveCraneOperation() {};
};

//the operation to reject a cargo from the port
class RejectCraneOperation : public CraneOperation {
private:
public:
	RejectCraneOperation(vector<string>& params);
	virtual void DoOperation(Ship* ship, Port& port);
	virtual ~RejectCraneOperation() {};
};
