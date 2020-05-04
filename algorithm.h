#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>
#include "AbstractAlgorithm.h"
#include "container.h"
#include "ship.h"

using std::string;

class Algorithm : public AbstractAlgorithm{
protected:
    Ship s;
    vector<string> routes;
    vector<Container> UnloadAll(string port);

    // insertes container to the next free location
    // return false if there is no space left
    size_t next_x, next_y;
    bool InsertNextFree(Container c);
    // this function is called inside getInstructionsForCargo and detailes
    // the operation each algorithm does polymophically
    virtual int GetPortInstructions(
            const string& port, const string& input_path) = 0;
public:
    Algorithm (){};
    virtual ~Algorithm (){};
    virtual int readShipPlan(const string& full_path_and_file_name);
    virtual int readShipRoute(const string& full_path_and_file_name);
    virtual int setWeightBalanceCalculator(WeightBalanceCalculator& calculator){
        (void)calculator;return 0;}
    void FinalDestination();
    virtual string GetName(){return "NOT_DEFINED";};
    virtual int getInstructionsForCargo(
        const std::string& input_full_path_and_file_name,
        const std::string& output_full_path_and_file_name);
};

// the brute algorithm moves every container off the ship
// then loads them back on
class BruteAlgorithm : public Algorithm {
protected:
    virtual int GetPortInstructions(const string& port,
            const string& input_path);
public:
    BruteAlgorithm (){};
    virtual string GetName(){ return "BruteAlgorithm";}
    virtual ~BruteAlgorithm(){};
};

// the reject algorithm accepts only cargo that needs to go
// to the next route
class RejectAlgorithm : public Algorithm {
protected:
    virtual int GetPortInstructions(const string& port,
            const string& input_path);
public:
    RejectAlgorithm(){};
    virtual string GetName(){ return "RejectAlgorithm";}
    virtual ~RejectAlgorithm(){};
};

#endif /* ALGORITHM_H */
