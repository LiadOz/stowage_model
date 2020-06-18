#pragma once 
#include "AdvancedAlgorithm.h"

// an improvement of algorithm c it prioritizes far cargos
// and uses the move policy defined in alg d
// other algorithms will inherit this class and try to improve
// only the move policy ie the method getBestStack()
class SuperAdvancedAlgorithm: public AdvancedAlgorithm {
private:
    int whereToStart(vector<Container>& awaiting,
            unordered_set<string>& mustReturn);
    // loads all cargos that were not at unload port
    Algorithm::InsertStatus loadAwaiting(vector<Container>& awaiting, unordered_set<string>& mustReturn);
    // will check where is the best place to start unloading, it should be the one 
    // where the port cargo is the highest then continue by that order
    unordered_set<string> unloadPort(const string& port, vector<Container>& awaiting);
protected: 
    // returns the best stack to move container with certain port to
    //
    // How a best stack is found:
    //  1. Search all the sorted stacks that the top goes after the target
    //  container, return the one that is closest to target.
    //  2. if you failed find a top of stack that goes after you first.
    //  3. if you failed find a top of stack that is as far away as possible
    virtual pair<int, int> getBestStack(const string& port, int x, int );
public:
    SuperAdvancedAlgorithm(){};
    virtual ~SuperAdvancedAlgorithm(){};
};
