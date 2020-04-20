COMP = g++-8
#put all your object files here
OBJS = main.o container.o inventory.o util.o ship.o algorithm.o calculator.o
#The executabel filename DON'T CHANGE
EXEC = ex1
#CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
container.o: container.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
inventory.o: inventory.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
ship.o: ship.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
util.o: util.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
algorithm.o: algorithm.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
calculator.o: calculator.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
