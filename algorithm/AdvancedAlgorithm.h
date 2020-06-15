#pragma once

#include <unordered_map>
#include <unordered_set>

#include "Algorithm.h"

using std::unordered_map;
using std::unordered_set;

// Algorithm which uses a heuristic of placing cargo only on cargo that would be be unloaded after
// every implementing algorithm has to implement unloadPort and loadAwating
// unloadPort has default implementation, unloadPort is called before loadAwating
class AdvancedAlgorithm : public Algorithm {
private:
    unordered_map<string, int> cargoPriority; // lower value means closer to the top
    // gets a vector of awaiting containers at port and a set of container ids
    // each of the id in the set represent a container in the vector that must return the ship
    virtual Algorithm::InsertStatus loadAwaiting(vector<Container>& awaiting, unordered_set<string>& mustReturn) = 0;


    // unloads every container from specified port and those above it
    // it returns a set of ids that are inside awaiting that must return to the ship
    virtual unordered_set<string> unloadPort(const string& port, vector<Container>& awaiting);
protected:
    // returns the coordinate to where the cloest cargo with certain 
    // port is
    pair<int, int> getClosestCoordinate(const string& port);
    // using this priorty we say that a cargo is placed on top of the other
    // in a good way if the bottom's priority is bigger then the upper's
    void setPriority();
    // returns true if placing a container with certain port on top of another one is good placement
    int placeOn(const string& above, const string& below);
    virtual void getPortInstructions(
            const string& port, vector<Container>& awaiting);
    // finds a good location to move a container at coordinate
    // good means that you will be placed on the one that is closest to your port
    // if no location is found returns {-1, -1}
    pair<int, int> findGoodLocation(int x, int y, const string& port);
    // sorts vector according to priority the starting cargos should be placed high
    void prioritySort(vector<Container>& toSort);
public:
    AdvancedAlgorithm(){};
    virtual ~AdvancedAlgorithm(){};

};
