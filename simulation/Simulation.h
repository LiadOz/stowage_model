#pragma once

#include <map>
#include <list>
#include <string>
#include <vector>
#include <memory>

#include "../common/Ship.h"
#include "../interfaces/AbstractAlgorithm.h"
#include "CraneOperations.h"
#include "Port.h"

using std::map;
using std::list;
using std::unique_ptr;

// simulates an algorithm travel pair
class Simulation {
private:
	Ship ship;
    string algName;
    unique_ptr<AbstractAlgorithm> algorithm;
    vector<Port> route;
	string folder; //root folder of the sim, changes per travel
	int actionsPerformedCounter = 0; //count total actions performed
	
	//will load all containers from file to the relevant port
	map<string, list<string> > createPortsCargoFromFiles(); 
	
	//init algorithm stuff
	void prepareAlgorithm(const string& shipPath, const string& routePath);
	
	//will load all containers from file to the relevant port
	bool loadContainersToPortsInRoute();

	//read file from algo and try to do the actions
	void performAlgorithmActions(const string& filePath, Port& port);

	//create a crane operation from the input proviced from one instruction
	CraneOperation* createOperationFromLine(const string& line);

	//make sure all cargo is in the port
	void validateAllPortCargoUnloaded(Ship& ship, Port& port);

	//log the results 
	void logResults();

	//log simulation errors
	void logSimulationErrors(const string& funcName, const string& error);

public:
	//constructor
	Simulation(const string& travelFolder, unique_ptr<AbstractAlgorithm> alg, const string& algName);

	//remove older log files before running the entire program
	static void removeLogFiles(const string& simulationFolder);

	//the main function for simulator, will run the sim itself
	void runSimulation();
	~Simulation();
};
