CC := g++
CO := -c -ggdb -std=c++1z -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing

LN := g++
LO =

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, obj/%.o, $(SRCS))

TARGET := londonstockexchange

first: all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LN) $(LO) -o $@ $^ #-lpthread  -lboost_system

obj/%.o: %.cpp
	mkdir -p obj/src
	$(CC) $(CO) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
