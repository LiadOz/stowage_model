COMP = g++-9.3.0
ifdef STOWAGE # used to complie on my computer
	COMP = g++-9
endif
ifdef STOWAGE_MATAN # used to complie on my computer
	COMP = g++
endif

OBJS = Algorithm.o AdvancedAlgorithm.o SuperAdvancedAlgorithm.o _208643270_a.o _208643270_b.o
EXEC = algtest
SHARED_OBJS = _208643270_a.so _208643270_b.so
COMMONOBJS = ../common/Container.o ../common/Exceptions.o ../common/Inventory.o ../common/Parser.o ../common/Ship.o ../common/Util.o
CPP_COMP_FLAG = -std=c++2a -g -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC -fvisibility=hidden
CPP_LINK_FLAG = -lstdc++fs -shared 

all: complie_common $(SHARED_OBJS)

complie_common:
	+$(MAKE) -C ../common
_208643270_a.so: _208643270_a.o Algorithm.o 
		$(COMP) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@ $^
_208643270_b.so: _208643270_b.o Algorithm.o AdvancedAlgorithm.o
		$(COMP) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@ $^
_208643270_c.so: _208643270_c.o Algorithm.o AdvancedAlgorithm.o
		$(COMP) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@ $^
_208643270_d.so: _208643270_d.o Algorithm.o AdvancedAlgorithm.o
		$(COMP) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@ $^
_208643270_e.so: _208643270_e.o Algorithm.o AdvancedAlgorithm.o SuperAdvancedAlgorithm.o
		$(COMP) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@ $^
_208643270_f.so: _208643270_f.o Algorithm.o AdvancedAlgorithm.o SuperAdvancedAlgorithm.o
		$(COMP) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@ $^
_208643270_a.o: _208643270_a.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
_208643270_b.o: _208643270_b.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
_208643270_c.o: _208643270_c.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
_208643270_d.o: _208643270_d.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
_208643270_e.o: _208643270_e.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
_208643270_f.o: _208643270_f.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
Algorithm.o: Algorithm.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
AdvancedAlgorithm.o: AdvancedAlgorithm.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
SuperAdvancedAlgorithm.o: SuperAdvancedAlgorithm.cpp 
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
main.o: main.cpp
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
# to tests linking replace link flags and put the exec instead of all:
# also add main.o to OBJS
# CPP_LINK_FLAG = -lstdc++fs
# $(EXEC): complie_common $(OBJS) 
#	 $(COMP) $(OBJS) $(COMMONOBJS) $(CPP_LINK_FLAG) -o $@
			
clean:
	rm -f ../common/*.o
	rm -f $(OBJS) $(SHARED_OBJS)
