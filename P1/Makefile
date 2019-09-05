TEST		:= ../Tests-auto

CXX 		:= clang++
CPPFLAGS	:= -DP1 -I ../P1/ -I $(TEST)
CXXFLAGS 	:= -std=c++14 -Wall -pedantic -g
SOURCES		:= fecha.cpp cadena.cpp
OBJECTS     := $(SOURCES:.cpp=.o)

all: test-P1-auto test-P1-consola

test-P1-auto: $(OBJECTS)
	@${CXX} $(CXXFLAGS) -o $@  $(CPPFLAGS) $(TEST)/test-auto.cpp $(TEST)/test-caso0-cadena-auto.cpp $(TEST)/test-caso0-fecha-auto.cpp $(OBJECTS)

test-P1-consola: test-P1-consola.o $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^

fecha.o: fecha.hpp
	@$(CXX) $(CXXFLAGS) -c fecha.cpp

cadena.o: cadena.hpp
	@$(CXX) $(CXXFLAGS) -c cadena.cpp

fecha_check:
	@make -f Make_check.mk $@

check_Fecha:
	@make -f Make_check.mk $@

cadena_check:
	@make -f Make_check.mk $@

check_Cadena:
	@make -f Make_check.mk $@

checks:
	@make -f Make_check.mk $@

clean:
	@${RM} test-P1-consola test-P1-auto *.o cadena_check fecha_check