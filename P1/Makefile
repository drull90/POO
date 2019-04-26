DSL   		:= ../dsl-comprobaciones/
TEST		:= ../Tests-auto/

CXX 		:= clang++
CPPFLAGS	:= -DP1 -I${DSL} ${TEST}
CXXFLAGS 	:= -std=c++11 -Wall -pedantic -g
SOURCES		:= fecha.cpp cadena.cpp
OBJECTS     := $(SOURCES:.cpp=.o)
EXES		:= fecha_check cadena_check test-P1-consola test-P1-auto


################################# TEST - AUTO #####################-DP0 -I../dsl-comprobaciones#########################
test-P1-auto: ../Tests-auto/test-caso0-fecha-auto.o ../Tests-auto/test-caso0-cadena-auto.o ../Tests-auto/test-auto.o $(OBJECTS)
	$(CXX) -o $@
test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o:
	$(CXX) $(CXXFLAGS) -I ${TEST} -c test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp test-auto.cpp 

################################# TEST-P0-CONSOLA ##########################################
test-P1-consola: test-P1-consola.o $(OBJECTS)
	@echo "Link test-P1-consola.o"
	@$(CXX) -o $@ $^

test-P1-consola.o: test-P1-consola.cpp
	@$(CXX) $(CXXFLAGS) -c $^

#################################### FECHA.O ###############################################
fecha.o: fecha.hpp fecha.cpp
	@$(CXX) $(CXXFLAGS) -c fecha.cpp

#################################### CADENA.O ##############################################
cadena.o: cadena.hpp cadena.cpp
	@$(CXX) $(CXXFLAGS) -c cadena.cpp

############################### CHECKS DEL CODIGO FUENTE ###################################
fecha_check:
	make -f Make_check.mk $@

check_Fecha:
	make -f Make_check.mk $@

cadena_check:
	make -f Make_check.mk $@

check_Cadena:
	make -f Make_check.mk $@

checks:
	make -f Make_check.mk $@

##################################### CLEAN #################################################
clean:
	@${RM} $(EXES) *.o $(DSL)*.o $(TEST)*.o