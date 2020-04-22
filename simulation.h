#ifndef SIMULATION_H
#define SIMULATION_H

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
	void PrepareAlgorithm(const string& shipPath, const string& routePath);
	bool LoadContainersToPortsInRoute();
	void PerformAlgorithmActions(const string& filePath, Port& port);
	CraneOperation* CreateOperationFromLine(const string& line);
	void ValidateAllPortCargoUnloaded(Ship* ship, Port& port);
	void LogResults();
	void LogSimulationErrors(const string& funcName, const string& error);
public:
	Simulation(const string& rootFolder, Algorithm* alg);
	static void RemoveLogFiles(const string& simulationFolder);
	void RunSimulation();
	~Simulation();
};
#endif /* SIMULATION_H */
