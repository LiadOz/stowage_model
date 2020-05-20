#include <iostream>
#include <stdlib.h>
#include "AlgorithmRegistrar.h"
#include <memory>

int load() {

    auto& registrar = AlgorithmRegistrar::getInstance();
    std::string error;
    if (!registrar.loadAlgorithmFromFile("../algorithm/_208643270_b.so", error)) {
        std::cerr << error << '\n'; 
            return EXIT_FAILURE;
    }
    if (!registrar.loadAlgorithmFromFile("../algorithm/_208643270_a.so", error)) {
        std::cerr << error << '\n'; 
            return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
#include <stdlib.h>
#include <filesystem>
#include <sstream>

#include "Simulation.h"
#include "../common/Util.h"
#include "../common/Exceptions.h"

#define LOG_FILE "simulation.errors"
#define FILE_SEPARATOR "/"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
using std::stringstream;

namespace fs = std::filesystem;

int main(int argc, char** argv) {
    load();

	string algorithmPath, travelPath, outputPath;
    auto& registrar = AlgorithmRegistrar::getInstance();

	try {
		getCommandLineParameters(argc, argv) >> algorithmPath >> travelPath >> outputPath;
		fs::path outPath { outputPath };
		fs::create_directory(outputPath);

		const fs::path travelFolder{ travelPath };

		for (const auto& entry : fs::directory_iterator(travelFolder)) {
			const auto folderName = entry.path().filename().string();
			if (entry.is_directory()) {
                Logger::Instance().setFile(entry.path().string() + LOG_FILE);
                Logger::Instance().setLogType("General");
                Simulation::removeLogFiles(entry.path().string());
                for (auto algo_iter = registrar.begin(); algo_iter != registrar.end(); ++algo_iter) {	
                    auto algo = (*algo_iter)();
                    std::string algName = registrar.getAlgorithmName(algo_iter - registrar.begin());
                    std::cout << "running " << algName << std::endl;
                    //algo = std::unique_ptr<_208643270_a>(new _208643270_a());
                    Simulation simulation(folderName, std::move(algo), algName);
                    simulation.runSimulation();
                }	
			}
		}

	}
	catch (const FatalError & ferror) {
		//TODO: log error
        std::cout << "hasdfasdf" << std::endl;
        std::cout << ferror.what() << std::endl;
        return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

