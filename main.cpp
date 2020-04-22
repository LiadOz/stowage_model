#include <iostream>
#include <string>
#include <stdlib.h>
#include "container.h"
#include "ship.h"
#include "algorithm.h"
#include "util.h"
#include "Port.h"
#include "simulation.h"
#include <filesystem>


using std::string;
using std::vector;
using std::cout;
using std::endl;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
namespace fs = std::filesystem;

int main() {
	
	Algorithm* bruteAlgorithm = new BruteAlgorithm();
	Algorithm* rejectAlgorithm = new RejectAlgorithm();


	const fs::path pathToShow{ "./Simulation/" };

	for (const auto& entry : fs::directory_iterator(pathToShow)) {
		const auto folderName = entry.path().filename().string();
		if (entry.is_directory()) {
			Simulation simulation(folderName, bruteAlgorithm);
			simulation.RunSimulation();
			Simulation simulation2(folderName, rejectAlgorithm);
			simulation2.RunSimulation();
		}
	}

    delete bruteAlgorithm;
    delete rejectAlgorithm;

	return EXIT_SUCCESS;
}
