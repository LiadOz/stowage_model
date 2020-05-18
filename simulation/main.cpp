#include <iostream>
#include <stdlib.h>
#include "AlgorithmRegistrar.h"

int main() {

    auto& registrar = AlgorithmRegistrar::getInstance(); {
        std::string error;
        if (!registrar.loadAlgorithmFromFile("../algorithm/_208643270_a.so", error)) {
            std::cerr << error << '\n'; 
                return EXIT_FAILURE;
        }
    }
    
    for (auto algo_iter = registrar.begin(); algo_iter != registrar.end(); ++algo_iter) {	
		auto algo = (*algo_iter)();
		algo->readShipPlan("Big boats - They float!"); 
	}	
    	return EXIT_SUCCESS;
}
