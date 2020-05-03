#include <stdexcept>
#include "ship.h"

using std::to_string;

void ShipLogger::LogAction(const string& action){
    file << action << std::endl;
    if (logToScreen)
        std::cout << "(ship logger): " << action << std::endl;
}
void Ship::InsertContainer(size_t x, size_t y, Container& c){
    // TODO: add calculator check
    storage.PushContainer(x, y, c);
    logger.LogAction("<L>," + c.GetId() + "," +
            to_string(GetCoordinateHeight(x, y)) + 
            "," + to_string(x) + "," + to_string(y)
            );
}

Container Ship::RemoveContainer(size_t x, size_t y){
    // TODO: add calculator check
    int h = GetCoordinateHeight(x, y);
    Container c = storage.PopContainer(x, y);
    logger.LogAction("<U>," + c.GetId() + "," +
            to_string(h) + "," + to_string(x) + "," + to_string(y)
            );
    return c;
}

void Ship::MoveContainer(size_t x1, size_t y1, size_t x2, size_t y2){
    // TODO: add calculator check
    int firstHeight = GetCoordinateHeight(x1, y1);
    Container c = storage.PopContainer(x1, y1);
    try {
        storage.PushContainer(x2, y2, c);
    }catch(std::out_of_range& e) {
        storage.PushContainer(x1, y1, c);
        throw e;
    }
    logger.LogAction("<M>," + c.GetId() + "," +
            to_string(firstHeight) + "," + 
            to_string(x1) + "," + to_string(y1) +
            to_string(GetCoordinateHeight(x2, y2)) + "," + 
            to_string(x2) + "," + to_string(y2) 
            );
}

void Ship::RejectContainer(Container& c){
    logger.LogAction("<R>," + c.GetId());
}
