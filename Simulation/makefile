COMP = g++-8
#put all your object files here
OBJS = main.o Container.o Inventory.o Util.o Ship.o Algorithm.o WeightBalanceCalculator.o Simulation.o Port.o CraneOperations.o Parser.o AbstractAlgorithm.o Exceptions.o AdvancedAlgorithm.o
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
#CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Container.o: Container.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Inventory.o: Inventory.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Ship.o: Ship.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Util.o: Util.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AbstractAlgorithm.o: AbstractAlgorithm.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Algorithm.o: Algorithm.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
AdvancedAlgorithm.o: AdvancedAlgorithm.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
WeightBalanceCalculator.o: WeightBalanceCalculator.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Simulation.o: Simulation.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Port.o: Port.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Parser.o: Parser.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
CraneOperations.o: CraneOperations.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Exceptions.o: Exceptions.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
