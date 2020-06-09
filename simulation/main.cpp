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
    SimulationManager s(algorithmDirStr, outputDirStr);
    s.runSimulations(travelDirStr, outputDirStr);
    s.recordResults(outputDirStr);


    return EXIT_SUCCESS;
}
