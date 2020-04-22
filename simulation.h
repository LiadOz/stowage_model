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
	static int totalUnloadsInCorrectPort;
	map<string, list<string> > CreatePortsCargoFromFiles();
	void PrepareAlgorithm(string shipPath, string routePath);
	bool LoadContainersToPortsInRoute();
	void PerformAlgorithmActions(string filePath, Port& port);
	CraneOperation* CreateOperationFromLine(string line);
	void ValidateAllPortCargoUnloaded(Ship* ship, Port& port);
	void LogResults();
	void LogSimulationErrors(string funcName, string error);
public:
	Simulation(string rootFolder, Algorithm* alg);
	static void RemoveLogFiles(string simulationFolder);
	void RunSimulation();
	~Simulation();
};
