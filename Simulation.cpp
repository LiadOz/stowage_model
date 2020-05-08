#include "Simulation.h"

#include <iostream>
#include <filesystem>

#include "Util.h"

namespace fs = std::filesystem;

using std::stringstream;
using std::map;
using std::endl;

#define FILE_SEPARATOR "/"
#define SIMULATION_ROOT_FOLDER "./Simulation/"
#define SIMULATION_SHIP_FILE_NAME "sample.plan"
#define SIMULATION_ROUTE_FILE_NAME "ports"
#define SIMULATION_PORTS_FOLDER_NAME "portsCargo/"
#define SIMULATION_CARGO_INSTRUCTIONS_FOLDER "Instructions/"
#define SIMULATION_ERROR_FILE_NAME "errors.txt"
#define SIMULATION_RESULTS_FILE_NAME "results.txt"

Simulation::Simulation(const string& rootFolder, Algorithm* algo) {
	string folderPath = SIMULATION_ROOT_FOLDER + rootFolder + FILE_SEPARATOR;
	string shipPath = folderPath + SIMULATION_SHIP_FILE_NAME;
	string routePath = folderPath + SIMULATION_ROUTE_FILE_NAME;
	folder = folderPath;
	route = createShipRoute(routePath);
	loadContainersToPortsInRoute();
	ship = new Ship();
    ship->readPlan(shipPath);
	algorithm = algo;
	prepareAlgorithm(shipPath, routePath);
}

//init algorithm stuff
void Simulation::prepareAlgorithm(const string& shipPath, const string& routePath)
{
	algorithm->readShipPlan(shipPath);
	algorithm->readShipRoute(routePath);

}

//remove older log files before running the entire program
void Simulation::removeLogFiles(const string& simulationFolder)
{
	string errorsFile = simulationFolder + FILE_SEPARATOR + SIMULATION_ERROR_FILE_NAME;
	string resultsFile = simulationFolder + FILE_SEPARATOR + SIMULATION_RESULTS_FILE_NAME;

	remove(errorsFile.c_str());
	remove(resultsFile.c_str());
}

//will load all containers from file to the relevant port
bool Simulation::loadContainersToPortsInRoute()
{
	map<string, list<string>> portsMap = createPortsCargoFromFiles();

	vector<Port>& ports = this->route;

	//last port doesn't need a file, ignore it
	for (size_t i = 0; i < ports.size() - 1; i++)
	{
		Port& port = ports[i];
		string portCode = port.getPortCode();

		//check if port doesn't exist
		if (portsMap.find(portCode) == portsMap.end())
		{
			Logger::Instance().logError("Port file doesn't exist");
			logSimulationErrors("loadContainersToPortsInRoute", "Port file doesn't exist");
		}

		else
		{
			auto& filesList = portsMap.find(portCode)->second;
			
			//check if port doesn't exist
			if (filesList.empty())
			{
				Logger::Instance().logError("Port file doesn't exist");
				logSimulationErrors("loadContainersToPortsInRoute", "Port file doesn't exist");
			}

			else
			{
				port.loadContainersFromFile(folder + SIMULATION_PORTS_FOLDER_NAME + filesList.front());
				filesList.pop_front();
			}
		}
	}

	return true;
}

//helper function for loadContainersToPortsInRoute
map<string, list<string>> Simulation::createPortsCargoFromFiles()
{
	map<string, list<string>> map;

	for (const auto& entry : fs::directory_iterator(folder + SIMULATION_PORTS_FOLDER_NAME))
	{
		string fileName = entry.path().filename().string();

		if (validCargoFile(fileName))
		{
			string portCode = fileName.substr(0, 5);

			//port is not in the map yet
			if (map.find(portCode) == map.end())
			{
				list<string> list;
				map.insert(std::make_pair(portCode, list));
			}

			//add file to map
			map.find(portCode)->second.push_back(fileName);
		}
	}

	return map;
}

