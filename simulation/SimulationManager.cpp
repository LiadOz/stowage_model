#include "./SimulationManager.h"

#include "./../common/Util.h"
#include "./AlgorithmRegistrar.h"
#include "./Simulation.h"

#include "./ThreadPoolExecuter.h"
#include "./AlgTravelProducer.h"

#define LOG_FILE "simulation.errors"
#define RESULTS_FILE "simulation.results"
#define FILE_SEPARATOR "/"
#define DYNAMIC_FILE_EXTENSION ".so"

#define SIMULATION_ERROR_RESULT -1

void SimulationManager::initilizeFiles(const string& rootFolder){
    remove((rootFolder + FILE_SEPARATOR + LOG_FILE).c_str());
    remove((rootFolder + FILE_SEPARATOR + RESULTS_FILE).c_str());

    LOG.setFile(rootFolder + FILE_SEPARATOR + LOG_FILE);
    LOG.setLogType("General Errors");
}

SimulationManager::SimulationManager(const string& algDir, const string& outputDir){
    initilizeFiles(outputDir);
    // registring the algs
    auto& registrar = AlgorithmRegistrar::getInstance();
    for (const auto& entry : fs::directory_iterator(algDir)) {
        if (entry.path().filename().extension() == DYNAMIC_FILE_EXTENSION) {
            string error;
            if (!registrar.loadAlgorithmFromFile(entry.path().string(), error)) {
                LOG.logError(error);
            }
        }
    }
}

void SimulationManager::addTravelsToResults(const string& travelDir){
    for (const auto& entry : fs::directory_iterator(travelDir))
        if (entry.is_directory()) r.addTravel(entry.path().filename().string());
}

void SimulationManager::runSimulations(const string& travelDir, const string& outputDir){
    AlgTravelProducer producer(travelDir, outputDir);
    // TODO : determine number of threads
    ThreadPoolExecuter ex {producer, 1};
    ex.start();
    ex.wait_till_finish();
}
/* Single Threaded
void SimulationManager::runSimulations(const string& travelDir, const string& outputDir){
    auto& registrar = AlgorithmRegistrar::getInstance();
    addTravelsToResults(travelDir);

    // iterating over the algs
    for (auto algo_iter = registrar.begin();
         algo_iter != registrar.end(); ++algo_iter) {
        string algName =
            registrar.getAlgorithmName(algo_iter - registrar.begin());

        r.startRecordingAlg(algName);

        for (const auto& entry : fs::directory_iterator(travelDir)) {
            if (!entry.is_directory()) continue;

            // setting the logger
            LOG.setLogType(algName + " " + entry.path().filename().string());
            std::unique_ptr<AbstractAlgorithm> algo = (*algo_iter)();
            try {
                string travelName = entry.path().filename().string();
                Simulation simulation(outputDir, travelDir, travelName, algName, std::move(algo));

                int num = simulation.runSimulation();
                r.addAlgResult(num);
            } catch (std::exception& e) {
                LOG.logError(e.what());
                r.addAlgResult(SIMULATION_ERROR_RESULT);
            }
        }
    }
}
*/

void SimulationManager::recordResults(const string& outputDir){
    r.writeToFile(outputDir + FILE_SEPARATOR + RESULTS_FILE);
}
