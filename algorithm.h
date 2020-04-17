#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>
#include <unordered_set>
#include "container.h"
#include "ship.h"

using std::string;
using std::unordered_set;

class Algorithm {
protected:
    Ship s;
    vector<string> routes;
    unordered_set<Container*> outside;
    void unloadAll(string port);
public:
    Algorithm (){};
    void readShipPlan(const string& full_path_and_file_name){ s = Ship(full_path_and_file_name); }
    void readShipRoute(const string& full_path_and_file_name);
    void finalDestination();
    virtual void getInstructionsForCargo(
            const string& input_full_path_and_file_name,
            const string& output_full_path_and_file_name){};
};

// the brute algorithm moves every container off the ship
// then loads them back on
class BruteAlgroithm : public Algorithm {
private:
    // insertes container to the next free location
    // return false if there is no space left
    size_t next_x, next_y;
    bool insertNextFree(Container* c);
public:
    BruteAlgroithm (){};
    virtual void getInstructionsForCargo(
            const string& input_full_path_and_file_name,
            const string& output_full_path_and_file_name);
};

#endif /* ALGORITHM_H */