//the main function for simulator, will run the sim itself
void Simulation::runSimulation()
{
	vector<Port>& ports = this->route;
	string outputFolderPath = folder + SIMULATION_CARGO_INSTRUCTIONS_FOLDER;
	Logger::Instance().setLogType(this->algorithm->getName());

	//go through all the ports and do actions there
	for (size_t i = 0; i < ports.size(); i++) {
		try
		{
			string outputFilePath = outputFolderPath + std::to_string(i);
			algorithm->getInstructionsForCargo(ports[i].getCargoFilePath(), outputFilePath);
			performAlgorithmActions(outputFilePath, ports[i]);
		}
		catch (const std::exception & error)
		{
			logSimulationErrors("runSimulation", error.what());
		}
	}

	logResults();
}

//read file from algo and try to do the actions
void Simulation::performAlgorithmActions(const string& filePath, Port& port)
{
    std::ifstream file(filePath);
	string lineFromFile;

	while (getline(file, lineFromFile))
	{

		/*if line is a comment - ignore*/
		if (isCommentLine(lineFromFile))
		{
			continue;
		}

		CraneOperation* craneOperation = createOperationFromLine(lineFromFile);

		//check that craneOperation is valid

		if (craneOperation == NULL)
		{
			logSimulationErrors("performAlgorithmActions", "craneOperation is null");
		}

		//operation format is valid
		else
		{
			try
			{
				craneOperation->doOperation(ship, port);
				actionsPerformedCounter++;
			}
			catch (const std::exception & error)
			{
				logSimulationErrors("performAlgorithmActions", error.what());
			}
		}

		delete craneOperation;
	}

	validateAllPortCargoUnloaded(this->ship, port);

	file.close();
}

//make sure all cargo is in the port
void Simulation::validateAllPortCargoUnloaded(Ship* ship, Port& port)
{
	string portID = port.getPortCode();
	vector<Container> shipContainers = ship->getShipContainers();

	for (size_t i = 0; i < shipContainers.size(); i++)
	{
		if (shipContainers[i].getDestination() == portID)
		{
			logSimulationErrors("validateAllPortCargoUnloaded", "container " + shipContainers[i].getId() + " didn't unload at port " + portID);
		}
	}
}

//create a crane operation from the input proviced from one instruction
CraneOperation* Simulation::createOperationFromLine(const string& lineFromFile) {

	vector<string> operationsData;
	CraneOperation* craneOperation = NULL;

	//get data from line, params may vary
	operationsData = getDataFromLine(lineFromFile, CRANE_OPERATIONS_FILE_MAX_NUM_OF_PARAMS, true);

	//peak at the (supposed) type of action 
	string operationString = operationsData.size() ? operationsData[0] : "";
	Operations operation = CraneOperation::getOperationType(operationString);

	/*after determining the type of the operation, create the operation*/
	try
	{
		switch (operation)
		{
		case Operations::load:
			craneOperation = new LoadCraneOperation(operationsData);
			break;
		case Operations::unload:
			craneOperation = new UnloadCraneOperation(operationsData);
			break;
		case Operations::move:
			craneOperation = new MoveCraneOperation(operationsData);
			break;
		case Operations::reject:
			craneOperation = new RejectCraneOperation(operationsData);
			break;
		default:
			logSimulationErrors("createOperationFromLine", "invalid operation enum type");
			break;
		}
	}
	catch (const std::exception & error)
	{
		logSimulationErrors("createOperationFromLine", error.what());
        std::cout << error.what();
	}

	return craneOperation;
}

void Simulation::logResults()
{
	ofstream file;
	file.open(folder + SIMULATION_RESULTS_FILE_NAME, std::ios::app);
	file << "algorithm " << algorithm->getName() << " has performed " << actionsPerformedCounter << " actions." << endl;
	file << "the ship successfully delivered " << ship->getTotalCorrectUnloads() << " cargos. " << endl;
	file.close();
}

void Simulation::logSimulationErrors(const string& funcName, const string& error)
{
    Logger::Instance().logError("function" + funcName + ": " + error);
}


Simulation::~Simulation() {
	delete this->ship;
	LOG.saveFile();
}