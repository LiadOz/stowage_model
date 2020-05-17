#pragma once 
#include "Algorithm.h"
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
