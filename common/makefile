COMP = g++-9.3.0
ifdef STOWAGE # used to complie on my computer
	COMP = g++-9
endif
ifdef STOWAGE_MATAN # used to complie on matan's computer
	COMP = g++
endif

#The executabel filename DON'T CHANGE
CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
OBJS = Container.o Inventory.o Util.o Ship.o Parser.o Exceptions.o Logger.o
#The executabel filename DON'T CHANGE
CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC
#CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -pedantic-errors -DNDEBUG
CPP_LINK_FLAG = -lstdc++fs 

all: $(OBJS)
#a rule for building a simple c++ source file
#use g++ -MM main.cpp to see dependencies
Container.o: Container.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Inventory.o: Inventory.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Ship.o: Ship.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Util.o: Util.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Parser.o: Parser.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
CraneOperations.o: CraneOperations.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Exceptions.o: Exceptions.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Logger.o: Logger.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)
