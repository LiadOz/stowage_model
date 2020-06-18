#pragma once

#include "AdvancedAlgorithm.h"

// in this algorithm when you load new containers you insert the ones that are going to farther ports first
class _208643270_b : public AdvancedAlgorithm {
private:

    // loads containers from awaiting to the ship, from the furthest port to the closet
    Algorithm::InsertStatus loadAwaiting(vector<Container>& awaiting, unordered_set<string>& mustReturn);
protected:
public:
    _208643270_b (){};
    virtual ~_208643270_b (){};

};
