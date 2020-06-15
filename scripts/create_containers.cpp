#include <regex>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#define CONTAINER_REGEX "[A-Z]{3}[U,J,Z]\\d{6}\\d"
#define ID_NUMBER_OF_LETTERS 4
using namespace std;

// retruns letter mapping according to ISO 6346
int letterMapping(char c){
    if (c == 'A') return 10;
    if (c - 'K' <= 0) return c - 'B' + 12;
    if (c - 'U' <= 0) return c - 'L' + 23;
    return c - 'V' + 34;
}

int validContainer(string id){
    int digitValidate = 0;
    for (size_t i = 0; i < id.length(); ++i) {
        if (i < ID_NUMBER_OF_LETTERS)
            digitValidate += pow(2, i) * letterMapping(id[i]);
        else
            digitValidate += pow(2, i) * (id[i] - '0');
    }
    int secondary = (int)(digitValidate/11) * 11;
    digitValidate -= secondary;
    return digitValidate;
}

char middle[] = {'U', 'J', 'Z'};

int main(int argc, char *argv[]) {
    ofstream file;
    file.open("samples");
    for (int i = 0; i < 10000; ++i) {
        string name;
        for (int i = 0; i < 3; ++i) {
            name.push_back((char)(rand() % 26 + 'A'));
        }
        name.push_back(middle[rand()%3]);
        for (int i = 0; i < 6; ++i) {
            name.push_back((char)(rand() % 10 + '0'));
        }
        name.push_back((char)validContainer(name) + '0');
        file << name << endl;
    }
    file.close();
    return 0;
}
