#pragma once
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

Simulation::Simulation(string rootFolder)
{
	folder = SIMULATION_ROOT_FOLDER;
	folder += rootFolder + FILE_SEPARATOR;
	ship = new Ship(folder+SIMULATION_SHIP_FILE_NAME);
	algorithm = new Algorithm();
	route = new ShipRoute(folder + SIMULATION_ROUTE_FILE_NAME);
}

bool Simulation::LoadContainersToPortsInRoute()
{
	map<string, list<string>> portsMap = CreatePortsCargoFromFiles();

	vector<Port>* ports = this->route->getRoute();
	
	//last port doesn't need a file, ignore it
	for (size_t i = 0; i < ports->size()-1; i++)
	{
		Port& port = (*ports)[i];
		string portCode = port.getPortCode();

		if (portsMap.find(portCode) == portsMap.end())
		{
			//TODO: log that the port doesn't have files
		}

		else
		{
			auto& filesList = portsMap.find(portCode)->second;
			if (filesList.empty())
			{
				//TODO: not enough files for port, log it
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

Simulation::~Simulation() {
	delete this->ship;
	delete this->algorithm;
	delete this->route;
}