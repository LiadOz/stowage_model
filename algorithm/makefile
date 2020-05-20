COMP = g++-9

OBJS = _208643270_a.o Algorithm.o _208643270_a.o
EXEC = algtest
SHARED_OBJS = _208643270_a.so _208643270_b.so
COMMONOBJS = ../common/Container.o ../common/Exceptions.o ../common/Inventory.o ../common/Parser.o ../common/Ship.o ../common/Util.o ../common/WeightBalanceCalculator.o
CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC -fvisibility=hidden
CPP_LINK_FLAG = -lstdc++fs -shared

all: complie_common $(SHARED_OBJS)

complie_common:
	+$(MAKE) -C ../common
_208643270_a.so: _208643270_a.o Algorithm.o
		$(COMP) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@ $^
_208643270_b.so: _208643270_b.o Algorithm.o
		$(COMP) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@ $^
_208643270_a.o: _208643270_a.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
_208643270_b.o: _208643270_b.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
Algorithm.o: Algorithm.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
$(EXEC): complie_common $(OBJS) 
	$(COMP) $(OBJS) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@
			
clean:
	rm -f ../common/*.o
	rm -f $(OBJS) $(SHARED_OBJS)
