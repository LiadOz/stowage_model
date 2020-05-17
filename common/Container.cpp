#include "container.h"

#include <regex>
#include <cmath>

#include "Util.h"
#include "Exceptions.h"

using std::endl;
using std::regex;
using std::regex_match;
using std::pow;

#define CONTAINER_REGEX "[A-Z]{3}[U,J,Z]\\d{6}\\d"
#define ID_NUMBER_OF_LETTERS 4
#define PARSING_ID 0
#define PARSING_WEIGHT 1
#define PARSING_PORT 2

// retruns letter mapping according to ISO 6346
int LetterMapping(char c){
    if (c == 'A') return 10;
    if (c - 'K' <= 0) return c - 'B' + 12;
    if (c - 'U' <= 0) return c - 'L' + 23;
    return c - 'V' + 34;
}

bool validContainer(const string& id){
    regex valid(CONTAINER_REGEX);
    if(!regex_match(id, valid)) return false;
    int digitValidate = 0;
    for (size_t i = 0; i < id.length() - 1; ++i) {
        if (i < ID_NUMBER_OF_LETTERS)
            digitValidate += pow(2, i) * LetterMapping(id[i]);
        else
            digitValidate += pow(2, i) * (id[i] - '0');
    }
    int secondary = (int)(digitValidate/11) * 11;
    digitValidate -= secondary;
    if (id[id.length()-1] - '0' == digitValidate)
        return true;
    return false;

}

Container::Container(int weight, const string& destination, const string& id){
    if(!validContainer(id))
        throw NonFatalError("invalid id " + id, ERROR_BAD_ID_FORMAT);
    if(!validRoute(destination))
        throw NonFatalError("invalid destination " + destination, ERROR_BAD_CARGO_PORT);
    this->weight = weight;
    this->destination = destination;
    this->id = id;
}

Container::Container(vector<string>& line){
    if (line.size() < 1)
        throw NonFatalError("invalid id", ERROR_CANT_READ_ID);
    if (!validContainer(line[PARSING_ID]))
        throw NonFatalError("invalid id", ERROR_BAD_ID_FORMAT);
    if (line.size() < 2 or std::stoi(line[PARSING_WEIGHT]) <= 0)
        throw NonFatalError("invalid weight", ERROR_BAD_WEIGHT);
    if (line.size() < 3 or !validRoute(line[PARSING_PORT]))
        throw NonFatalError("invalid destination", ERROR_BAD_CARGO_PORT);
    weight = std::stoi(line[PARSING_WEIGHT]);
    destination = line[PARSING_PORT];
    id = line[PARSING_ID];
}

ostream& operator<<(ostream& out, const Container &c){
    return out << "Weight = " << c.weight << "\n"
        << "Destination = " << c.destination << "\n"
        << "id = " << c.id << endl;
}
