#pragma once

#include <unordered_map>
#include <unordered_set>

#include "Algorithm.h"

using std::unordered_map;
using std::unordered_set;

// Algorithm which uses a heuristic of placing cargo only on cargo that would be be unloaded after
class AdvancedAlgorithm : public Algorithm {
private:
    unordered_map<string, int> cargoPriority; // lower value means closer to the top
    // using this priorty we say that a cargo is placed on top of the other
    // in a good way if the bottom's priority is bigger then the upper's
    void setPriority();
    // gets a vector of awaiting containers at port and a set of container ids
    // each of the id in the set represent a container in the vector that must return the ship
    virtual Algorithm::InsertStatus loadAwaiting(vector<Container>& awaiting, unordered_set<string>& mustReturn) = 0;


    // unloads every container from specified port and those above it
    // it returns a set of ids that are inside awaiting that must return to the ship
    virtual unordered_set<string> unloadPort(const string& port, vector<Container>& awaiting);
protected:
    // returns true if placing a container with certain port on top of another one is good placement
    int placeOn(const string& above, const string& below);
    virtual void getPortInstructions(
            const string& port, vector<Container>& awaiting);
public:
    AdvancedAlgorithm(){};
    virtual ~AdvancedAlgorithm(){};

};
