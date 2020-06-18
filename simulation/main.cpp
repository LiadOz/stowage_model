#include <stdlib.h>

#include <iostream>

#include "./SimulationManager.h"
#include "../common/Exceptions.h"
#include "../common/Util.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
    string algorithmDirStr, travelDirStr, outputDirStr;
    int numOfThreads;

    try {  //get command line arguments
        getCommandLineParameters(argc, argv) >> algorithmDirStr >> travelDirStr >> outputDirStr >> numOfThreads;
    } catch (const FatalError& ferror) {
        std::cout << ferror.what() << endl
                  << "Exiting..." << endl;
        return EXIT_FAILURE;
    }

    SimulationManager s(algorithmDirStr, outputDirStr);
    // TODO: add more threads to nova using this  guide
    // https://www.youtube.com/watch?v=dQw4w9WgXcQ
    s.runSimulations(travelDirStr, outputDirStr, numOfThreads);
    s.recordResults(outputDirStr);

    return EXIT_SUCCESS;
}
