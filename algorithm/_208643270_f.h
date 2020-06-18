#pragma once 
#include "SuperAdvancedAlgorithm.h"

class _208643270_f : public SuperAdvancedAlgorithm {
protected:
    // this method reverses the order that the best stack is found
    // switching between case 3 and cases 1 2
    // this somehow has better performance
    pair<int, int> getBestStack(const string& port, int x, int y);
public:
    _208643270_f (){};
    virtual ~_208643270_f (){};
};
