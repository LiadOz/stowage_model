#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::pair;
using std::unordered_map;

typedef pair<string, string> algTravel;

class Results {
private:
    vector<string> travels;
    vector<pair<string, vector<int>>> algResults;
    unordered_map<string, int> travelMapping;
    unordered_map<string, int> algMapping;

    void sumResults();
    void sortResults();
public:
    Results(){};
    void writeToFile(const string& outputFile);
    void startRecordingAlg(const string& algName){ algResults.push_back({algName, vector<int>()});}
    void addAlgResult(int x){ algResults.back().second.push_back(x);}
    void addTravel(const string& travelName);
};

