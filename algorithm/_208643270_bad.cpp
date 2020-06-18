#include "_208643270_a.h"

REGISTER_ALGORITHM(_208643270_a)

void _208643270_a::getPortInstructions(const string& port,
        vector<Container>& awaiting){
    vector<Container> outside = unloadAll(port);
    next_x = next_y = 0;

    // inserting all cargos that were removed
    for (Container c : outside)
        insertNextFree(c);

    // pushing new cargo
    for (auto c : awaiting) {
        InsertStatus stat = insertNextFree(c);
        if (stat == FULL){
            s.rejectContainer(c);
        }
            
    }
}
