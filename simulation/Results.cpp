#include "Results.h"

#include <fstream>
#include <iostream>
#include <algorithm>

void Results::addTravel(const string& travelName){
    if (travelMapping.find(travelName) == travelMapping.end()){
        travels.push_back(travelName);
        travelMapping.insert({travelName, travelMapping.size()});
    }
}
void Results::addAlg(const string& algName){
    if (algMapping.find(algName) == algMapping.end()){
        algs.push_back(algName);
        algMapping.insert({algName, algMapping.size()});
    }
}

void Results::reserveSpace(){
    algResults = vector<vector<int>>(algs.size(), vector<int>(travels.size(), 0));
}

void Results::addResult(const string& algName, const string& travelName, int x){
    algResults[algMapping[algName]][travelMapping[travelName]] = x;
}

void Results::sortResults(){
    std::sort(algs.begin(), algs.end(),[this](auto& a, auto& b) {
            int i = algMapping[a], j = algMapping[b];
            if (algResults[i].back() == algResults[j].back())
                return algResults[i].end()[-2] < algResults[j].end()[-2];
            return algResults[i].back() < algResults[j].back();
            });
    std::sort(algResults.begin(), algResults.end(),
            [](auto& r1, auto& r2){
            if (r1.back() == r2.back())
                return r1.end()[-2] < r2.end()[-2];
            return r1.back() < r2.back(); });
}

void Results::sumResults(){
    for (auto& algP : algResults) {
        int errors = 0;
        int sum = 0;
        for (int x : algP) {
            if(x != -1) sum+=x;
            else errors++;
        }
        algP.push_back(sum);
        algP.push_back(errors);
    }
}
void Results::writeToFile(const string& outputFile){
    remove(outputFile.c_str());
    std::ofstream file(outputFile);
    sumResults();
    sortResults();
    file << "RESULTS";
    for (auto& x : travels) {
        file << "," << x;
    }
    file << ",Sum,Num Errors" << std::endl;
    for (int i = 0; i < (int)algs.size(); ++i) {
        file << algs[i];
        for (int x : algResults[i]) {
           file << "," << x;
        }
        file << std::endl;
    }
}
