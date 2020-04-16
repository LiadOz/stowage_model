#include <iostream>
#include <string>
#include <stdlib.h>
#include "container.h"
#include "ship.h"

using std::string;
using std::vector;

int main() {
    Container c = {20, "this", "that"};
    string a = "sample.plan";
    Ship s(a);
    std::cout << "did it" << std::endl;s
	return EXIT_SUCCESS;
}
