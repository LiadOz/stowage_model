#include <stdlib.h>
#include "algorithm.h"
#include "util.h"
#include "simulation.h"
#include <filesystem>

#define LOG_FILE "simulation.errors"
#define SIMULATION_ROOT_FOLDER "./Simulation/"
#define FILE_SEPARATOR "/"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
namespace fs = std::filesystem;

int main() {
	
	Algorithm* bruteAlgorithm = new BruteAlgorithm();
	Algorithm* rejectAlgorithm = new RejectAlgorithm();

	const fs::path pathToShow{ "./Simulation/" };

	for (const auto& entry : fs::directory_iterator(pathToShow)) {
		const auto folderName = entry.path().filename().string();
		if (entry.is_directory()) {
            string folderPath = SIMULATION_ROOT_FOLDER + folderName+ FILE_SEPARATOR;
            Logger::Instance().SetFile(folderPath + LOG_FILE);
            Logger::Instance().SetLogType("General");
			Simulation::RemoveLogFiles(entry.path().string());
			Simulation simulation(folderName, bruteAlgorithm);
			simulation.RunSimulation();
			Simulation simulation2(folderName, rejectAlgorithm);
			simulation2.RunSimulation();
		}
	}

    delete bruteAlgorithm;
    delete rejectAlgorithm;

    /*
    Algorithm& b = *(new BruteAlgorithm());
    int me = b.readShipPlan("invalid.plan");
    std::cout << me << std::endl;
    */
	return EXIT_SUCCESS;
}
