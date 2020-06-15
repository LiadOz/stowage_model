#include <stdlib.h>

#include <iostream>

#include "./SimulationManager.h"
#include "../common/Exceptions.h"
#include "../common/Util.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
    string algorithmDirStr, travelDirStr, outputDirStr;

    try {  //get command line arguments
        getCommandLineParameters(argc, argv) >> algorithmDirStr >> travelDirStr >> outputDirStr;
    } catch (const FatalError& ferror) {
        std::cout << ferror.what() << endl
                  << "Exiting..." << endl;
        return EXIT_FAILURE;
    }

    // call the Simulation Manager
    // the one should be replaced with the num of threads
    // TODO: get number of threads
    SimulationManager s(algorithmDirStr, outputDirStr);
    s.runSimulations(travelDirStr, outputDirStr, 1);
    s.recordResults(outputDirStr);


    return EXIT_SUCCESS;
}
