
CXX 		= clang++
CPPFLAGS 	= -DP0 -I../Tests-auto -I.
CXXFLAGS 	= -std=c++11 -Wall -pedantic -g
VPATH 		= ../Tests-auto:.

all: fecha_check cadena_check
	make -f Make_check.mk fecha_check cadena_check

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

clean:
	make -f Make_check.mk $@