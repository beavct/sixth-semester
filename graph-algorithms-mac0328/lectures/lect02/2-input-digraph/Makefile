SRCS=$(wildcard *.cpp)
DEPS=$(SRCS:.cpp=.d)
OBJS=$(SRCS:.cpp=.o)
PROG=$(subst .cpp,,$(shell echo *.cpp))

CXX=g++
CXXFLAGS=-Wall -pedantic -O2 -std=c++14 -I ~/boost_1_85_0
RM=rm -fv

COMPILE.cpp = $(CXX) $(CXXFLAGS)
OUTPUT_OPTION=-MMD -MP -c
LINK.o = $(CXX) $(LDFLAGS)

all: run

%.o: %.cpp
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(PROG) : $(OBJS)
	$(LINK.o) $^ -o $@

.PHONY: run clean

run: $(PROG)
	./$(PROG) < example.in

clean:
	$(RM) $(PROG) $(OBJS) $(DEPS)

-include $(DEPS)
