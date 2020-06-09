#pragma once

#include <memory>
#include <string>

#include "../interfaces/AbstractAlgorithm.h"

using std::string;
class AlgorithmTravelPair {
private:
    
    std::unique_ptr<AbstractAlgorithm> algorithm;
    const string travelPath;
    const string algName;
    const int writeLocation;

public:
    AlgorithmTravelPair(std::unique_ptr<AbstractAlgorithm> algo, const string &path, const string& algName, const int writeLocation)
     : travelPath(path), algName(algName), writeLocation(writeLocation){
        algorithm = std::move(algo);
    }

    std::unique_ptr<AbstractAlgorithm> getAlgorithm() {
        return std::move(algorithm);
    }

    const string &getTravelPath() {
        return travelPath;
    }
    const string& getAlgorithmName(){
        return algName;
    }
};

struct AlgorithmTravelPairData {
    string errors;
    int actionsPerformed;
};