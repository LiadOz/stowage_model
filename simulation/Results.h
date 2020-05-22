#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;
using std::pair;

class Results {
private:
    vector<string> travels;
    vector<pair<string, vector<int>>> algResults;

    void sumResults();
    void sortResults();
public:
    Results(){};
    void writeToFile(const string& outputFile);
    void startRecordingAlg(const string& algName){ algResults.push_back({algName, vector<int>()});}
    void addAlgResult(int x){ algResults.back().second.push_back(x);}
    void addTravel(const string& travelName){ travels.push_back(travelName);};
};

