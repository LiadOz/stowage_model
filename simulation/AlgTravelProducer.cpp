#include "./AlgTravelProducer.h"

#include <filesystem>

#include "../common/Util.h"
#include "./AlgorithmRegistrar.h"
#include "./Simulation.h"


namespace fs = std::filesystem;

AlgTravelProducer::AlgTravelProducer (const string& directory, const string& outputDir): travelDir(directory), outputDir(outputDir) {
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
            pairs.push_back({std::move(algo), entry.path(), algName, pairsIndexCounter});
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

std::optional<std::function<void(void)>> AlgTravelProducer::getTask() {
    auto task_index = next_task_index(); // or: next_task_index_simple();
    if(task_index) {
        return [task_index, this]{
            AlgorithmTravelPair& p = pairs[task_index.value()];
            auto algo = p.getAlgorithm();
            fs::path entry{p.getTravelPath()};
            string algName = p.getAlgorithmName();
            try {
                string travelName = entry.filename().string();
                Simulation simulation(outputDir, travelDir, travelName, algName, std::move(algo));

                // TODO : int num = simulation.runSimulation();
                simulation.runSimulation();
            } catch (std::exception& e) {
                LOG.logError(e.what());
            }
        };
    }
    else return {};
}


