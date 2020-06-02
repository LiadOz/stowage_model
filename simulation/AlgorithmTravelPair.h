#pragma once

#include <memory>
#include <string>

#include "../interfaces/AbstractAlgorithm.h"

class AlgorithmTravelPair {
private:
    std::unique_ptr<AbstractAlgorithm> algorithm;
    const string travelPath;

public:
    AlgorithmTravelPair(std::unique_ptr<AbstractAlgorithm> algo, const string &path) {
        algorithm = std::move(algo);
        travelPath = path;
    }

    std::unique_ptr<AbstractAlgorithm> getAlgorithm() {
        return algorithm;
    }

    const string &getTravelPath() {
        return travelpath;
    }
}