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

SimulationManager::SimulationManager(const string& algDir, const string& outputDir): outputDir(outputDir) {
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

void SimulationManager::runSimulations(const string& travelDir, int numThreads) {
    addTravelsToResults(travelDir);
    addAlgsToResults();
    r.reserveSpace();
    if (numThreads == 1)
        singleThreadedRun(travelDir);
    else {
        AlgTravelProducer producer(travelDir);
        if (numThreads < (int)std::thread::hardware_concurrency())
                numThreads = (int)std::thread::hardware_concurrency();
        ThreadPoolExecuter ex{producer, numThreads, 
            [this, travelDir](auto i, auto s){runAlgTravelPair(i, s, travelDir);}};
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

void SimulationManager::runAlgTravelPair(int algIndex, 
        const string& travel, const string& travelDir){
    auto algo = AlgorithmRegistrar::getInstance()
        .getAlgorithmByIndex(algIndex)();
    fs::path entry{travel};
    string algName = AlgorithmRegistrar::getInstance()
        .getAlgorithmName(algIndex);
    string travelName = entry.filename().string();
    int num = -1;
    try {
        LOG.setLogType(algName + "-" + travelName);
        Simulation simulation(outputDir, travelDir, travelName, algName, std::move(algo));

        num = simulation.runSimulation();
    } catch (std::runtime_error& e) {
        LOG.logError(e.what());
    } catch (std::exception& e) {
    }
    r.addResult(algName, travelName, num);
}
// Single Threaded
void SimulationManager::singleThreadedRun(const string& travelDir){
    auto& registrar = AlgorithmRegistrar::getInstance();
    for (const auto& entry : fs::directory_iterator(travelDir)) {        
        if (!entry.is_directory()) continue;
        for (auto algo_iter = registrar.begin();
                algo_iter != registrar.end(); ++algo_iter) {
            runAlgTravelPair(algo_iter - registrar.begin(),
                    entry.path(), travelDir);

        }
    }
}

void SimulationManager::recordResults() {
    r.writeToFile(outputDir + FILE_SEPARATOR + RESULTS_FILE);
}
