#pragma once 
#include "AdvancedAlgorithm.h"

class _208643270_c : public AdvancedAlgorithm {
private:
    // finds a good location to move a container at coordinate
    // if no location is found returns {-1, -1}
    pair<int, int> findValidLocation(int x, int y);
    int whereToStart(vector<Container>& awaiting,
            unordered_set<string>& mustReturn);

protected:
    // if you can't insert all the awaiting you want to take all those 
    // that must return and also the ones with closests ports
    // thist requires some preprocessing of the awaiting
    Algorithm::InsertStatus loadAwaiting(vector<Container>& awaiting, unordered_set<string>& mustReturn);

    // tries to be better than the parent algorithm by using move operations
    unordered_set<string> unloadPort(const string& port, vector<Container>& awaiting);
public:
    _208643270_c (){};
    virtual ~_208643270_c(){};
};
