#include "_208643270_d.h"

REGISTER_ALGORITHM(_208643270_d)

#include <algorithm>
#include <queue>
#include <tuple>
#include "../common/Exceptions.h"

using std::get;

void _208643270_d::getPortInstructions(
        const string& port, vector<Container>& awaiting){

    routes.push_back(port); // adding current port to the priority
    setPriority();
    routes.pop_back();

    unordered_set<string> cargoToInsert = cargoToAdd(port, awaiting);
    unloadPort(port, awaiting);
    prioritySort(awaiting);
    if(loadAwaiting(awaiting, cargoToInsert) == FULL)
        errorVar(errorStatus, ERROR_TOO_MUCH_CARGO);
}

Algorithm::InsertStatus _208643270_d::loadAwaiting(
        vector<Container>& awaiting, unordered_set<string>& mustReturn){
    InsertStatus ret = SUCCSESS;
    for (auto c : awaiting) {
        if (mustReturn.find(c.getId()) == mustReturn.end()){
            s.rejectContainer(c);
            continue;
        }
        auto p = getBestStack(c.getDestination(), -1, -1);
        if (p.first == -1)
            insertBiggestDepth(c);
        else
            s.insertContainer(p.first, p.second, c);
    }
    return ret; 
}

pair<int, int> _208643270_d::getBestStack(const string& port, int x, int y){
    pair<int, int> ret;
    // a mapping of coordinate with sorted flag and top port
    vector<std::tuple<pair<int, int>, bool, string>> mapping;
    auto d = s.getStorageDimensions();
    // calculating the mapping
    for (size_t i = 0; i < d.first; ++i){
        for (size_t j = 0; j < d.second; ++j){
            if (x == (int)i && y == (int)j) continue;
            if (s.fullCoordinate(i, j)) continue;
            if (s.emptyCoordinate(i, j)){
                mapping.push_back({ {i, j}, true, routes.back()});
                continue;
            }

            bool flag = true;
            vector<Container> vc = s.getCoordinateContainers(i, j);
            string topPort = vc.back().getDestination();
            for (auto it = vc.begin(); it != vc.end() -1; ++it){
                if (placeOn((*it).getDestination(), (*(it + 1)).getDestination())) flag = false;
            }
            mapping.push_back({ {i, j}, flag, topPort});
        }
    }

    if (mapping.size() == 0) return {-1, -1};

    // trying to find best sorted stack
    int m = routes.size() * 100; // just to make sure its the max
    for (auto s : mapping) {
        if (!get<1>(s)) continue;
        int val = placeOn(port, get<2>(s));
        if (val > -1 && val < m){
            m = val;
            ret = {get<0>(s).first, get<0>(s).second};
        }
        if (m != (int)routes.size() * 100) return ret;
    }

    for (auto s : mapping) {
        if (get<1>(s)) continue;
        int val = placeOn(port, get<2>(s));
        if (val > -1 && val < m){
            m = val;
            ret = {get<0>(s).first, get<0>(s).second};
        }
        if (m != (int)routes.size() * 100) return ret;
    }

    // if nothing good found just return the first
    return {get<0>(mapping[0])};
}

unordered_set<string> _208643270_d::unloadPort(const string& port, vector<Container>& awaiting){
    unordered_set<string> mustReturn;
    pair<int, int> p;
    while (true){
        p = getClosestCoordinate(port);
        if (p.first == -1) break;
        int level = s.getContainerDestinationLevel(p.first, p.second, port);
        if (level == 0){
            s.removeContainer(p.first, p.second);
            continue;
        }
        Container c = s.peekContainer(p.first, p.second);
        auto bs = getBestStack(c.getDestination(), p.first, p.second);
        if (bs.first == -1){
            s.removeContainer(p.first, p.second);
            mustReturn.insert(c.getDestination());
            awaiting.push_back(c);
        }
        else 
            s.moveContainer(p.first, p.second, bs.first, bs.second);
        
    } 
    /*
    for (size_t i = 0; i < d.first; ++i){
        for (size_t j = 0; j < d.second; ++j){
            while(s.getContainerDestinationLevel(i, j, port) != -1){
                Container c = s.peekContainer(i, j);
                // when at correct port
                if (c.getDestination() == port &&
                        calc.tryOperation((char)Action::UNLOAD, c.getWeight(), i, j)
                        == WeightBalanceCalculator::APPROVED) {
                    s.removeContainer(i, j);
                    continue;
                }

                // when no other good move exists
                pair<int, int> mv = findGoodLocation(i, j, port);
                if (mv.first == -1 && mv.second == -1 &&
                        calc.tryOperation((char)Action::UNLOAD, c.getWeight(), i, j)
                        == WeightBalanceCalculator::APPROVED) {
                    s.removeContainer(i, j);
                    awaiting.push_back(c);
                    mustReturn.insert(c.getId());
                }

                if (calc.tryOperation((char)Action::MOVE, c.getWeight(), i, j) 
                            == WeightBalanceCalculator::APPROVED)
                    s.moveContainer(i, j, mv.first, mv.second);
            }
        }
    }
    */
    return mustReturn;
}


// this function is long but very straight forward
// cutting it to parts will make bad code prone to bugs
unordered_set<string> _208643270_d::cargoToAdd(
        const string& port, vector<Container>& awaiting){

    unordered_set<string> ret;
    int spaceLeft = s.freeSpaces();

    // first we want to know how many we have for each port
    vector<Container> current = s.getShipContainers();
    unordered_map<string, int> distribution;
    for (auto r : routes) {
        distribution.insert({r, 0});
    }
    for (auto& c : current) {
        string d = c.getDestination();
        if (d == port){
            spaceLeft++;
            continue;
        }
        auto it = distribution.find(d);
        if (it == distribution.end())
            distribution.insert({d, 1});
        else it->second += 1;
    }

    // second we construst a min heap using the distribution
    using pis = pair<int, string>;
    std::priority_queue<pis, vector<pis>, std::greater<pis>> pq;
    for (auto x : distribution) {
        pq.push({x.second, x.first});
    }

    // third we want to have a set of awaiting cargo destination ports
    unordered_map<string, vector<string>> candidates;
    for (auto& c : awaiting){
        auto it = candidates.find(c.getDestination());
        if (it == candidates.end())
            candidates.insert({c.getDestination(), {c.getId()}});
        else
            (*it).second.push_back(c.getId());
    }

    // now we determine who is going to be loaded by always adding ones
    // with the fewest representation.
    while (spaceLeft && !pq.empty()) {
        string minority = pq.top().second;
        int n = pq.top().first;
        pq.pop();
        auto it = candidates.find(minority);
        if (it == candidates.end() || it->second.size() == 0) continue;
        ret.insert(it->second.back());
        it->second.pop_back();
        spaceLeft--;
        pq.push({n+1, minority});
    }

    return ret;
}
