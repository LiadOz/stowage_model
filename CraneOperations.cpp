#include "CraneOperations.h"
#include <iostream>
#include <stdexcept>

using std::runtime_error;
using std::stringstream;
using std::stoi;

Operations CraneOperation::GetOperationType(const string& opStr)
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

LoadCraneOperation::LoadCraneOperation(const vector<string>& params) {

	if (params.size() != CRANE_OPERATION_LOAD_NUM_OF_PARAM)
	{
		throw runtime_error("different amount of params passed");
	}

	try
	{
		operation = Operations::load;
		containerID = params[1];
		height = stoi(params[2]);
		row = stoi(params[3]);
		col = stoi(params[4]);
	}
	catch (const std::exception & error)
	{
		throw error;
	}
}

void LoadCraneOperation::DoOperation(Ship* ship, Port& port) {
	try
	{
		Container container = port.RemoveContainer(this->containerID);
		ship->InsertContainer(row, col, container);
	}
	catch (const std::exception & error)
	{
		throw error;
	}
}

UnloadCraneOperation::UnloadCraneOperation(const vector<string>& params) {
	if (params.size() != CRANE_OPERATION_UNLOAD_NUM_OF_PARAM)
	{
		throw runtime_error("different amount of params passed");
	}

	try
	{
		operation = Operations::unload;
		containerID = params[1];
		height = stoi(params[2]);
		row = stoi(params[3]);
		col = stoi(params[4]);
	}
	catch (const std::exception & error)
	{
		throw error;
	}
}

void UnloadCraneOperation::DoOperation(Ship* ship, Port& port) {
	try
	{
		Container container = ship->RemoveContainer(row, col);
		bool addedContainerToPort = port.AddContainer(container);
		if (!addedContainerToPort)
		{
			throw runtime_error("container already in port");
		}
		if (container.GetDestination() == port.getPortCode())
		{
			ship->UnloadedCargoAtCorrectPort();
		}
	}
	catch (const std::exception & error)
	{
		throw error;
	}
}

MoveCraneOperation::MoveCraneOperation(const vector<string>& params) {

	if (params.size() != CRANE_OPERATION_MOVE_NUM_OF_PARAM)
	{
		throw runtime_error("different amount of params passed");
	}

	try
	{
		operation = Operations::move;
		containerID = params[1];
		heightFrom = stoi(params[2]);
		rowFrom = stoi(params[3]);
		colFrom = stoi(params[4]);
		heightTo = stoi(params[5]);
		rowTo = stoi(params[6]);
		colTo = stoi(params[7]);
	}
	catch (const std::exception & error)
	{
		throw error;
	}
}

void MoveCraneOperation::DoOperation(Ship* ship, Port& port) {
	try
	{
        (void)port;
		ship->MoveContainer(rowFrom, colFrom, rowTo, colTo);
	}
	catch (const std::exception& error)
	{
		throw error;
	}
}

RejectCraneOperation::RejectCraneOperation(const vector<string>& params) {
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
	//TODO: shouldn't be in ship class (change in exec2), and add GetContainer function in port
	try
	{
		Container container = port.RemoveContainer(containerID);
		ship->RejectContainer(container);
		port.AddContainer(container);

	}
	catch (const std::exception& error)
	{
		throw error;
	}
}
