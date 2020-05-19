COMP = g++-8

SHARED_OBJS = _208643270_a.so 
OBJS = _208643270_a.o
CPP_COMP_FLAG = -std=c++2a -Wall -Wextra -Werror -pedantic-errors -DNDEBUG -fPIC
CPP_LINK_FLAG = -fvisibility=hidden -shared 

all: $(SHARED_OBJS)

_208643270_a.so: $(OBJS)
		$(COMP) $(CPP_LINK_FLAG) -o $@ $^

_208643270_a.o: _208643270_a.cpp 
		$(COMP) $(CPP_COMP_FLAG) -c $*.cpp 
			
clean:
		rm -f $(OBJS) $(SHARED_OBJS)
