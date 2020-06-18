#pragma once

#include <string>
#include <vector>

#include "../common/Ship.h"
#include "Port.h"

#define OPERATION_LOAD "L"
#define OPERATION_UNLOAD "U"
#define OPERATION_MOVE "M"
#define OPERATION_REJECT "R"

#define CRANE_OPERATION_LOAD_NUM_OF_PARAM 5
#define CRANE_OPERATION_UNLOAD_NUM_OF_PARAM 5
#define CRANE_OPERATION_MOVE_NUM_OF_PARAM 8
#define CRANE_OPERATION_REJECT_NUM_OF_PARAM 2

#define LOAD_UNLOAD_COST 5;
#define MOVE_COST 3;

using std::string;
using std::vector;

enum class Operations { undefined,
                        load,
                        unload,
                        move,
                        reject };

//base class, should not be initiated
class CraneOperation {
   protected:
    Operations operation;
    string containerID;
    int cost;

   public:
    virtual void doOperation(Ship& ship, Port& port) = 0;
    static Operations getOperationType(const string& str);
    CraneOperation() {
        operation = Operations::undefined;
        containerID = "";
        cost = 0;
    };
    virtual ~CraneOperation(){};
    Operations getOperation() { return operation; }
    int getCost() { return cost; }
    string getcontainerID() { return containerID; }
};

//the operation to load a cargo from the port to the ship
class LoadCraneOperation : public CraneOperation {
   private:
    int row;
    int col;
    int height;

   public:
    LoadCraneOperation(const vector<string>& params);
    virtual void doOperation(Ship& ship, Port& port);
    virtual ~LoadCraneOperation(){};
};

//the operation to unload a cargo from the ship to the port
class UnloadCraneOperation : public CraneOperation {
   private:
    int row;
    int col;
    int height;

   public:
    UnloadCraneOperation(const vector<string>& params);
    virtual void doOperation(Ship& ship, Port& port);
    virtual ~UnloadCraneOperation(){};
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
    MoveCraneOperation(const vector<string>& params);
    virtual void doOperation(Ship& ship, Port& port);
    virtual ~MoveCraneOperation(){};
};

//the operation to reject a cargo from the port
class RejectCraneOperation : public CraneOperation {
   private:
   public:
    RejectCraneOperation(const vector<string>& params);
    virtual void doOperation(Ship& ship, Port& port);
    virtual ~RejectCraneOperation(){};
};
