#pragma once

#include <unordered_map>

#include "Algorithm.h"

using std::unordered_map;

class AdvancedAlgorithm : public Algorithm {
private:
    unordered_map<string, int> cargoPriority; // lower value means closer to the top
    // using this priorty we say that a cargo is placed on top of the other
    // in a good way if the bottom's priority is bigger then the upper's
    void setPriority();
    Algorithm::InsertStatus loadAwaiting(vector<Container>& awaiting);
    void unloadOpen(const string& port);
protected:
    virtual void getPortInstructions(
            const string& port, vector<Container>& awaiting);
public:
    AdvancedAlgorithm (){};
    virtual string getName(){ return "AdvancedAlgorithm";}
    virtual ~AdvancedAlgorithm (){};

};
