#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <memory>

#include "./Results.h"
#include "AlgorithmTravelPair.h"

namespace fs = std::filesystem;
using std::string;
using fs::path;
using std::vector;

// used to simulate each algorithm travel pair
// initialized with algorithm directory
class SimulationManager {
private:
    vector<AlgorithmTravelPairData> algoTravelData;
    vector<int> threadToPairData;
    // used to initialize results and errors files
    void initilizeFiles(const string& rootFolder);
    void addTravelsToResults(const string& travelDir);
    bool validateTravelsDirectory(const string& travelFolder);
    int countTotalTravels(const string& travelsDirectory);
    Results r;
public:
    SimulationManager (const string& algDir, const string& travelDir, const string& outputDir);
    void runSimulations(const string& travelDir, const string& outputDir);
    void recordResults(const string& outputDir);

};
