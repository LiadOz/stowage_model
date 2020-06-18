#include "SuperAdvancedAlgorithm.h"

#include <algorithm>

using std::get;

// tells where do you start loading all containers that are in the awaiting vector
// so when you start loading you load all those who must return until you reach
// this index and you can insert all that's left
// the returned index is used by reducing it from the vector back
//
// example
// R - must return by the end
// a - simple container
// assmue there is place to 6 containers
// ____________________
// |R|a|R|a|a|a|R|a|a|a| 
// _____________________
//              *  <-- the index that should be returned when subtracting
//
int SuperAdvancedAlgorithm::whereToStart(vector<Container>& awaiting,
        unordered_set<string>& mustReturn){
    int freeSpace = s.freeSpaces(); 
    if ((int)awaiting.size() < freeSpace)
        return awaiting.size();
    int returnInRange = 0;
    for(auto it = awaiting.end() - freeSpace; it != awaiting.end(); ++it){
        if (mustReturn.find((*it).getId()) != mustReturn.end())
            returnInRange++;
    }
    int wouldBeSkipped = mustReturn.size() - returnInRange;
    return freeSpace - wouldBeSkipped;
}

Algorithm::InsertStatus SuperAdvancedAlgorithm::loadAwaiting(
        vector<Container>& awaiting, unordered_set<string>& mustReturn){
    InsertStatus ret = SUCCSESS;
    int startAt = whereToStart(awaiting, mustReturn);

    for (auto it = awaiting.begin(); it != awaiting.end(); ++it){
        if (it < awaiting.end() - startAt && 
                mustReturn.find((*it).getId()) == mustReturn.end()){
            s.rejectContainer((*it));
            continue;
        }
        auto p = getBestStack((*it).getDestination(), -1, -1);
        if (p.first == -1)
            insertBiggestDepth(*it);
        else
            s.insertContainer(p.first, p.second, *it);
    }
    return ret; 
}


unordered_set<string> SuperAdvancedAlgorithm::unloadPort(const string& port, vector<Container>& awaiting){
    // stupid test
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
            mustReturn.insert(c.getId());
            awaiting.push_back(c);
        }
        else 
            s.moveContainer(p.first, p.second, bs.first, bs.second);
        
    } 
    return mustReturn;
}


pair<int, int> SuperAdvancedAlgorithm::getBestStack(const string& port, int x, int y){
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
