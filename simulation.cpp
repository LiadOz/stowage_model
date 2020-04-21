#include "simulation.h"
#include <iostream>
#include <filesystem>
#include "util.h"

namespace fs = std::filesystem;

using std::stringstream;

#define FILE_SEPARATOR "/"
#define SIMULATION_ROOT_FOLDER "./Simulation/"
#define SIMULATION_SHIP_FILE_NAME "sample.plan"
#define SIMULATION_ROUTE_FILE_NAME "ports"
#define SIMULATION_PORTS_FOLDER_NAME "portsCargo/"
#define SIMULATION_CARGO_INSTRUCTIONS_FOLDER "Instructions/"

Simulation::Simulation(string rootFolder, Algorithm* algo)
{
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
}

void Simulation::PrepareAlgorithm(string shipPath, string routePath)
{
	algorithm->readShipPlan(shipPath);
	algorithm->readShipRoute(routePath);
}

bool Simulation::LoadContainersToPortsInRoute()
{
	map<string, list<string>> portsMap = CreatePortsCargoFromFiles();

	 vector<Port>& ports = this->route->getRoute();
	
	//last port doesn't need a file, ignore it
	for (size_t i = 0; i < ports.size()-1; i++)
	{
		Port& port = ports[i];
		string portCode = port.getPortCode();

		if (portsMap.find(portCode) == portsMap.end())
		{
            Logger::Instance().logError("Port file doesn't exist");
		}

		else
		{
			auto& filesList = portsMap.find(portCode)->second;
			if (filesList.empty())
			{
                Logger::Instance().logError("Port file doesn't exist");
			}

			else
			{
				port.LoadContainersFromFile(folder+SIMULATION_PORTS_FOLDER_NAME+filesList.front());
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
	for (size_t i = 0; i < ports.size(); i++) {
        Logger::Instance().setLogType("Simulation Port - " + ports[i].getPortCode());
		string outputFilePath = outputFolderPath + std::to_string(i);
		algorithm->getInstructionsForCargo(ports[i].getCargoFilePath(), outputFilePath);
		ValidateOperationsFromFile(outputFilePath);
	}
}

void Simulation::ValidateOperationsFromFile(string filePath)
{
	//ifstream file(filePath);
	//string lineFromFile;
	//vector<string> operatoinsData;

	////data members for a port
	//string portName;

	//while (getline(file, lineFromFile))
	//{

	//	/*if line is a comment - ignore*/
	//	if (isCommentLine(lineFromFile))
	//	{
	//		continue;
	//	}

	//	portData = getDataFromLine(lineFromFile, SHIPROUTE_FILE_NUM_OF_PARAMS);

	//	if (portData.size() != SHIPROUTE_FILE_NUM_OF_PARAMS)
	//	{
	//		//TODO: error message and stuff
	//	}

	//	else
	//	{
	//		//try to parse the first param to weight & create the object
	//		//TODO: validate params when creating a container
	//		try
	//		{
	//			portName = portData[0];
	//			if (Port::validateSeaPortCode(portName))
	//			{
	//				Port port(portName);
	//				route.push_back(port);
	//			}
	//			else
	//			{
	//				//TODO: throw an error that port is not valid and log it
	//			}

	//		}
	//		catch (std::invalid_argument error)
	//		{
	//			//TODO: add error to log
	//			cout << "error in ShipRoute constructor";
	//		}
	//	}
	//}

	//file.close();
}

Simulation::~Simulation() {
	delete this->ship;
	delete this->route;
}
