#pragma once
#include <map>
#include <list>
#include <string>
#include <vector>
#include "algorithm.h"
#include "ship.h"
#include "calculator.h"
#include "CraneOperations.h"
#include "Port.h"

using std::map;
using std::list;

class Simulation {
private:
	Algorithm* algorithm;
	Ship* ship;
	ShipRoute* route;
	string folder;
	int actionsPerformedCounter;
	map<string, list<string> > CreatePortsCargoFromFiles();
	void PrepareAlgorithm(string shipPath, string routePath);
	bool LoadContainersToPortsInRoute();
	void PerformAlgorithmActions(string filePath, Port& port);
	CraneOperation* CreateOperationFromLine(string line);
	void ValidateAllPortCargoUnloaded(Ship* ship, Port& port);
public:
	Simulation(string rootFolder, Algorithm* alg);
	void RunSimulation();
	~Simulation();
};