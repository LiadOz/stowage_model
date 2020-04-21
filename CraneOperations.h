#pragma once

#define OPERATION_LOAD "<L>"
#define OPERATION_UNLOAD "<U>"
#define OPERATION_MOVE "<M>"
#define OPERATION_REJECT "<R>"

#include <string>

using std::string;

enum class Operations { undefined, load, unload, move, reject };

class CraneOperation {
protected:
	Operations operation;
	string containerID;
public:
	void DoOperation();
	static Operations GetOperationType(string str);
	CraneOperation() { operation = Operations::undefined; containerID = ""; };
};

class LoadCraneOperation : public CraneOperation {
private:
	int row;
	int col;
	int height;
public:
	LoadCraneOperation(int rowIndex, int colIndex, int heightValue);
	virtual void DoOperation();
};

class UnloadCraneOperation : public CraneOperation {
private:
	int row;
	int col;
	int height;
public:
	UnloadCraneOperation(int rowIndex, int colIndex, int heightValue);
	virtual void DoOperation();
};

class MoveCraneOperation : public CraneOperation {
private:
	int rowFrom;
	int colFrom;
	int heightFrom;
	int rowTo;
	int colTo;
	int heightTo;
public:
	MoveCraneOperation(int fromRow, int fromCol, int fromHeight, int toRow, int toCol, int toHeight);
	virtual void DoOperation();
};

class RejectCraneOperation : public CraneOperation {
private:
public:
	RejectCraneOperation(string containerID);
	virtual void DoOperation();
};