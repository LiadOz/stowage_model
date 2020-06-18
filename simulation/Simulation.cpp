#include "Simulation.h"

#include <filesystem>
#include <iostream>

#include "../common/Exceptions.h"
#include "../common/Logger.h"
#include "../common/Util.h"

namespace fs = std::filesystem;

using std::endl;
using std::map;
using std::stringstream;

#define FILE_SEPARATOR "/"
#define SIMULATION_ROOT_FOLDER "./Simulation/"
#define SIMULATION_SHIP_FILE_NAME "sample.plan"
#define SIMULATION_ROUTE_FILE_NAME "ports"
#define SIMULATION_CARGO_INSTRUCTIONS_FOLDER "Instructions/"
#define SIMULATION_ERROR_FILE_NAME "errors.txt"
#define SIMULATION_RESULTS_FILE_NAME "results.txt"

Simulation::Simulation(const string& outputDirectory, const string& travelDirectory, const string& travelName, const string& algorithmName, unique_ptr<AbstractAlgorithm> algo) {
    folder = travelDirectory + FILE_SEPARATOR + travelName + FILE_SEPARATOR;
    try {
        getRouteFromStore(folder);
        string shipPath = getFileWithExt(folder, PLAN_EXT);
        string routePath = getFileWithExt(folder, ROUTE_EXT);
        string simOutputDirectory = outputDirectory + FILE_SEPARATOR + algorithmName + "_" + travelName;
        algorithm = std::move(algo);
        route = createShipRoute(routePath);
        loadContainersToPortsInRoute();
        ship.readPlan(shipPath);
        this->algName = algorithmName;
        this->outputFolder = simOutputDirectory;
        wbCalculator = WeightBalanceCalculator();
        wbCalculator.readShipPlan("ain't_nobody_got_time_for_that");
        prepareAlgorithm(shipPath, routePath, simOutputDirectory);
    }

    catch (const FatalError& ferror) {
        throw ferror;
    }
}

//init algorithm stuff
void Simulation::prepareAlgorithm(const string& shipPath, const string& routePath, const string& outputDirectory) {
    algorithm->readShipPlan(shipPath);
    algorithm->readShipRoute(routePath);
    fs::create_directory(outputDirectory);
}

//remove older log files before running the entire program
void Simulation::removeLogFiles(const string& simulationFolder) {
    string errorsFile = simulationFolder + FILE_SEPARATOR + SIMULATION_ERROR_FILE_NAME;
    string resultsFile = simulationFolder + FILE_SEPARATOR + SIMULATION_RESULTS_FILE_NAME;

    remove(errorsFile.c_str());
    remove(resultsFile.c_str());
}

//will load all containers from file to the relevant port
bool Simulation::loadContainersToPortsInRoute() {
    map<string, list<string>> portsMap = createPortsCargoFromFiles();
    map<string, int> portsEncountermentsMap;
    vector<Port>& ports = this->route;

    //last port doesn't need a file, ignore it
    for (size_t i = 0; i < ports.size() - 1; i++) {
        Port& port = ports[i];
        string portCode = port.getPortCode();

        //count how many times we've visited each port so we can get the currect file
        if (portsEncountermentsMap.find(portCode) == portsEncountermentsMap.end()) {
            portsEncountermentsMap.insert(std::make_pair(portCode, 1));
        } else {
            int numOfTimes = portsEncountermentsMap.find(portCode)->second;
            portsEncountermentsMap.find(portCode)->second = numOfTimes + 1;
        }

        //check if port doesn't exist
        if (portsMap.find(portCode) == portsMap.end()) {
            // logSimulationErrors("loadContainersToPortsInRoute", "Port file doesn't exist");
        }

        else {
            auto& filesList = portsMap.find(portCode)->second;
            bool foundFile = false;

            for (string file : filesList) {
                if (file == portCode + '_' + std::to_string(portsEncountermentsMap.find(portCode)->second) + string(CARGO_EXT)) {
                    port.loadContainersFromFile(folder + file);
                    foundFile = true;
                }
            }

            //check if port doesn't exist
            if (!foundFile) {
                //no need for an error if file is not found: instead it is treated as an empty file.
                //logSimulationErrors("loadContainersToPortsInRoute", "Port file doesn't exist");
            }
        }
    }

    return true;
}

//helper function for loadContainersToPortsInRoute
map<string, list<string>> Simulation::createPortsCargoFromFiles() {
    map<string, list<string>> map;

    for (const auto& entry : fs::directory_iterator(folder)) {
        string fileName = entry.path().filename().string();

        if (validCargoFile(fileName)) {
            string portCode = fileName.substr(0, 5);

            //port is not in the map yet
            if (map.find(portCode) == map.end()) {
                list<string> list;
                map.insert(std::make_pair(portCode, list));
            }

            //add file to map
            map.find(portCode)->second.push_back(fileName);
        }
    }

    return map;
}

