#pragma once

#include <atomic>
#include <optional>
#include <functional>
#include <string>
#include <vector>

#include "./Results.h"

using std::vector;
using std::string;
using std::pair;

class AlgTravelProducer {
private:
    string travelDir;
    string outputDir;
    Results& r;
    int numTasks;
    vector<pair<int, string>> pairs;
    std::atomic_int task_counter = 0;
    std::optional<int> next_task_index();

public:
    // creating the pairs and doing some preprocessing
    AlgTravelProducer (const string& directory, const string& outputDir,
            Results& results);

    std::optional<std::function<void(void)>> getTask();

    void simulationStart(int task_index);
};
