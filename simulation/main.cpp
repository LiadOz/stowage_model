#include <iostream>
#include <stdlib.h>
#include <memory>
#include <stdlib.h>
#include <filesystem>
#include <sstream>

#include "Simulation.h"

#include "AlgorithmRegistrar.h"

#include "../interfaces/AbstractAlgorithm.h"
#include "../common/Util.h"
#include "../common/Exceptions.h"
#include "./Results.h"

#define LOG_FILE "simulation.errors"
#define RESULTS_FILE "simulation.results"
#define FILE_SEPARATOR "/"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
using std::stringstream;

using fs::path;
using std::cerr;
using std::cout;
using std::endl;

namespace fs = std::filesystem;

void loadAlgorithms(const path& algFolder){
	auto &registrar = AlgorithmRegistrar::getInstance();
    for (const auto &entry : fs::directory_iterator(algFolder)) {
        if (entry.path().filename().extension() == DYNAMIC_FILE_EXTENSION) {
            string error;
            if (!registrar.loadAlgorithmFromFile(entry.path().string(), error)) {
                LOG.logError(error);
            }
        }
    }
}

int main(int argc, char **argv) {

    string algorithmDirStr, travelDirStr, outputDirStr;
	try { //get command line arguments
		getCommandLineParameters(argc, argv) >> algorithmDirStr >> travelDirStr >> outputDirStr;
	}
	catch (const FatalError& ferror) {
		std::cout << ferror.what() << endl
				  << "Exiting..." << endl;
		return EXIT_FAILURE;
	}
    remove((outputDirStr + LOG_FILE).c_str());
    LOG.setFile(outputDirStr + LOG_FILE);
    LOG.setLogType("General");

    Results r; // registring travels in results
    for (const auto& entry : fs::directory_iterator(travelDirStr))
        if (entry.is_directory()) r.addTravel(entry.path().filename().string());

    loadAlgorithms(algorithmDirStr);
	auto& registrar = AlgorithmRegistrar::getInstance();
    for (auto algo_iter = registrar.begin(); 
            algo_iter != registrar.end(); ++algo_iter) {
        std::string algName = 
            registrar.getAlgorithmName( algo_iter - registrar.begin());

        r.startRecordingAlg(algName);

        for (const auto& entry : fs::directory_iterator(travelDirStr)){
            if (!entry.is_directory()) continue;
            LOG.setLogType(algName + " " + entry.path().filename().string());
            auto algo = (*algo_iter)();
            try {
                Simulation simulation(
                        entry.path().string(), std::move(algo), algName);
                int num = simulation.runSimulation();
                r.addAlgResult(num);
            }catch(std::exception& e) {
                LOG.logError(e.what());
                r.addAlgResult(-1);
            }
        }
    }
    r.writeToFile(RESULTS_FILE);

	return EXIT_SUCCESS;
}
