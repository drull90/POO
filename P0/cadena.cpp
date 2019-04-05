#include <stdexcept>
#include <cstring>
#include "cadena.hpp"

using namespace std;

Cadena::Cadena(unsigned long int tam, char c) noexcept : tam_{tam} {

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

Cadena& Cadena::operator +=	(const Cadena& cad2) noexcept {

	int tam = this->tam_ + cad2.tam_ + 1;

	char* buff = new char[tam];

	strcpy(buff, this->s_);
	strcat(buff, cad2.s_);
	strcat(buff, "\0");

	delete[] this->s_;

	this->tam_ = tam;
	this->s_ = new char[tam];

	strcpy(this->s_, buff);

	delete[] buff;

	return *this;
}

Cadena operator + (const Cadena& cad1, const Cadena& cad2) noexcept {

	Cadena aux = cad1;
	aux += cad2;

	return aux;
}

bool operator < 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (strcmp(cad1, cad2) < 0); }

bool operator <		(const Cadena& cad1, const char* cad2)	 noexcept { return (strcmp(cad1, cad2) < 0); }

bool operator <		(const char* cad1, 	 const Cadena& cad2) noexcept { return (strcmp(cad1, cad2) < 0); }

bool operator == 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (strcmp(cad1, cad2) == 0); }

bool operator == 	(const Cadena& cad1, const char* cad2) 	 noexcept { return (strcmp(cad1, cad2) == 0); }

bool operator == 	(const char* cad1, const Cadena& cad2) 	 noexcept { return (strcmp(cad1, cad2) == 0); }

bool operator > 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (cad2 < cad1); }

bool operator > 	(const Cadena& cad1, const char* cad2) 	 noexcept { return (cad2 < cad1); }

bool operator > 	(const char* cad1, 	 const Cadena& cad2) noexcept { return (cad2 < cad1); }

bool operator <= 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (!(cad2 < cad1)); }

bool operator <= 	(const Cadena& cad1, const char* cad2) 	 noexcept { return (!(cad2 < cad1)); }

bool operator <= 	(const char* cad1, const Cadena& cad2) 	 noexcept { return (!(cad2 < cad1)); }

bool operator >= 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (!(cad1 < cad2)); }

bool operator >= 	(const Cadena& cad1, const char* cad2) 	 noexcept { return (!(cad1 < cad2)); }

bool operator >= 	(const char* cad1, const Cadena& cad2) 	 noexcept { return (!(cad1 < cad2)); }

bool operator != 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (!(cad1 == cad2)); }

bool operator != 	(const Cadena& cad1, const char* cad2) 	 noexcept { return (!(cad1 == cad2)); }

bool operator != 	(const char* cad1, const Cadena& cad2) 	 noexcept { return (!(cad1 == cad2)); }

const char 	Cadena::operator [] (unsigned long int n) const noexcept{ return s_[n]; }

char& 		Cadena::operator [] (unsigned long int n) noexcept{ return s_[n]; }

const char Cadena::at(unsigned long int n) const { 

	if(n >= tam_) throw out_of_range("Índice no válido");

	return s_[n];
}

char& Cadena::at(unsigned long int n) { 
	
	if(n >= tam_) throw out_of_range("Índice no válido");

	return s_[n]; 
}

Cadena Cadena::substr(unsigned long int indice, unsigned long int tam) const {

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