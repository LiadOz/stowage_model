#include "Results.h"

#include <fstream>
#include <iostream>
#include <algorithm>

void Results::addTravel(const string& travelName){
    if (travelMapping.find(travelName) == travelMapping.end())
        travelMapping.insert({travelName, travelMapping.size()});
}

void Results::sortResults(){
    std::sort(algResults.begin(), algResults.end(),
            [](auto& r1, auto& r2){
            if (r1.second.back() == r2.second.back())
                return r1.second.end()[-2] < r2.second.end()[-2];
            return r1.second.back() < r2.second.back(); });
}

void Results::sumResults(){
    for (auto& algP : algResults) {
        int errors = 0;
        int sum = 0;
        for (int x : algP.second) {
            if(x != -1) sum+=x;
            else errors++;
        }
        algP.second.push_back(sum);
        algP.second.push_back(errors);
    }
}
void Results::writeToFile(const string& outputFile){
    remove(outputFile.c_str());
    std::ofstream file(outputFile);
    sumResults();
    sortResults();
    file << "Results";
    for (auto& x : travels) {
        file << "," << x;
    }
    file << ",Sum,Num Errors" << std::endl;
    for (auto& alg : algResults) {
        file << alg.first; 
        for (auto i : alg.second) {
            file << "," << i;
        }
        file << std::endl;
    }
}
