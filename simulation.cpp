#include "simulation.h"
#include <iostream>
#include <filesystem>
#include "util.h"

#define LOG_FILE "simulation.errors"
namespace fs = std::filesystem;

using std::stringstream;

#define FILE_SEPARATOR "/"
#define SIMULATION_ROOT_FOLDER "./Simulation/"
#define SIMULATION_SHIP_FILE_NAME "sample.plan"
#define SIMULATION_ROUTE_FILE_NAME "ports"
#define SIMULATION_PORTS_FOLDER_NAME "portsCargo/"
#define SIMULATION_CARGO_INSTRUCTIONS_FOLDER "Instructions/"
#define SIMULATION_ERROR_FILE_NAME "errors.txt"
#define SIMULATION_RESULTS_FILE_NAME "results.txt"

Simulation::Simulation(string rootFolder, Algorithm* algo)
{
	Logger::Instance().setFile(LOG_FILE);
	Logger::Instance().setLogType("Simulation init");
	string folderPath = SIMULATION_ROOT_FOLDER + rootFolder + FILE_SEPARATOR;
	string shipPath = folderPath + SIMULATION_SHIP_FILE_NAME;
	string routePath = folderPath + SIMULATION_ROUTE_FILE_NAME;
	folder = folderPath;
	route = new ShipRoute(routePath);
	LoadContainersToPortsInRoute();
	ship = new Ship(shipPath);
	algorithm = algo;
	PrepareAlgorithm(shipPath, routePath);
	actionsPerformedCounter = 0;
}

void Simulation::PrepareAlgorithm(string shipPath, string routePath)
{
	algorithm->readShipPlan(shipPath);
	algorithm->readShipRoute(routePath);

}

void Simulation::RemoveLogFiles(string simulationFolder)
{
	string errorsFile = simulationFolder + FILE_SEPARATOR + SIMULATION_ERROR_FILE_NAME;
	string resultsFile = simulationFolder + FILE_SEPARATOR + SIMULATION_RESULTS_FILE_NAME;

	remove(errorsFile.c_str());
	remove(resultsFile.c_str());
}

bool Simulation::LoadContainersToPortsInRoute()
{
	map<string, list<string>> portsMap = CreatePortsCargoFromFiles();

	vector<Port>& ports = this->route->getRoute();

	//last port doesn't need a file, ignore it
	for (size_t i = 0; i < ports.size() - 1; i++)
	{
		Port& port = ports[i];
		string portCode = port.getPortCode();

		if (portsMap.find(portCode) == portsMap.end())
		{
			Logger::Instance().logError("Port file doesn't exist");
			LogSimulationErrors("LoadContainersToPortsInRoute", "Port file doesn't exist");
		}

		else
		{
			auto& filesList = portsMap.find(portCode)->second;
			if (filesList.empty())
			{
				Logger::Instance().logError("Port file doesn't exist");
				LogSimulationErrors("LoadContainersToPortsInRoute", "Port file doesn't exist");
			}

			else
			{
				port.LoadContainersFromFile(folder + SIMULATION_PORTS_FOLDER_NAME + filesList.front());
				filesList.pop_front();
			}
		}
	}

	return true;
}

map<string, list<string>> Simulation::CreatePortsCargoFromFiles()
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

void Simulation::RunSimulation()
{
	vector<Port>& ports = this->route->getRoute();
	string outputFolderPath = folder + SIMULATION_CARGO_INSTRUCTIONS_FOLDER;
	Logger::Instance().setLogType(this->algorithm->getName());
	for (size_t i = 0; i < ports.size(); i++) {
		try
		{
			Logger::Instance().setLogType("Simulation Port - " + ports[i].getPortCode());
			string outputFilePath = outputFolderPath + std::to_string(i);
			algorithm->getInstructionsForCargo(ports[i].getCargoFilePath(), outputFilePath);
			PerformAlgorithmActions(outputFilePath, ports[i]);
		}
		catch (const std::exception & error)
		{
			LogSimulationErrors("RunSimulation", error.what());
		}
	}

	LogResults();
}

void Simulation::PerformAlgorithmActions(string filePath, Port& port)
{
	ifstream file(filePath);
	string lineFromFile;

	while (getline(file, lineFromFile))
	{

		/*if line is a comment - ignore*/
		if (isCommentLine(lineFromFile))
		{
			continue;
		}

		CraneOperation* craneOperation = CreateOperationFromLine(lineFromFile);

		//check that craneOperation is valid

		if (craneOperation == NULL)
		{
			LogSimulationErrors("PerformAlgorithmActions", "craneOperation is null");
		}

		//operation format is valid
		else
		{
			try
			{
				craneOperation->DoOperation(ship, port);
				actionsPerformedCounter++;
			}
			catch (const std::exception & error)
			{
				LogSimulationErrors("PerformAlgorithmActions", error.what());
			}
		}

		delete craneOperation;
	}

	ValidateAllPortCargoUnloaded(this->ship, port);

	file.close();
}

void Simulation::ValidateAllPortCargoUnloaded(Ship* ship, Port& port)
{
	string portID = port.getPortCode();
	vector<Container> shipContainers = ship->getShipContainers();

	for (size_t i = 0; i < shipContainers.size(); i++)
	{
		if (shipContainers[i].getDestination() == portID)
		{
			LogSimulationErrors("ValidateAllPortCargoUnloaded", "container " + shipContainers[i].getId() + " didn't unload at port " + portID);
		}
	}
}

CraneOperation* Simulation::CreateOperationFromLine(string lineFromFile) {

	vector<string> operationsData;
	CraneOperation* craneOperation = NULL;
	operationsData = getDataFromLine(lineFromFile, CRANE_OPERATIONS_FILE_MAX_NUM_OF_PARAMS, true);
	string operationString = operationsData.size() ? operationsData[0] : "";
	Operations operation = CraneOperation::GetOperationType(operationString);

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
			LogSimulationErrors("CreateOperationFromLine", "invalid operation enum type");
			break;
		}
	}
	catch (const std::exception & error)
	{
		LogSimulationErrors("CreateOperationFromLine", error.what());
		cout << error.what();
	}

	return craneOperation;
}

void Simulation::LogResults()
{
	ofstream file;
	file.open(folder + SIMULATION_RESULTS_FILE_NAME, std::ios::app);
	file << "algorithm " << algorithm->getName() << " has performed " << actionsPerformedCounter << " actions." << endl;
	file.close();
}

void Simulation::LogSimulationErrors(string funcName, string error)
{
	ofstream file;
	file.open(folder + SIMULATION_ERROR_FILE_NAME, std::ios::app);
	file << "function" << funcName << ": " << error << endl;
	file.close();
}


Simulation::~Simulation() {
	delete this->ship;
	delete this->route;
	Logger::Instance().saveFile();
}
