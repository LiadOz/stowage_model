#pragma once
#include <map>
#include <list>
#include <string>
#include <vector>
#include "algorithm.h"
#include "ship.h"
#include "calculator.h"

using std::map;
using std::list;

class Simulation {
private:
	Algorithm* algorithm;
	Ship* ship;
	ShipRoute* route;
	string folder;
	map<string, list<string> > CreatePortsCargoFromFiles();
	void PrepareAlgorithm(string shipPath, string routePath);
	bool LoadContainersToPortsInRoute();
	void ValidateOperationsFromFile(string filePath);
public:
	Simulation(string rootFolder, Algorithm* alg);
	void RunSimulation();
	~Simulation();
};