COMP = g++-8
#put all your object files here
OBJS = main.o container.o ship_plans.o #objects should be placed here!
#The executabel filename DON'T CHANGE
EXEC = ex1
CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) $(CPP_LINK_FLAG) -o $@
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
main.o: main.cpp container.o ship_plans.o
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
container.o: container.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
ship_plans.o: ship_plans.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
