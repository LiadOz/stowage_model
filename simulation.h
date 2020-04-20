#pragma once
#include "algorithm.h"
#include "ship.h"
#include <map>
#include <string>
#include <vector>

using std::map;

class Simulation {
private:
	Algorithm* algorithm;
	Ship* ship;
	ShipRoute* route;
	string folder;
	map<string, vector<int>> CreatePortFilesMap();
public:
	Simulation(string rootFolder);
	bool LoadContainersToPortsInRoute();
	~Simulation();
};