#include "_208643270_b.h"


REGISTER_ALGORITHM(_208643270_b)

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
