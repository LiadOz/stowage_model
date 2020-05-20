COMP = g++-9
#put all your object files here
#OBJS = main.o Container.o Inventory.o Util.o Ship.o Algorithm.o WeightBalanceCalculator.o Simulation.o Port.o CraneOperations.o Parser.o AbstractAlgorithm.o Exceptions.o AdvancedAlgorithm.o
OBJS = main.o AlgorithmRegistrar.o AlgorithmRegistration.o Simulation.o Port.o CraneOperations.o
COMMONOBJS = ../common/Container.o ../common/Exceptions.o ../common/Inventory.o ../common/Parser.o ../common/Ship.o ../common/Util.o ../common/WeightBalanceCalculator.o
#The executabel filename DON'T CHANGE
EXEC = simulator
CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
#CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs -export-dynamic -ldl

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
CraneOperations.o: CraneOperations.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
