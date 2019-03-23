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

	tam_ = cad.tam_;
	s_ = new char[tam_ + 1];
	strcpy(s_, cad.s_);

}

Cadena::Cadena(const char* cad){

	tam_ = strlen(cad);
	s_ = new char[tam_ + 1];
	strcpy(s_, cad);
	strcat(s_, "\0");

}

Cadena::~Cadena(){

	delete[] s_;
	tam_ = 0;

}

unsigned int Cadena::length(){
	return tam_;
}

/**
 * Asignacion cad a cad
 */
Cadena& Cadena::operator = (Cadena& cad) {

	if(this != &cad){
		delete[] s_;
		tam_ = cad.tam_;
		s_ = new char[tam_ + 1];
		strcpy(s_, cad.s_);
	}

	return *this;
}

/**
 * Asignacion const char* a cad
 */
Cadena& Cadena::operator = (const char* cad) {

	delete[] s_;
	tam_ = strlen(cad);
	s_ = new char[tam_ + 1];
	strcpy(s_, cad);

	return *this;
}

Cadena& operator +=	(Cadena& cad1, Cadena& cad2){

	char* aux;
	aux = new char[cad1.tam_ + cad2.tam_ + 1];
	strcat(aux, cad1.s_);
	strcat(aux, cad2.s_);

	delete[] cad1.s_;
	cad1.tam_ = strlen(aux);
	cad1.s_ = new char[cad1.tam_ + 1];
	strcpy(cad1.s_, aux);

	delete[] aux;

	return cad1;
}

Cadena operator + (Cadena& cad1, Cadena& cad2){

	Cadena aux = cad1;
	aux += cad2;

	return aux;
}

bool operator < 	(Cadena& cad1, Cadena& cad2) { 
	
	puts(cad1);
	puts(cad2);

	return (strcmp(cad1, cad2) < 0); }

bool operator == 	(Cadena& cad1, Cadena& cad2) { return (strcmp(cad1, cad2) == 0); }

bool operator > 	(Cadena& cad1, Cadena& cad2) { return (cad2 < cad1); }

bool operator <= 	(Cadena& cad1, Cadena& cad2) { return (!(cad2 < cad1)); }

bool operator >= 	(Cadena& cad1, Cadena& cad2) { return (!(cad1 < cad2)); }

bool operator != 	(Cadena& cad1, Cadena& cad2) { return (!(cad1 == cad2)); }

Cadena::operator const char*() const { return s_; }