#pragma once

#include <string>
#include <filesystem>
#include <memory>

#include "./Results.h"

namespace fs = std::filesystem;
using std::string;
using fs::path;
// used to simulate each algorithm travel pair
// initialized with algorithm directory
class SimulationManager {
private:
    // used to initialize results and errors files
    void initilizeFiles(const string& rootFolder);
    void addTravelsToResults(const string& travelDir);
    Results r;
public:
    SimulationManager (const string& algDir, const string& outputDir);
    void runSimulations(const string& travelDir, const string& outputDir);
    void recordResults(const string& outputDir);

};
