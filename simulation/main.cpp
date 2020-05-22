#include <stdlib.h>

#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>

#include "../common/Exceptions.h"
#include "../common/Util.h"
#include "../interfaces/AbstractAlgorithm.h"
#include "./Results.h"
#include "AlgorithmRegistrar.h"
#include "Simulation.h"

#define LOG_FILE "simulation.errors"
#define FILE_SEPARATOR "/"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
using std::stringstream;

using fs::path;
using std::cerr;
using std::cout;
using std::endl;

namespace fs = std::filesystem;

void loadAlgorithms(const path &algFolder) {
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
    Results r;
    auto &registrar = AlgorithmRegistrar::getInstance();

    try {
        //get command line arguments
        getCommandLineParameters(argc, argv) >> algorithmDirStr >> travelDirStr >> outputDirStr;
    }

    catch (const FatalError &ferror) {
        //TODO: log error
        std::cout << ferror.what() << endl
                  << "Exiting..." << endl;
        return EXIT_FAILURE;
    }

    //create paths from strings
    const path algorithmPath{algorithmDirStr};
    const path travelPath{travelDirStr};
    const path outputPath{outputDirStr};

    for (const auto &entry : fs::directory_iterator(travelPath))
        if (entry.is_directory()) {
            r.addTravel(entry.path().filename().string());
        }

    loadAlgorithms(algorithmPath);

    for (auto algo_iter = registrar.begin();
         algo_iter != registrar.end(); ++algo_iter) {
        std::string algName =
            registrar.getAlgorithmName(algo_iter - registrar.begin());

        r.startRecordingAlg(algName);

        for (const auto &entry : fs::directory_iterator(travelPath)) {
            if (!entry.is_directory())
                continue;
            //Logger::Instance().setFile(entry.path().string() + LOG_FILE);
            //Logger::Instance().setLogType("General");
            auto algo = (*algo_iter)();
            string travelName = entry.path().filename().string();
            Simulation simulation(outputPath.string(), travelPath.string(), travelName, algName, std::move(algo));
            simulation.runSimulation();
            r.addAlgResult(1);
        }
    }
    r.writeToFile("this");

    return EXIT_SUCCESS;
}

// manual check
/*
    auto algo = (*registrar.begin())();
    std::string algName = registrar.getAlgorithmName(0);
    string folderName = "./Simulation/example_travel_4";
    std::cout << "running " << algName << std::endl;
    Simulation simulation(folderName, std::move(algo), algName);
    simulation.runSimulation();
    */
/*
		//create paths from strings
		const path algorithmPath{algorithmDirStr};
		const path travelPath{travelDirStr};
		const path outputPath{outputDirStr};

		//TODO: Travel folder validations (number 7 in page 4)

		for (const AbstractAlgorithm &algorithm : algorithms)
		{

			//TODO: log algorithm loaded or something
			for (const auto &entry : travelPath)
			{
                (void)entry;
                (void)algorithm;
				//todo: continue here
			}
		}

		//TODO: this is the iter for algorithms
		//  for (auto algo_iter = registrar.begin(); algo_iter != registrar.end(); ++algo_iter) {
		//             auto algo = (*algo_iter)();
		//             std::string algName = registrar.getAlgorithmName(algo_iter - registrar.begin());
		//             std::cout << "running " << algName << std::endl;
		//             //algo = std::unique_ptr<_208643270_a>(new _208643270_a());
		//             Simulation simulation(folderName, std::move(algo), algName);
		//             simulation.runSimulation();
		//         }

		for (const auto &entry : fs::directory_iterator(travelPath))
		{
			const auto folderName = entry.path().filename().string();
			if (entry.is_directory())
			{
				Logger::Instance().setFile(entry.path().string() + LOG_FILE);
				Logger::Instance().setLogType("General");

				//Simulation::removeLogFiles(entry.path().string());
				//Simulation simulation(folderName, bruteAlgorithm);
				//simulation.runSimulation();
				//Simulation simulation2(folderName, rejectAlgorithm);
				//simulation2.runSimulation();
			}
		}

		//delete bruteAlgorithm;
		//delete rejectAlgorithm;
*/
