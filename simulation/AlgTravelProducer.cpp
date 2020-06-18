#include "./AlgTravelProducer.h"

#include <filesystem>

#include "./AlgorithmRegistrar.h"
#include "./Simulation.h"
#include "../common/Util.h"
#include "../common/Logger.h"


namespace fs = std::filesystem;

AlgTravelProducer::AlgTravelProducer (const string& directory): travelDir(directory) {
    int pairsIndexCounter = 0;

    auto& registrar = AlgorithmRegistrar::getInstance();
    for (const auto& entry : fs::directory_iterator(travelDir)) {        

        if (!entry.is_directory()) continue;
        for (auto algo_iter = registrar.begin();
                algo_iter != registrar.end(); ++algo_iter) {
            string algName =
                registrar.getAlgorithmName(algo_iter - registrar.begin());
            auto algo = (*algo_iter)();
            pairs.push_back({algo_iter - registrar.begin(), entry.path()});
            pairsIndexCounter++;
        }
    }
    numTasks = pairs.size();
}
std::optional<int> AlgTravelProducer::next_task_index() {
    for(int curr_counter = task_counter.load(); curr_counter < numTasks; ) {
        if(task_counter.compare_exchange_weak(curr_counter, curr_counter + 1)) {
            return {curr_counter}; // zero based
        }
    }
    return {};
}

/*
void AlgTravelProducer::simulationStart(int task_index){
    auto p = pairs[task_index];
    auto algo = AlgorithmRegistrar::getInstance()
        .getAlgorithmByIndex(p.first)();
    fs::path entry{p.second};
    string algName = AlgorithmRegistrar::getInstance()
        .getAlgorithmName(p.first);
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
*/

std::optional<pair<int, string>> AlgTravelProducer::getTask() {
    auto task_index = next_task_index(); // or: next_task_index_simple();
    if(task_index) {
        return {pairs[task_index.value()]};
    }
    else return {};
}

