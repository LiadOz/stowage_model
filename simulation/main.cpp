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

#define LOG_FILE "simulation.errors"
#define FILE_SEPARATOR "/"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
using std::stringstream;

using fs::path;
using std::cerr;
using std::cout;
using std::endl;

namespace fs = std::filesystem;

int load()
{

	auto &registrar = AlgorithmRegistrar::getInstance();
	string error;
	//TODO: change to param path
	if (!registrar.loadAlgorithmFromFile("../algorithm/_208643270_b.so", error))
	{
		std::cerr << error << '\n';
		return EXIT_FAILURE;
	}
	//TODO: change to param path
	if (!registrar.loadAlgorithmFromFile("../algorithm/_208643270_a.so", error))
	{
		std::cerr << error << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
	string algorithmDirStr, travelDirStr, outputDirStr;
	vector<AbstractAlgorithm> algorithms;
	auto &registrar = AlgorithmRegistrar::getInstance();

	try
	{
		//get command line arguments
		getCommandLineParameters(argc, argv) >> algorithmDirStr >> travelDirStr >> outputDirStr;

		//create paths from strings
		const path algorithmPath{algorithmDirStr};
		const path travelPath{travelDirStr};
		const path outputPath{outputDirStr};

		//TODO: Travel folder validations (number 7 in page 4)

		for (const auto &entry : fs::directory_iterator(algorithmPath))
		{
			if (entry.path().filename().extension() == DYNAMIC_FILE_EXTENSION)
			{
				//todo: register algo and add to algo vectors
			}
		}

		for (const AbstractAlgorithm &algorithm : algorithms)
		{

			//TODO: log algorithm loaded or something
			for (const auto &entry : travelPath)
			{
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
	}
	catch (const FatalError &ferror)
	{
		//TODO: log error
		std::cout << ferror.what() << endl
				  << "Exiting..." << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
