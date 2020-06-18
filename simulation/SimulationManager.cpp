#include "./SimulationManager.h"

#include <thread>

#include "./AlgTravelProducer.h"
#include "./AlgorithmRegistrar.h"
#include "./Simulation.h"
#include "./ThreadPoolExecuter.h"

#include "./../common/Util.h"
#include "./../common/Logger.h"


void SimulationManager::initilizeFiles(const string& rootFolder) {
    remove((rootFolder + FILE_SEPARATOR + LOG_FILE).c_str());
    remove((rootFolder + FILE_SEPARATOR + RESULTS_FILE).c_str());

    LOG.setFile(rootFolder + FILE_SEPARATOR + LOG_FILE);
    LOG.setLogType("General Errors");
}

SimulationManager::SimulationManager(const string& algDir, const string& outputDir) {
    initilizeFiles(outputDir);
    // registring the algs
    auto& registrar = AlgorithmRegistrar::getInstance();
    int totalAlgoRegistered = 0;
    for (const auto& entry : fs::directory_iterator(algDir)) {
        if (entry.path().filename().extension() == DYNAMIC_FILE_EXTENSION) {
            string error;
            if (!registrar.loadAlgorithmFromFile(entry.path().string(), error)) {
                LOG.logError(error);
            } else {
                //count how many algorithms we've registered
                totalAlgoRegistered++;
            }
        }
    }
}

void SimulationManager::addTravelsToResults(const string& travelDir) {
    for (const auto& entry : fs::directory_iterator(travelDir))
        if (entry.is_directory()) r.addTravel(entry.path().filename().string());
}
void SimulationManager::addAlgsToResults(){
    auto& registrar = AlgorithmRegistrar::getInstance();
    for (auto algo_iter = registrar.begin();
            algo_iter != registrar.end(); ++algo_iter) {
        r.addAlg(registrar.getAlgorithmName(algo_iter - registrar.begin()));
    }
}

void SimulationManager::runSimulations(const string& travelDir, const string& outputDir, int numThreads) {
    addTravelsToResults(travelDir);
    addAlgsToResults();
    r.reserveSpace();
    if (numThreads == 1)
        singleThreadedRun(outputDir, travelDir);
    else {
        AlgTravelProducer producer(travelDir, outputDir, r);
        if (numThreads < (int)std::thread::hardware_concurrency())
                numThreads = (int)std::thread::hardware_concurrency();
        ThreadPoolExecuter ex{producer, numThreads};
        ex.start();
        ex.wait_till_finish();
    }
}

int SimulationManager::countTotalTravels(const string& travelsDirectory) {
    int counter = 0;

    for (const auto& entry : fs::directory_iterator(travelsDirectory)) {
        if (entry.is_directory()) {
            if (validateTravelsDirectory(entry.path())) {
                counter++;
            }
        }
    }

    return counter;
}

bool SimulationManager::validateTravelsDirectory(const string& travelFolder) {
    int routeEXT = 0;
    int shipPlanEXT = 0;

    for (const auto& entry : fs::directory_iterator(travelFolder)) {
        string ext = entry.path().filename().extension();
        if (ext == PLAN_EXT) {
            shipPlanEXT++;
        } else if (ext == ROUTE_EXT) {
            routeEXT++;
        }
        //ignore other files, so no more checks
    }

    return (routeEXT == 1 && shipPlanEXT == 1);
}

// Single Threaded
void SimulationManager::singleThreadedRun(const string& outputDir, const string& travelDir){
    auto& registrar = AlgorithmRegistrar::getInstance();
    for (const auto& entry : fs::directory_iterator(travelDir)) {        
        if (!entry.is_directory()) continue;
        for (auto algo_iter = registrar.begin();
                algo_iter != registrar.end(); ++algo_iter) {
            string algName =
                registrar.getAlgorithmName(algo_iter - registrar.begin());
            auto algo = (*algo_iter)();
            int moves = -1;
            string travelName = entry.path().filename().string();
            try {
                LOG.setLogType(algName + "-" + travelName);
                Simulation simulation(outputDir, travelDir, travelName, algName, std::move(algo));

                moves = simulation.runSimulation();
            } catch (std::runtime_error& e) {
                LOG.logError(e.what());
            } catch (std::exception& e) {
            }
            r.addResult(algName, travelName, moves);
        }
    }
}

void SimulationManager::recordResults(const string& outputDir) {
    r.writeToFile(outputDir + FILE_SEPARATOR + RESULTS_FILE);
}
