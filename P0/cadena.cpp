#include <iostream>
#include <stdio.h>
#include <string.h>
#include "cadena.hpp"

using namespace std;

Cadena::Cadena(unsigned int tam, char c) noexcept : tam_{tam} {

	unsigned int i = 0;
	s_ = new char[tam + 1];				// Caracter terminador \0 +1
	for(i = 0; i < tam; ++i){
		s_[i] = c;
	}
	s_[i] = '\0';

}

Cadena::Cadena(const Cadena& cad) noexcept {

	tam_ = cad.tam_;
	s_ = new char[tam_ + 1];
	strcpy(s_, cad.s_);

}

Cadena::Cadena(const char* cad) noexcept {

	tam_ = strlen(cad);
	s_ = new char[tam_ + 1];
	strcpy(s_, cad);
	strcat(s_, "\0");

}

Cadena::~Cadena(){

	delete[] s_;
	tam_ = 0;

}

inline unsigned int Cadena::length() noexcept { return tam_; }

/**
 * Asignacion cad a cad
 */
Cadena& Cadena::operator = (Cadena& cad) noexcept {

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
Cadena& Cadena::operator = (const char* cad) noexcept {

	delete[] s_;
	tam_ = strlen(cad);
	s_ = new char[tam_ + 1];
	strcpy(s_, cad);
	strcat(s_, "\0");

	return *this;
}

Cadena& operator +=	(Cadena& cad1, Cadena& cad2) noexcept {

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

Cadena operator + (Cadena& cad1, Cadena& cad2) noexcept {

	Cadena aux = cad1;
	aux += cad2;

	return aux;
}

bool operator < 	(Cadena& cad1, Cadena& cad2) noexcept { return (strcmp(cad1, cad2) < 0); }

bool operator == 	(Cadena& cad1, Cadena& cad2) noexcept { return (strcmp(cad1, cad2) == 0); }

bool operator > 	(Cadena& cad1, Cadena& cad2) noexcept { return (cad2 < cad1); }

bool operator <= 	(Cadena& cad1, Cadena& cad2) noexcept { return (!(cad2 < cad1)); }

bool operator >= 	(Cadena& cad1, Cadena& cad2) noexcept { return (!(cad1 < cad2)); }

bool operator != 	(Cadena& cad1, Cadena& cad2) noexcept { return (!(cad1 == cad2)); }

const char 	Cadena::operator [] (unsigned int n) const noexcept{ return s_[n]; }

char 		Cadena::operator [] (unsigned int n) noexcept{ return s_[n]; }

const char Cadena::at(unsigned int n) const { 

	if(n >= tam_) throw out_of_range("Índice no válido");

	return s_[n];
}

char Cadena::at(unsigned int n) { 
	
	if(n >= tam_) throw out_of_range("Índice no válido");

	return s_[n]; 
}

Cadena Cadena::substr(unsigned int indice, unsigned int tam) const {

	if(indice > tam_ || indice + tam > tam_) throw out_of_range("Rango substr no válido");

	char* buff = new char[tam];
	int j = 0;
	for(unsigned int i = indice; i <= indice+tam; ++i){
		buff[j] = s_[i];
		++j;
	}

	Cadena aux{buff};

	delete[] buff;

	return aux;
}

Cadena::operator const char*() const { return s_; }