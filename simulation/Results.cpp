#include "Results.h"

#include <iostream>
#include <algorithm>
void Results::writeToFile(const string& outputFile){
    std::cout << outputFile << std::endl;
    std::cout << "Results,";
    for (auto& x : travels) {
        std::cout << x ;
    }
    std::cout << std::endl;
    std::sort(algResults.begin(), algResults.end(),
            [this](auto& r1, auto& r2){
            return r1.second.back() > r2.second.back(); });
    for (auto& alg : algResults) {
        std::cout << alg.first; 
        for (auto i : alg.second) {
            std::cout << "," << i;
        }
        std::cout << std::endl;
    }
}