//the main function for simulator, will run the sim itself
int Simulation::runSimulation() {
    vector<Port>& ports = this->route;
    vector<Port> nextPortsToVisit = this->route;

    map<string, int> portsEncountermentsMap;

    //go through all the ports and do actions there
    for (size_t i = 0; i < ports.size(); i++) {
        try {
            Port& port = ports[i];
            string portCode = port.getPortCode();

            //count how many times we've visited each port so we can get the currect file
            if (portsEncountermentsMap.find(portCode) == portsEncountermentsMap.end()) {
                portsEncountermentsMap.insert(std::make_pair(portCode, 1));
            } else {
                int numOfTimes = portsEncountermentsMap.find(portCode)->second;
                portsEncountermentsMap.find(portCode)->second = numOfTimes + 1;
            }

            string instructionsFileName = portCode + '_' + std::to_string(portsEncountermentsMap.find(portCode)->second) + string(CRANE_INSTRUCTIONS_EXT);

            string outputFilePath = this->outputFolder + "/" + instructionsFileName;
            algorithm->getInstructionsForCargo(port.getCargoFilePath(), outputFilePath);

            if (!fs::exists(outputFilePath)) {
                throw FatalError("Algorithm didn't create cargo file for port " + port.getPortCode() + "(number " + std::to_string(i) + ")");
            }

            performAlgorithmActions(outputFilePath, port, i);
        } catch (const FatalError& error) {
            logSimulationErrors("runSimulation", error.what());
            return -1;
        } catch (const std::exception& error) {
            logSimulationErrors("runSimulation", error.what());
        }
    }

    logResults();
    return actionsPerformedCounter;
}

//read file from algo and try to do the actions
void Simulation::performAlgorithmActions(const string& filePath, Port& port, int routePortIndex) {
    std::ifstream file(filePath);
    string lineFromFile;

    while (getline(file, lineFromFile)) {
        /*if line is a comment - ignore*/
        if (isCommentLine(lineFromFile)) {
            continue;
        }

        unique_ptr<CraneOperation> craneOperation = createOperationFromLine(lineFromFile);

        //check that craneOperation is valid

        if (craneOperation == NULL) {
            logSimulationErrors("performAlgorithmActions", "craneOperation is null");
        }

        //operation format is valid
        else {
            try {
                craneOperation->doOperation(ship, port);

                if (craneOperation->getOperation() != Operations::reject) {
                    actionsPerformedCounter += craneOperation->getCost();
                }
            } catch (const std::runtime_error& error) {
                logSimulationErrors("performAlgorithmActions", error.what());
            } catch (const std::exception& error) {
                logSimulationErrors("performAlgorithmActions", error.what());
            }
        }
    }

    //if failed validating either function (cargo that could be loaded + had dest in the route
    //or failed to unload all cargo for current port) it's a fatal error - return -1.
    if (!validateAllPortCargoUnloaded(this->ship, port)) {
        throw FatalError("validateAllPortCargoUnloaded failed");
    }
    if (!validateAllShipCargoLoaded(this->ship, port, routePortIndex + 1)) {
        throw FatalError("validateAllShipCargoLoaded failed");
    }

    file.close();
}

//make sure all cargo is in the port
bool Simulation::validateAllPortCargoUnloaded(Ship& ship, Port& port) {
    string portID = port.getPortCode();
    vector<Container> shipContainers = ship.getShipContainers();

    for (size_t i = 0; i < shipContainers.size(); i++) {
        if (shipContainers[i].getDestination() == portID) {
            logSimulationErrors("validateAllPortCargoUnloaded", "container " + shipContainers[i].getId() + " didn't unload at port " + portID);
            return false;
        }
    }
    return true;
}

bool Simulation::validateAllShipCargoLoaded(Ship& ship, Port& port, int routePortIndex) {
    string portID = port.getPortCode();
    const vector<Container>& cargoInPort = port.getCargoList();

    //if there is free space
    if (ship.freeSpaces() != 0) {
        //go through all the containers left in the port
        for (size_t i = 0; i < cargoInPort.size(); i++) {
            bool containerHasPortInRoute = false;
            const Container& cargo = cargoInPort[i];
            if (cargo.getDestination() == portID) continue;

            //go through all the next ports in route
            for (; routePortIndex < (int)this->route.size(); routePortIndex++) {
                if (cargo.getDestination() == this->route[routePortIndex].getPortCode()) {
                    containerHasPortInRoute = true;
                    break;
                }
            }

            //if container has route ahead and wasn't loaded (there is free space), log error
            if (containerHasPortInRoute) {
                logSimulationErrors("validateAllShipCargoLoaded", "container " + cargo.getId() + " wasn't loaded into ship, and was left at port " + portID);
                return false;
            }
        }
    }

    return true;
}

//create a crane operation from the input proviced from one instruction
unique_ptr<CraneOperation> Simulation::createOperationFromLine(const string& lineFromFile) {
    vector<string> operationsData;
    unique_ptr<CraneOperation> craneOperation = NULL;

    //get data from line, params may vary
    operationsData = getDataFromLine(lineFromFile, CRANE_OPERATIONS_FILE_MAX_NUM_OF_PARAMS, true);

    //peak at the (supposed) type of action
    string operationString = operationsData.size() ? operationsData[0] : "";
    Operations operation = CraneOperation::getOperationType(operationString);

    /*after determining the type of the operation, create the operation*/
    try {
        switch (operation) {
            case Operations::load:
                craneOperation = std::make_unique<LoadCraneOperation>(operationsData);
                break;
            case Operations::unload:
                craneOperation = std::make_unique<UnloadCraneOperation>(operationsData);
                break;
            case Operations::move:
                craneOperation = std::make_unique<MoveCraneOperation>(operationsData);
                break;
            case Operations::reject:
                craneOperation = std::make_unique<RejectCraneOperation>(operationsData);
                break;
            default:
                logSimulationErrors("createOperationFromLine", "invalid operation enum type");
                break;
        }
    } catch (const std::exception& error) {
        logSimulationErrors("createOperationFromLine", error.what());
        std::cerr << error.what();
    }

    return craneOperation;
}

void Simulation::logResults() {
    // currently does nothing
}

void Simulation::logSimulationErrors(const string& funcName, const string& error) {
    LOG.logError("function " + funcName + ": " + error);
}

Simulation::~Simulation() {
}
