BOOST_ROOT?=~/boost_1_86_0

SRCS=$(wildcard *.cpp)
DEPS=$(SRCS:.cpp=.d)
OBJS=$(SRCS:.cpp=.o)
PROG=main

# Diretórios de testes e saídas
TEST_DIRS := tests0 tests1 tests2
OUT_DIRS := outs0 outs1 outs2

# Variáveis para entradas e saídas
INPUTS0=$(wildcard tests0/in*)
INPUTS1=$(wildcard tests1/in*)
INPUTS2=$(wildcard tests2/in*)

OUTS0=$(INPUTS0:tests0/in%=outs0/out%)
OUTS1=$(INPUTS1:tests1/in%=outs1/out%)
OUTS2=$(INPUTS2:tests2/in%=outs2/out%)

.SECONDARY: $(OUTS0) $(OUTS1) $(OUTS2)

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
	$(RM) $(PROG) $(OBJS) $(DEPS) $(OUTS0) $(OUTS1) $(OUTS2)

test: $(OUTS0) $(OUTS1) $(OUTS2)

# Regras para processar entradas e gerar saídas para cada diretório
outs0/out%: tests0/in% $(PROG)
	./$(PROG) < $< > $@

outs1/out%: tests1/in% $(PROG)
	./$(PROG) < $< > $@

outs2/out%: tests2/in% $(PROG)
	./$(PROG) < $< > $@

-include $(DEPS)
