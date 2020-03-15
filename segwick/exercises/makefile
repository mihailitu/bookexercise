CC := g++
CO := -c -ggdb -std=c++17 -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -Iinclude/ -I../
#release
#CO := -c -std=c++17 -o3 -W -Wall -Wextra -pedantic -Wno-unknown-pragmas -fPIC -fno-strict-aliasing -Iinclude/

LN := g++
LO =

SRCS := $(wildcard *.cpp 01/*.cpp)
OBJS := $(patsubst %.cpp, ../obj/e01/%.o, $(SRCS))

TARGET := segwick

first: all

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LN) $(LO) -o $@ $^ -lgtest -lpthread #-lboost_system

obj/%.o: %.cpp
	mkdir -p ../obj/e01
	$(CC) $(CO) -c -o $@ $<
