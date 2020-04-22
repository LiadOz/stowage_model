#include <iostream>
#include <string>
#include <stdlib.h>
#include "container.h"
#include "ship.h"
#include "algorithm.h"
#include "util.h"
#include "Port.h"
#include "simulation.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

int main() {
	Algorithm* algorithm = new BruteAlgorithm();
	Simulation simulation("travelA", algorithm);
	simulation.RunSimulation();
    delete algorithm;

	return EXIT_SUCCESS;
}
