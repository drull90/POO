#include <iostream>
#include <stdio.h>
#include <string.h>
#include "cadena.hpp"

using namespace std;

Cadena::Cadena(unsigned int tam, char c) : tam_{tam} {

	unsigned int i = 0;
	s_ = new char[tam + 1];				// Caracter terminador \0 +1
	for(i = 0; i < tam; ++i){
		s_[i] = c;
	}
	s_[i] = '\0';

}

Cadena::Cadena(const Cadena& cad){

	strcpy(s_, cad.s_);
	

}

Cadena::Cadena(const char* cad){



}

Cadena::~Cadena(){

	delete[] s_;
	tam_ = 0;

}

unsigned int Cadena::length(){
	return tam_;
}

int main(){

	Cadena cad{5, 'X'};

	cout << cad.length() << endl;

	delete &cad;

	cout << cad.length() << endl;

	return 0;
}