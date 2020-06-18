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

// creates pairs of algorithm and travel
class AlgTravelProducer {
private:
    string travelDir;
    int numTasks;
    vector<pair<int, string>> pairs;
    std::atomic_int task_counter = 0;
    std::optional<int> next_task_index();

public:
    // creating the pairs and doing some preprocessing
    AlgTravelProducer (const string& directory);

    std::optional<pair<int, string>> getTask();

    //void simulationStart(int task_index);
};
