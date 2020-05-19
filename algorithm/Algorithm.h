#pragma once 

#include "../interfaces/AbstractAlgorithm.h"
#include "../interfaces/AlgorithmRegistration.h"

#include <string>
#include <vector>

#include "../common/Container.h"
#include "../common/WeightBalanceCalculator.h"
#include "../common/Ship.h"

using std::string;

class Algorithm : public AbstractAlgorithm{
protected:
    enum InsertStatus { SUCCSESS, IMPOSSIBLE, ERROR, FULL };
    Ship s;
    WeightBalanceCalculator calc;
    vector<string> routes;
    vector<Container> unloadAll(string port);
    int errorStatus = 0;
    size_t next_x, next_y;
    // inserts container to the next free location
    InsertStatus insertNextFree(Container c);
    // inserts container to place which has the most space above it
    InsertStatus insertBiggestDepth(Container c);
    // this function is called inside getInstructionsForCargo and detailes
    // the operation each algorithm does polymophically
    virtual void getPortInstructions(
            const string& port, vector<Container>& awaiting) = 0;
    // prepares the cargo in port
    void setAwaitingCargo(const string& file_path, vector<Container>& awaiting);
    // logs errors in the algorithm
public:
    Algorithm (){};
    virtual ~Algorithm (){};
    virtual int readShipPlan(const string& full_path_and_file_name);
    virtual int readShipRoute(const string& full_path_and_file_name);
    virtual int setWeightBalanceCalculator(WeightBalanceCalculator& calculator){
        (void)calculator;return 0;}
    void finalDestination();
    virtual string getName(){return "NOT_DEFINED";};
    virtual int getInstructionsForCargo(
        const std::string& input_full_path_and_file_name,
        const std::string& output_full_path_and_file_name);
};

// the reject algorithm accepts only cargo that needs to go
// to the next route
class RejectAlgorithm : public Algorithm {
protected:
    virtual void getPortInstructions(
            const string& port, vector<Container>& awaiting);
public:
    RejectAlgorithm(){};
    virtual string getName(){ return "RejectAlgorithm";}
    virtual ~RejectAlgorithm(){};
};
