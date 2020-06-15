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
    vector<string> algs;
    unordered_map<string, int> travelMapping;
    unordered_map<string, int> algMapping;
    vector<vector<int>> algResults;

    void sumResults();
    void sortResults();
public:
    Results(){};
    void writeToFile(const string& outputFile);
    void addTravel(const string& travelName);
    void addAlg(const string& algName);
    void reserveSpace();
    // can add results only to reserved spaces
    void addResult(const string& algName, const string& travelName, int x);
};

