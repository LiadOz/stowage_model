#pragma once 
#include "Algorithm.h"
// the brute algorithm moves every container off the ship
// then loads them back on
class _208643270_a : public Algorithm {
protected:
    virtual void getPortInstructions(
            const string& port, vector<Container>& awaiting);
public:
    _208643270_a (){};
    virtual string getName(){ return "_208643270_a";}
    virtual ~_208643270_a(){};
};
