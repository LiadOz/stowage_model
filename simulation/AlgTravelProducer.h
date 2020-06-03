#pragma once

#include <atomic>
#include <optional>
#include <functional>
#include <string>
#include <vector>

#include "./AlgorithmTravelPair.h"

using std::vector;
using std::string;

class AlgTravelProducer {
private:
    string travelDir;
    string outputDir;
    int numTasks;
    vector<AlgorithmTravelPair> pairs;
    std::atomic_int task_counter = 0;
    std::optional<int> next_task_index();

public:
    // creating the pairs and doing some preprocessing
    AlgTravelProducer (const string& directory, const string& outputDir);

    std::optional<std::function<void(void)>> getTask();
};
