#include <regex>
#include <cmath>
#include "container.h"
#define CONTAINER_REGEX "[A-Z]{3}[U,J,Z]\\d{6}\\d"
#define ID_NUMBER_OF_LETTERS 4

using std::endl;
using std::regex;
using std::regex_match;
using std::pow;

// retruns letter mapping according to ISO 6346
int letterMapping(char c){
    if (c == 'A') return 10;
    if (c - 'K' <= 0) return c - 'B' + 12;
    if (c - 'U' <= 0) return c - 'L' + 23;
    return c - 'V' + 34;
}

bool validContainer(string id){
    regex valid(CONTAINER_REGEX);
    if(!regex_match(id, valid)) return false;
    int digitValidate = 0;
    for (size_t i = 0; i < id.length() - 1; ++i) {
        if (i < ID_NUMBER_OF_LETTERS)
            digitValidate += pow(2, i) * letterMapping(id[i]);
        else
            digitValidate += pow(2, i) * (id[i] - '0');
    }
    int secondary = (int)(digitValidate/11) * 11;
    digitValidate -= secondary;
    if (id[id.length()-1] - '0' == digitValidate)
        return true;
    return false;

}

Container::Container(int weight, string destination, string id){
    validContainer(id);
    this->weight = weight;
    this->destination = destination;
    this->id = id;
}

ostream& operator<<(ostream& out, const Container &c){
    return out << "Weight = " << c.weight << "\n"
        << "Destination = " << c.destination << "\n"
        << "id = " << c.id << endl;
}
