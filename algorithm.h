#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
using std::string;

class Algorithm {
private:
    

public:
    Algorithm ();
    void readShipPlan(const string& full_path_and_file_name);
    void readShipRoute(const string& full_path_and_file_name);
    void getInstructionsForCargo(
            const string& input_full_path_and_file_name,
            const string& output_full_path_and_file_name);
};

#endif /* ALGORITHM_H */
