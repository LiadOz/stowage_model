#include "_208643270_b.h"

#include <algorithm>

#include "../common/Exceptions.h"

REGISTER_ALGORITHM(_208643270_b)

void _208643270_b::setPriority(){
    reverse(routes.begin(), routes.end());
    for (size_t i = 0; i < routes.size(); ++i) {
        if(cargoPriority.find(routes[i]) == cargoPriority.end())
            cargoPriority.insert({routes[i], i});
    }
    reverse(routes.begin(), routes.end());
}

Algorithm::InsertStatus _208643270_b::loadAwaiting(
        vector<Container>& awaiting, unordered_set<string>& mustReturn){
    InsertStatus ret = SUCCSESS;
    int maxNewInsertions = s.freeSpaces() - mustReturn.size();

    for (Container& c : awaiting) {
        if (maxNewInsertions > 0){
            ret = insertBiggestDepth(c);
            if (ret == SUCCSESS && mustReturn.find(c.getId()) == mustReturn.end()) maxNewInsertions--;
            else if (ret == FULL){
                s.rejectContainer(c);
                ret = FULL;
            }
        }
        else if(mustReturn.find(c.getId()) != mustReturn.end()){
            // returning all containers that were on ship when getting to the port
            ret = insertBiggestDepth(c);
        }
        else s.rejectContainer(c);
    }
    return ret; // since there is no calc then you can always fully load the ship
}

unordered_set<string> _208643270_b::unloadPort(const string& port, vector<Container>& awaiting){
    pair<size_t, size_t> d = s.getStorageDimensions();
    unordered_set<string> mustReturn;
    for (size_t i = 0; i < d.first; ++i){
        for (size_t j = 0; j < d.second; ++j){
            while(s.getContainerDestinationLevel(i, j, port) != -1){
                Container c = s.removeContainer(i, j);
                if (c.getDestination() == port) continue;
                awaiting.push_back(c);
                mustReturn.insert(c.getId());
            }
        }
    }
    return mustReturn;
}

void _208643270_b::getPortInstructions(
        const string& port, vector<Container>& awaiting){
    // now the ones at the start should be at the bottom
    auto mustReturn = unloadPort(port, awaiting);
    setPriority();
    std::sort(awaiting.begin(), awaiting.end(),
            [this](Container& a, Container& b){
            return cargoPriority.at(a.getDestination()) >
            cargoPriority.at(b.getDestination());
            });
    if(loadAwaiting(awaiting, mustReturn) == FULL)
        errorVar(errorStatus, ERROR_TOO_MUCH_CARGO);
}
/* this tries to implement the calculator
Algorithm::InsertStatus _208643270_b::loadAwaiting(
        vector<Container>& awaiting, unordered_set<string> mustReturn){
    vector<Container> tryAgain; // used to hold container rejected by calculator
    InsertStatus ret = SUCCSESS;
    int maxNewInsertions = s.freeSpaces() - mustReturn.size();

    for (Container& c : awaiting) {
        InsertStatus stat = insertBiggestDepth(c);
        if (stat == IMPOSSIBLE) { // due to calculator
            tryAgain.push_back(c);
        }
        else if (stat == FULL){
            s.rejectContainer(c);
            ret = FULL;
        }
        else { // ship has changed then you should try again with the calculator
            for (auto it = tryAgain.begin(); it != tryAgain.end(); ++it) {
                InsertStatus stat = insertBiggestDepth(*(it));
                if (stat == SUCCSESS)
                    tryAgain.erase(it);
                else if (stat == FULL){
                    s.rejectContainer(*it);
                    ret = FULL;
                }
            }
        }
    }
    return ret; // since there is no calc then you can always fully load the ship
}
*/
