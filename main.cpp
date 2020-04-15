#include <iostream>
#include <string>
#include "container.h"
#include "ship.h"

using std::string;
using std::vector;

int main() {
    Container* c = new Container(10, "a", "CSQU3054383");
    string a = "sample.plan";
    Ship s(a);
    s.insertContainer(0, 0, c);
    s.insertContainer(0, 0, c);
    s.insertContainer(0, 0, c);
    s.insertContainer(0, 0, c);
    s.insertContainer(0, 0, c);
    s.insertContainer(0, 0, c);
    s.insertContainer(0, 0, c);
    s.insertContainer(0, 0, c);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
}
