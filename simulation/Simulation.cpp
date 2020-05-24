#include "Simulation.h"

#include <filesystem>
#include <iostream>

#include "../interfaces/WeightBalanceCalculator.h"

#include "../common/Exceptions.h"
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

#define CRANE_INSTRUCTIONS_EXT ".crane_instructions"
#define CARGO_EXT ".cargo_data"
#define PLAN_EXT ".ship_plan"
#define ROUTE_EXT ".route"

Simulation::Simulation(const string& outputDirectory, const string& travelDirectory, const string& travelName, const string& algorithmName, unique_ptr<AbstractAlgorithm> algo) {
    folder = travelDirectory + FILE_SEPARATOR + travelName + FILE_SEPARATOR;
    try {
        string shipPath = getFileWithExt(folder, PLAN_EXT);
        string routePath = getFileWithExt(folder, ROUTE_EXT);
        string simOutputDirectory = outputDirectory + FILE_SEPARATOR + algorithmName + "_" + travelName;
        algorithm = std::move(algo);
        route = createShipRoute(routePath);
        loadContainersToPortsInRoute();
        ship.readPlan(shipPath);
        this->algName = algorithmName;
        this->outputFolder = simOutputDirectory;
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
            logSimulationErrors("loadContainersToPortsInRoute", "Port file doesn't exist");
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
                logSimulationErrors("loadContainersToPortsInRoute", "Port file doesn't exist");
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
            performAlgorithmActions(outputFilePath, port);
        } catch (const std::exception& error) {
            logSimulationErrors("runSimulation", error.what());
        }
    }

    logResults();
    return actionsPerformedCounter;
}

//read file from algo and try to do the actions
void Simulation::performAlgorithmActions(const string& filePath, Port& port) {
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
                    actionsPerformedCounter++;
                }

            } catch (const std::exception& error) {
                logSimulationErrors("performAlgorithmActions", error.what());
            }
        }
    }

    validateAllPortCargoUnloaded(this->ship, port);

    file.close();
}

//make sure all cargo is in the port
void Simulation::validateAllPortCargoUnloaded(Ship& ship, Port& port) {
    string portID = port.getPortCode();
    vector<Container> shipContainers = ship.getShipContainers();

    for (size_t i = 0; i < shipContainers.size(); i++) {
        if (shipContainers[i].getDestination() == portID) {
            logSimulationErrors("validateAllPortCargoUnloaded", "container " + shipContainers[i].getId() + " didn't unload at port " + portID);
        }
    }
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

    return std::move(craneOperation);
}

void Simulation::logResults() {
    ofstream file;
    file.open(folder + SIMULATION_RESULTS_FILE_NAME, std::ios::app);
    file << "algorithm " << algName << " has performed " << actionsPerformedCounter << " actions." << endl;
    file << "the ship successfully delivered " << ship.getTotalCorrectUnloads() << " cargos. " << endl;
    file.close();
}

void Simulation::logSimulationErrors(const string& funcName, const string& error) {
    LOG.logError("function " + funcName + ": " + error);
}

Simulation::~Simulation() {
}