CC := g++
CO := -c -ggdb -std=c++17 -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -Iinclude/
#release
#CO := -c -std=c++17 -o3 -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -Iinclude/

LN := g++
LO =

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst %.cpp, obj/%.o, $(SRCS))

TARGET := prjtemplate

first: all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LN) $(LO) -o $@ $^ #-lpthread  -lboost_system

obj/%.o: %.cpp
	mkdir -p obj/src
	$(CC) $(CO) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
