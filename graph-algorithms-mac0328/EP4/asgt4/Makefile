BOOST_ROOT?=~/boost_1_86_0

SRCS=$(wildcard *.cpp)
DEPS=$(SRCS:.cpp=.d)
OBJS=$(SRCS:.cpp=.o)
PROG=main

# Diretórios de testes e saídas
TEST_DIR := tests
OUT_DIR := outs

# Variáveis para entradas e saídas
INPUTS=$(wildcard tests/in*)

OUTS=$(INPUTS0:tests/in%=outs/out%)

.SECONDARY: $(OUTS) 

CXX=g++
CXXFLAGS= -g -Wall -pedantic -O2 -std=c++17 -I $(BOOST_ROOT)
RM=rm -fv

COMPILE.cpp = $(CXX) $(CXXFLAGS)
OUTPUT_OPTION=-MMD -MP -c
LINK.o = $(CXX) $(LDFLAGS)

all: $(PROG)

%.o: %.cpp
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(PROG) : $(OBJS)
	$(LINK.o) $^ -o $@

.PHONY: clean run test

run: $(PROG)
	./$(PROG)

clean:
	$(RM) $(PROG) $(OBJS) $(DEPS) $(OUTS)

test: $(OUTS)

# Regras para processar entradas e gerar saídas para cada diretório
outs/out%: tests/in% $(PROG)
	./$(PROG) < $< > $@

-include $(DEPS)
