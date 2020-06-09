#include "_208643270_c.h"

REGISTER_ALGORITHM(_208643270_c)

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
int _208643270_c::whereToStart(vector<Container>& awaiting,
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

Algorithm::InsertStatus _208643270_c::loadAwaiting(
        vector<Container>& awaiting, unordered_set<string>& mustReturn){
    InsertStatus ret = SUCCSESS;
    int startAt = whereToStart(awaiting, mustReturn);

    for (auto it = awaiting.begin(); it != awaiting.end(); ++it){
        if (it < awaiting.end() - startAt && 
                mustReturn.find((*it).getId()) == mustReturn.end()){
            s.rejectContainer((*it));
            continue;
        }
        ret = insertBiggestDepth((*it));
    }
    return ret; 
}

pair<int, int> _208643270_c::findValidLocation(int x, int y){
    Container c = s.peekContainer(x, y);

    pair<int, int> closest = {-1, -1};
    int lowestDistance = -1;
    pair<size_t, size_t> d = s.getStorageDimensions();
    for (size_t i = 0; i < d.first; ++i){
        for (size_t j = 0; j < d.second; ++j){
            if ((int)i == x && (int)j == y) continue;
            if (s.fullCoordinate(i, j)) continue;
            if (s.emptyCoordinate(i, j) && lowestDistance == -1){
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

unordered_set<string> _208643270_c::unloadPort(const string& port, vector<Container>& awaiting){
    pair<size_t, size_t> d = s.getStorageDimensions();
    unordered_set<string> mustReturn;
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
                pair<int, int> mv = findValidLocation(i, j);
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
    return mustReturn;
}
