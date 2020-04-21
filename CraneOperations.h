#pragma once

#include <string>


#define OPERATION_LOAD "<L>"
#define OPERATION_UNLOAD "<U>"
#define OPERATION_MOVE "<M>"
#define OPERATION_REJECT "<R>"

enum class Operations {undefined, load, unload, move, reject };

class CraneOperations {
private:
	Operations operation;
	int row;
	int col;
	int height;
public:
	//CraneOperations(string opStr);
};