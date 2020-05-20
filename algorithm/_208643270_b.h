#pragma once

#include <unordered_map>
#include <unordered_set>

#include "Algorithm.h"

using std::unordered_map;
using std::unordered_set;

// in this algorithm when you load new containers you insert the ones that are going to farther ports first
class _208643270_b : public Algorithm {
private:
    unordered_map<string, int> cargoPriority; // lower value means closer to the top
    // using this priorty we say that a cargo is placed on top of the other
    // in a good way if the bottom's priority is bigger then the upper's
    void setPriority();
    Algorithm::InsertStatus loadAwaiting(vector<Container>& awaiting, unordered_set<string>& mustReturn);
    // unloads every container from specified port and those above it
    // it returns a set of ids that are inside awaiting that must return to the ship
    unordered_set<string> unloadPort(const string& port, vector<Container>& awaiting);
protected:
    virtual void getPortInstructions(
            const string& port, vector<Container>& awaiting);
public:
    _208643270_b (){};
    virtual ~_208643270_b (){};

};
