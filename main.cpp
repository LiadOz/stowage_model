#include <stdlib.h>
#include <filesystem>
#include <sstream>

#include "Simulation.h"
#include "Algorithm.h"
#include "Util.h"
#include "Exceptions.h"

#define LOG_FILE "simulation.errors"
#define FILE_SEPARATOR "/"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
using std::stringstream;

namespace fs = std::filesystem;

int main(int argc, char** argv) {

	int errorStatus = 0;
	string algorithmPath, travelPath, outputPath;
	vector<AbstractAlgorithm> algorithms;

	try {
		getCommandLineParameters(argc, argv) >> algorithmPath >> travelPath >> outputPath;
		fs::path outPath { outputPath };
		fs::create_directory(outputPath);

		Algorithm* bruteAlgorithm = new BruteAlgorithm();
		Algorithm* rejectAlgorithm = new RejectAlgorithm();

		const fs::path travelFolder{ travelPath };
		const fs::path algorithmsFolder { algorithmPath };

		for (const auto& entry: fs::directory_iterator(algorithmsFolder)) {
			if (entry.path().filename().extension() == DYNAMIC_FILE_EXTENSION) {
				//todo: register algo and add to algo vectors
			}
		}

		for (const AbstractAlgorithm& algorithm : algorithms) {
			
			//TODO: log algorithm loaded or something
			for (const auto& entry : travelFolder) {
				//todo: continue here
			}

			
		}

		for (const auto& entry : fs::directory_iterator(travelFolder)) {
			const auto folderName = entry.path().filename().string();
			if (entry.is_directory()) {
				Logger::Instance().setFile(entry.path().string() + LOG_FILE);
				Logger::Instance().setLogType("General");

				Simulation::removeLogFiles(entry.path().string());
				Simulation simulation(folderName, bruteAlgorithm);
				simulation.runSimulation();
				Simulation simulation2(folderName, rejectAlgorithm);
				simulation2.runSimulation();
			}
		}

		delete bruteAlgorithm;
		delete rejectAlgorithm;
	}
	catch (const FatalError & ferror) {
		//TODO: log error
		std::cout << "hasdfasdf";
	}

	return EXIT_SUCCESS;
}

