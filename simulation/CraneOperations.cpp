#include "CraneOperations.h"

#include <iostream>
#include <stdexcept>

using std::runtime_error;
using std::stoi;
using std::stringstream;

#define LOAD_UNLOAD_COST 5;
#define MOVE_COST 3;

Operations CraneOperation::getOperationType(const string& opStr) {
    if (opStr == OPERATION_LOAD) {
        return Operations::load;
    } else if (opStr == OPERATION_UNLOAD) {
        return Operations::unload;
    } else if (opStr == OPERATION_MOVE) {
        return Operations::move;
    } else if (opStr == OPERATION_REJECT) {
        return Operations::reject;
    } else {
        return Operations::undefined;
    }
}

LoadCraneOperation::LoadCraneOperation(const vector<string>& params) {
    if (params.size() != CRANE_OPERATION_LOAD_NUM_OF_PARAM) {
        throw runtime_error("different amount of params passed");
    }

    try {
        operation = Operations::load;
        containerID = params[1];
        cost = LOAD_UNLOAD_COST;
        height = stoi(params[2]);
        row = stoi(params[3]);
        col = stoi(params[4]);
    } catch (const std::runtime_error& error) {
        throw std::runtime_error("Load constructor: " + string(error.what()));
    } catch (const std::exception& error) {
        throw error;
    }
}

void LoadCraneOperation::doOperation(Ship& ship, Port& port) {
    try {
        Container container = port.removeContainer(this->containerID);
        if (ship.idOnShip(container.getId())) {
            throw std::runtime_error("Id " + container.getId() + " already on ship");
        }
        ship.insertContainer(row, col, container);
    } catch (const std::runtime_error& error) {
        throw std::runtime_error("Load Operation: " + string(error.what()));
    } catch (const std::exception& error) {
        throw error;
    }
}

UnloadCraneOperation::UnloadCraneOperation(const vector<string>& params) {
    if (params.size() != CRANE_OPERATION_UNLOAD_NUM_OF_PARAM) {
        throw runtime_error("different amount of params passed");
    }

    try {
        operation = Operations::unload;
        containerID = params[1];
        cost = LOAD_UNLOAD_COST;
        height = stoi(params[2]);
        row = stoi(params[3]);
        col = stoi(params[4]);
    } catch (const std::runtime_error& error) {
        throw std::runtime_error("Unload constructor: " + string(error.what()));
    } catch (const std::exception& error) {
        throw error;
    }
}

void UnloadCraneOperation::doOperation(Ship& ship, Port& port) {
    try {
        Container container = ship.removeContainer(row, col);
        bool addedContainerToPort = port.addContainer(container);
        if (!addedContainerToPort) {
            throw runtime_error("container already in port");
        }
        if (container.getDestination() == port.getPortCode()) {
            ship.unloadedCargoAtCorrectPort();
        }
    } catch (const std::runtime_error& error) {
        throw std::runtime_error("Unload operation: " + string(error.what()));
    } catch (const std::exception& error) {
        throw error;
    }
}

MoveCraneOperation::MoveCraneOperation(const vector<string>& params) {
    if (params.size() != CRANE_OPERATION_MOVE_NUM_OF_PARAM) {
        throw runtime_error("different amount of params passed");
    }

    try {
        operation = Operations::move;
        containerID = params[1];
        cost = MOVE_COST;
        heightFrom = stoi(params[2]);
        rowFrom = stoi(params[3]);
        colFrom = stoi(params[4]);
        heightTo = stoi(params[5]);
        rowTo = stoi(params[6]);
        colTo = stoi(params[7]);
    } catch (const std::runtime_error& error) {
        throw std::runtime_error("Move constructor: " + string(error.what()));
    } catch (const std::exception& error) {
        throw error;
    }
}

void MoveCraneOperation::doOperation(Ship& ship, Port& port) {
    try {
        (void)port;
        ship.moveContainer(rowFrom, colFrom, rowTo, colTo);
    } catch (const std::runtime_error& error) {
        throw std::runtime_error("Move operation: " + string(error.what()));
    } catch (const std::exception& error) {
        throw error;
    }
}

RejectCraneOperation::RejectCraneOperation(const vector<string>& params) {
    if (params.size() != CRANE_OPERATION_REJECT_NUM_OF_PARAM) {
        throw runtime_error("different amount of params passed");
    }

    try {
        operation = Operations::reject;
        containerID = params[1];
    } catch (const std::runtime_error& error) {
        throw std::runtime_error("Reject constructor: " + string(error.what()));
    } catch (const std::exception& error) {
        throw error;
    }
}

void RejectCraneOperation::doOperation(Ship& ship, Port& port) {
    //TODO: shouldn't be in ship class (change in exec2), and add GetContainer function in port
    try {
        Container container = port.removeContainer(containerID);
        ship.rejectContainer(container);
        port.addContainer(container);

    } catch (const std::runtime_error& error) {
        throw std::runtime_error("Reject Operation: " + string(error.what()));
    } catch (const std::exception& error) {
        throw error;
    }
}
