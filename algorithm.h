#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>
#include "ship.h"
using std::string;

class Algorithm {
protected:
    Ship s;
    vector<string> routes;
public:
    Algorithm ();
    void readShipPlan(const string& full_path_and_file_name){ s = Ship(full_path_and_file_name); }
    void readShipRoute(const string& full_path_and_file_name);
    virtual void getInstructionsForCargo(
            const string& input_full_path_and_file_name,
            const string& output_full_path_and_file_name){};
};

// the brute algorithm moves every container off the ship
// then loads them back on
class BruteAlgroithm : protected Algorithm {
public:
    virtual void getInstructionsForCargo(
            const string& input_full_path_and_file_name,
            const string& output_full_path_and_file_name);
};

#endif /* ALGORITHM_H */
