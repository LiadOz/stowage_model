#include "ship.h"

bool Ship::insertContainer(int x, int y, Container* c){
    return storage.pushContainer(x, y, c);
}

Container* Ship::removeContainer(int x, int y){
    return storage.popContainer(x, y);
}
