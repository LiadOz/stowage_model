#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <memory>
#include <thread>
#include <atomic>

#include "./AlgTravelProducer.h"
#include "./Results.h"

namespace fs = std::filesystem;
using std::string;
using fs::path;
using std::vector;
using std::atomic_int;
using std::atomic_bool;

#define LOG_FILE "simulation.errors"
#define RESULTS_FILE "simulation.results"
#define FILE_SEPARATOR "/"
#define DYNAMIC_FILE_EXTENSION ".so"

#define SIMULATION_ERROR_RESULT -1

// used to simulate each algorithm travel pair
// initialized with algorithm directory
class SimulationManager {
private:
    // used to initialize results and errors files
    void initilizeFiles(const string& rootFolder);
    void addTravelsToResults(const string& travelDir);
    void addAlgsToResults();
    bool validateTravelsDirectory(const string& travelFolder);
    int countTotalTravels(const string& travelsDirectory);

    // runs a pair of algorithm and travel
    void runAlgTravelPair(int algIndex, 
            const string& travel, const string& travelDir);
    Results r;
    string outputDir;

public:
    SimulationManager (const string& algDir, const string& outputDir);
    void runSimulations(const string& travelDir, int numThreads);
    void singleThreadedRun(const string& travelDir);
    void recordResults();

};
