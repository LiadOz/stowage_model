#pragma once
#include <map>
#include <list>
#include <string>
#include <vector>
#include "algorithm.h"
#include "ship.h"

using std::map;
using std::list;

class Simulation {
private:
	Algorithm* algorithm;
	Ship* ship;
	ShipRoute* route;
	string folder;
	map<string, list<string> > CreatePortsCargoFromFiles();
public:
	Simulation(string rootFolder);
	bool LoadContainersToPortsInRoute();
	~Simulation();
};