#include "CraneOperations.h"

Operations CraneOperation::GetOperationType(string opStr)
{
	if (opStr == OPERATION_LOAD)
	{
		return Operations::load;
	}
	else if (opStr == OPERATION_UNLOAD)
	{
		return Operations::unload;
	}
	else if (opStr == OPERATION_MOVE)
	{
		return Operations::move;
	}
	else if (opStr == OPERATION_REJECT)
	{
		return Operations::reject;
	}
	else {
		return Operations::undefined;
	}
}

LoadCraneOperation::LoadCraneOperation(int rowIndex, int colIndex, int heightValue) {
	operation = Operations::load;
	row = rowIndex;
	col = colIndex;
	height = heightValue;
}

void LoadCraneOperation::DoOperation() {
	//TODO: implement
}

UnloadCraneOperation::UnloadCraneOperation(int rowIndex, int colIndex, int heightValue) {
	operation = Operations::unload;
	row = rowIndex;
	col = colIndex;
	height = heightValue;
}

void UnloadCraneOperation::DoOperation() {
	//TODO: implement
}

MoveCraneOperation::MoveCraneOperation(int fromRow, int fromCol, int fromHeight, int toRow, int toCol, int toHeight) {
	operation = Operations::move;
	rowFrom = fromRow;
	colFrom = fromCol;
	heightFrom = fromHeight;
	rowTo = toRow;
	colTo = toCol;
	heightTo = toHeight;
}

void MoveCraneOperation::DoOperation() {
	//TODO: implement
}

RejectCraneOperation::RejectCraneOperation(string containerIDStr) {
	operation = Operations::reject;
	containerID = containerIDStr;
}

void RejectCraneOperation::DoOperation() {
	//TODO: implement
}