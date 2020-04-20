#pragma once
#include "simulation.h"
#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include "util.h"

namespace fs = std::filesystem;
using std::map;
using std::stringstream;

#define FILE_SEPARATOR "/"
#define SIMULATION_ROOT_FOLDER "./Simulation"
#define SIMULATION_SHIP_FILE_NAME "sample.plan"
#define SIMULATION_ROUTE_FILE_NAME "ports"
#define SIMULATION_PORTS_FOLDER_NAME "/portsCargo"

Simulation::Simulation(string rootFolder)
{
	folder = SIMULATION_ROOT_FOLDER;
	folder += FILE_SEPARATOR + rootFolder + FILE_SEPARATOR;
	ship = new Ship(folder+SIMULATION_SHIP_FILE_NAME);
	algorithm = new Algorithm();
	route = new ShipRoute(folder + SIMULATION_ROUTE_FILE_NAME);
}

bool Simulation::LoadContainersToPortsInRoute()
{
	map<string, int> portsEncounteredMap;

	auto ports = this->route->getRoute();
	
	for (size_t i = 0; i < ports.size(); i++)
	{
		Port& port = ports[i];
		string portCode = port.getPortCode();

		if (portsEncounteredMap[portCode] == 0)
		{
			portsEncounteredMap[portCode] = 1;
		}
		cout << "this is the value: " << portsEncounteredMap[portCode] << endl;
	}

	CreatePortFilesMap();
	return true;
}

map<string, vector<int>> Simulation::CreatePortFilesMap()
{
	for (const auto& entry : fs::directory_iterator(folder+SIMULATION_PORTS_FOLDER_NAME))
		std::cout << entry.path().filename() << std::endl;

	map<string, vector<int>> mapy;
	return mapy;
}

Simulation::~Simulation() {
	delete this->ship;
	delete this->algorithm;
	delete this->route;
}