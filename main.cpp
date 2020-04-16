#include <iostream>
#include <string>
#include "container.h"
#include "ship.h"
#include "util.h"

using std::string;
using std::vector;

int main() {
    Logger& l = Logger::Instance();
    l.setLogType("creating conatiners");
    Container* c1 = new Container(10, "a", "CSQU3054383");
    Container* c2 = new Container(10, "a", "CSQU305438s");
    string a = "example/sample.plan";
    Ship s(a);
    l.setLogType("inserting Containers");
    s.insertContainer(0, 0, c1);
    s.insertContainer(0, 0, c2);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);
    s.removeContainer(0, 0);

}
