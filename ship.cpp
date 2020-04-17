#include <stdexcept>
#include "ship.h"

using std::to_string;

void ShipLogger::logAction(const string& action){
    file << action << std::endl;
    if (logToScreen)
        std::cout << "(ship logger): " << action << std::endl;
}
void Ship::insertContainer(size_t x, size_t y, Container* c){
    storage.pushContainer(x, y, c);
    logger.logAction("<L>," + c->getId() + "," +
            to_string(getCoordinateHeight(x, y)) + 
            "," + to_string(x) + "," + to_string(y)
            );
}

Container* Ship::removeContainer(size_t x, size_t y){
    int h = getCoordinateHeight(x, y);
    Container* c = storage.popContainer(x, y);
    logger.logAction("<U>," + c->getId() + "," +
            to_string(h) + "," + to_string(x) + "," + to_string(y)
            );
    return c;
}

void Ship::moveContainer(size_t x1, size_t y1, size_t x2, size_t y2){
    int firstHeight = getCoordinateHeight(x1, y1);
    Container* c = storage.popContainer(x1, y1);
    try {
        storage.pushContainer(x2, y2, c);
    }catch(std::out_of_range& e) {
        storage.pushContainer(x1, y1, c);
        throw e;
    }
    logger.logAction("<M>," + c->getId() + "," +
            to_string(firstHeight) + "," + 
            to_string(x1) + "," + to_string(y1) +
            to_string(getCoordinateHeight(x2, y2)) + "," + 
            to_string(x2) + "," + to_string(y2) 
            );
}

void Ship::rejectContainer(Container* c){
    logger.logAction("<R>," + c->getId());
}
