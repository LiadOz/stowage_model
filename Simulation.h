#ifndef SIMULATION_H
#define SIMULATION_H

#include <map>
#include <list>
#include <string>
#include <vector>
#include "algorithm.h"
#include "ship.h"
#include "CraneOperations.h"
#include "port.h"

using std::map;
using std::list;

class Simulation {
private:
	Algorithm* algorithm;
	Ship* ship;
    vector<Port> route;
	string folder; //root folder of the sim, changes per travel
	int actionsPerformedCounter = 0; //count total actions performed
	
	//will load all containers from file to the relevant port
	map<string, list<string> > CreatePortsCargoFromFiles(); 
	
	//init algorithm stuff
	void PrepareAlgorithm(const string& shipPath, const string& routePath);
	
	//will load all containers from file to the relevant port
	bool LoadContainersToPortsInRoute();

	//read file from algo and try to do the actions
	void PerformAlgorithmActions(const string& filePath, Port& port);

	//create a crane operation from the input proviced from one instruction
	CraneOperation* CreateOperationFromLine(const string& line);

	//make sure all cargo is in the port
	void ValidateAllPortCargoUnloaded(Ship* ship, Port& port);

	//log the results 
	void LogResults();

	//log simulation errors
	void LogSimulationErrors(const string& funcName, const string& error);
public:

	//constructor
	Simulation(const string& rootFolder, Algorithm* alg);

	//remove older log files before running the entire program
	static void RemoveLogFiles(const string& simulationFolder);

	//the main function for simulator, will run the sim itself
	void RunSimulation();
	~Simulation();
};
#endif /* SIMULATION_H */
