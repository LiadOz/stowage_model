#include "./AdvancedAlgorithm.h"

#include <algorithm>

#include "../common/Exceptions.h"

using std::get;

int AdvancedAlgorithm::placeOn(const string& above, const string& below){
    return cargoPriority.at(below) - cargoPriority.at(above);
}

void AdvancedAlgorithm::setPriority(){
    cargoPriority.clear();
    reverse(routes.begin(), routes.end());
    for (size_t i = 0; i < routes.size(); ++i) {
        if(cargoPriority.find(routes[i]) == cargoPriority.end())
            cargoPriority.insert({routes[i], i});
    }
    reverse(routes.begin(), routes.end());
}

void AdvancedAlgorithm::prioritySort(vector<Container>& toSort){
    std::sort(toSort.begin(), toSort.end(),
            [this](Container& a, Container& b){
            return cargoPriority.at(a.getDestination()) <
            cargoPriority.at(b.getDestination());
            });
}

void AdvancedAlgorithm::getPortInstructions(
        const string& port, vector<Container>& awaiting){

    routes.push_back(port); // adding current port to the priority
    setPriority();
    routes.pop_back();

    auto mustReturn = unloadPort(port, awaiting);
    prioritySort(awaiting);
    loadAwaiting(awaiting, mustReturn);
    if (s.freeSpaces() == 0)
        errorVar(errorStatus, ERROR_TOO_MUCH_CARGO);
}

unordered_set<string> AdvancedAlgorithm::unloadPort(const string& port, vector<Container>& awaiting){
    pair<size_t, size_t> d = s.getStorageDimensions();
    unordered_set<string> mustReturn;
    for (size_t i = 0; i < d.first; ++i){
        for (size_t j = 0; j < d.second; ++j){
            while(s.getContainerDestinationLevel(i, j, port) != -1){
                Container c = s.peekContainer(i, j);
                if (calc.tryOperation((char)Action::UNLOAD, c.getWeight(), i, j)
                        != WeightBalanceCalculator::APPROVED)
                    continue;

                s.removeContainer(i, j);
                if (c.getDestination() == port) continue;
                awaiting.push_back(c);
                mustReturn.insert(c.getId());
            }
        }
    }
    return mustReturn;
}

pair<int, int> AdvancedAlgorithm::findGoodLocation(int x, int y, const string& port){
    Container c = s.peekContainer(x, y);

    pair<int, int> closest = {-1, -1};
    int lowestDistance = -1;
    pair<size_t, size_t> d = s.getStorageDimensions();
    for (size_t i = 0; i < d.first; ++i){
        for (size_t j = 0; j < d.second; ++j){
            if ((int)i == x && (int)j == y) continue;
            if (s.fullCoordinate(i, j)) continue;
            // dont move to a place that will be  unloaded at a later stage
            if (s.getContainerDestinationLevel(i, j, port) != -1) continue;
            if (s.emptyCoordinate(i, j)){
                if (lowestDistance == -1)
                    closest = {i, j};
                continue;
            }

            Container other = s.peekContainer(i, j);
            int dist = placeOn(c.getDestination(), other.getDestination());
            if (dist >= 0 && lowestDistance == -1) lowestDistance = dist;
            else continue;

            if (dist <= lowestDistance){
                lowestDistance = dist;
                closest = {i, j};
            }

        }
    }
    return closest;
}

pair<int, int> AdvancedAlgorithm::getClosestCoordinate(const string& port){
    pair<int, int> ret = {-1, -1};
    int m = s.getNumFloors() + 1;
    pair<size_t, size_t> d = s.getStorageDimensions();
    for (size_t i = 0; i < d.first; ++i){
        for (size_t j = 0; j < d.second; ++j){
            int level = s.getContainerDestinationLevel(i, j, port);
            if (level != -1 && level < m){
                m = level;
                ret = {i, j};
            }
        }
    }

    return ret;
}
