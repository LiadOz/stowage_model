#include "container.h"

using std::endl;

Container::Container(int weight, string destination, string id){
    this->weight = weight;
    this->destination = destination;
    this->id = id;
}

ostream& operator<<(ostream& out, const Container &c){
    return out << "Weight = " << c.weight << "\n"
        << "Destination = " << c.destination << "\n"
        << "id = " << c.id << endl;
}
