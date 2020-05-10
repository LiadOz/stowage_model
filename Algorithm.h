#pragma once 

#include "AbstractAlgorithm.h"

#include <string>
#include <vector>

#include "Container.h"
#include "Ship.h"

using std::string;

class Algorithm : public AbstractAlgorithm{
protected:
    Ship s;
    vector<string> routes;
    vector<Container> unloadAll(string port);
    int errorStatus = 0;
    size_t next_x, next_y;
    // inserts container to the next free location
    // return false if there is no space left
    bool insertNextFree(Container c);
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

// the brute algorithm moves every container off the ship
// then loads them back on
class BruteAlgorithm : public Algorithm {
protected:
    virtual void getPortInstructions(
            const string& port, vector<Container>& awaiting);
public:
    BruteAlgorithm (){};
    virtual string getName(){ return "BruteAlgorithm";}
    virtual ~BruteAlgorithm(){};
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
