COMP = g++-9.3.0
ifdef STOWAGE # used to complie on my computer
	COMP = g++-9
endif

OBJS = main.o AlgorithmRegistrar.o AlgorithmRegistration.o Simulation.o Port.o CraneOperations.o Results.o SimulationManager.o AlgTravelProducer.o ThreadPoolExecuter.o
COMMONOBJS = ../common/Container.o ../common/Exceptions.o ../common/Inventory.o ../common/Parser.o ../common/Ship.o ../common/Util.o ../common/WeightBalanceCalculator.o ../common/Logger.o
#The executabel filename DON'T CHANGE
EXEC = simulator
CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC
#CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs -export-dynamic -ldl -pthread

$(EXEC): complie_common $(OBJS)
	$(COMP) $(OBJS) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@ 
complie_common:
	+$(MAKE) -C ../common
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AlgorithmRegistrar.o: AlgorithmRegistrar.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AlgorithmRegistration.o: AlgorithmRegistration.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Simulation.o: Simulation.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Port.o: Port.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Results.o: Results.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
SimulationManager.o: SimulationManager.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
CraneOperations.o: CraneOperations.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AlgTravelProducer.o: AlgTravelProducer.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
ThreadPoolExecuter.o: ThreadPoolExecuter.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f ../common/*.o
	rm -f $(OBJS) $(EXEC)
