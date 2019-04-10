
DSL			:= ../dsl-comprobaciones/
DIR			= ../Tests-auto/
CXX 		:= clang++
CPPFLAGS 	:= -DP0 -I${DIR}
CXXFLAGS 	:= -std=c++11 -Wall -pedantic
VPATH 		:= ../Tests-auto:.
SOURCES		:= fecha.cpp cadena.cpp
OBJECTS     := $(SOURCES:.cpp=.o)


################################# TEST - AUTO ##############################################
test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o $(OBJECTS)

test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

################################# TEST-P0-CONSOLA ##########################################
test-P0-consola: test-P0-consola.o $(OBJECTS)
	@echo "Link test-P0-consola.o"
	@$(CXX) -o $@ test-P0-consola.o $(OBJECTS)

test-P0-consola.o: test-P0-consola.cpp
	@$(CXX) $(CXXFLAGS) -c test-P0-consola.cpp

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
	@${RM} *.o test-P0-consola test-P0-auto fecha_check cadena_check $(DSL)*.o