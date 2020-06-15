#include "./AlgTravelProducer.h"

#include <filesystem>

#include "./AlgorithmRegistrar.h"
#include "./Simulation.h"
#include "../common/Util.h"
#include "../common/Logger.h"


namespace fs = std::filesystem;

AlgTravelProducer::AlgTravelProducer (const string& directory, const string& outputDir, Results& results): travelDir(directory), outputDir(outputDir), r(results) {
    // TODO : add preprocessing

    int pairsIndexCounter = 0;

    auto& registrar = AlgorithmRegistrar::getInstance();
    for (const auto& entry : fs::directory_iterator(travelDir)) {        

        //TODO: change to validate travel directory? (there is a function already)
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

void AlgTravelProducer::simulationStart(int task_index){
    auto p = pairs[task_index];
    auto algo = AlgorithmRegistrar::getInstance()
        .getAlgorithmByIndex(p.first)();
    fs::path entry{p.second};
    string algName = AlgorithmRegistrar::getInstance()
        .getAlgorithmName(p.first);
    try {
        string travelName = entry.filename().string();
        LOG.setLogType(algName + "-" + travelName);
        Simulation simulation(outputDir, travelDir, travelName, algName, std::move(algo));

        int num = simulation.runSimulation();
        r.addResult(algName, travelName, num);
    } catch (std::exception& e) {
        LOG.logError(e.what());
    }
}

std::optional<std::function<void(void)>> AlgTravelProducer::getTask() {
    auto task_index = next_task_index(); // or: next_task_index_simple();
    if(task_index) {
        return [task_index, this]{
            simulationStart(task_index.value());
        };
    }
    else return {};
}

