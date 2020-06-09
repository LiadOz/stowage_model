#include "./AdvancedAlgorithm.h"

#include <algorithm>

#include "../common/Exceptions.h"

int AdvancedAlgorithm::placeOn(const string& above, const string& below){
    return cargoPriority.at(below) - cargoPriority.at(above);
}

void AdvancedAlgorithm::setPriority(){
    reverse(routes.begin(), routes.end());
    for (size_t i = 0; i < routes.size(); ++i) {
        if(cargoPriority.find(routes[i]) == cargoPriority.end())
            cargoPriority.insert({routes[i], i});
    }
    reverse(routes.begin(), routes.end());
}

void AdvancedAlgorithm::getPortInstructions(
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
