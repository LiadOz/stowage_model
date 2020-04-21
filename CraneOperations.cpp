#include "CraneOperations.h"
#include <iostream>
#include <stdexcept>

using std::runtime_error;
using std::stringstream;
using std::stoi;

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

LoadCraneOperation::LoadCraneOperation(vector<string>& params) {

	if (params.size() != CRANE_OPERATION_LOAD_NUM_OF_PARAM)
	{
		throw runtime_error("different amount of params passed");
	}

	try
	{
		operation = Operations::load;
		containerID = params[1];
		row = stoi(params[2]);
		col = stoi(params[3]);
		height = stoi(params[4]);
	}
	catch (const std::exception & error)
	{
		throw error;
	}
}

void LoadCraneOperation::DoOperation(Ship* ship, Port& port) {
	try
	{

	}
	catch (const std::exception& error)
	{

	}
}

UnloadCraneOperation::UnloadCraneOperation(vector<string>& params) {
	if (params.size() != CRANE_OPERATION_UNLOAD_NUM_OF_PARAM)
	{
		throw runtime_error("different amount of params passed");
	}

	try
	{
		operation = Operations::unload;
		containerID = params[1];
		row = stoi(params[2]);
		col = stoi(params[3]);
		height = stoi(params[4]);
	}
	catch (const std::exception & error)
	{
		throw error;
	}
}

void UnloadCraneOperation::DoOperation(Ship* ship, Port& port) {
	//TODO: implement
}

MoveCraneOperation::MoveCraneOperation(vector<string>& params) {

	if (params.size() != CRANE_OPERATION_MOVE_NUM_OF_PARAM)
	{
		throw runtime_error("different amount of params passed");
	}

	try
	{
		operation = Operations::move;
		containerID = params[1];
		rowFrom = stoi(params[2]);
		colFrom = stoi(params[3]);
		heightFrom = stoi(params[4]);
		rowTo = stoi(params[5]);
		colTo = stoi(params[6]);
		heightTo = stoi(params[7]);
	}
	catch (const std::exception & error)
	{
		throw error;
	}
}

void MoveCraneOperation::DoOperation(Ship* ship, Port& port) {
	//TODO: implement
}

RejectCraneOperation::RejectCraneOperation(vector<string>& params) {
	if (params.size() != CRANE_OPERATION_REJECT_NUM_OF_PARAM)
	{
		throw runtime_error("different amount of params passed");
	}

	try
	{
		operation = Operations::reject;
		containerID = params[1];
	}
	catch (const std::exception & error)
	{
		throw error;
	}
}

void RejectCraneOperation::DoOperation(Ship* ship, Port& port) {
	//TODO: implement
}