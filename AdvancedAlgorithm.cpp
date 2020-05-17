#include "AdvancedAlgorithm.h"

#include <algorithm>

#include "Exceptions.h"

void AdvancedAlgorithm::setPriority(){
    reverse(routes.begin(), routes.end());
    for (size_t i = 0; i < routes.size(); ++i) {
        if(cargoPriority.find(routes[i]) == cargoPriority.end())
            cargoPriority.insert({routes[i], i});
    }
    reverse(routes.begin(), routes.end());
}


Algorithm::InsertStatus AdvancedAlgorithm::loadAwaiting(vector<Container>& awaiting){
    vector<Container> tryAgain; // used to hold container rejected by calculator

    for (Container& c : awaiting) {
        InsertStatus stat = insertBiggestDepth(c);
        if (stat == IMPOSSIBLE) { // due to calculator
            tryAgain.push_back(c);
        }
        else if (stat == FULL)
            return FULL;
        else { // ship has changed then you should try again with the calculator
            for (auto it = tryAgain.begin(); it != tryAgain.end(); ++it) {
                InsertStatus stat = insertBiggestDepth(*(it));
                if (stat == SUCCSESS)
                    tryAgain.erase(it);
                else if (stat == FULL)
                    return FULL;
            }
        }
    }
    return SUCCSESS; // since there is no calc then you can always fully load the ship
}

void AdvancedAlgorithm::unloadOpen(const string& port){
    pair<size_t, size_t> d = s.getStorageDimensions();
    for (size_t i = 0; i < d.first; ++i){
        for (size_t j = 0; j < d.second; ++j){
            while (s.getContainerDestinationLevel(i, j, port) == 0)
                s.removeContainer(i, j);
        }
    }
}


void AdvancedAlgorithm::getPortInstructions(
        const string& port, vector<Container>& awaiting){
    setPriority();
    std::sort(awaiting.begin(), awaiting.end(),
            [this](Container& a, Container& b){
            return cargoPriority.at(a.getDestination()) >
            cargoPriority.at(b.getDestination());
            });
    // now the ones at the start should be at the bottom
    unloadOpen(port);
    if(loadAwaiting(awaiting) == FULL)
        errorVar(errorStatus, ERROR_TOO_MUCH_CARGO);
}
