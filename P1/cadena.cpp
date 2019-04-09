#include <stdexcept>
#include <cstring>
#include <iostream>

#include "cadena.hpp"

/**
 * Constructor tam y char, tam, o predeterminado
 */
Cadena::Cadena(unsigned long int tam, char c) noexcept : tam_{tam} {

	unsigned int i = 0;
	s_ = new char[tam + 1];				// Caracter terminador \0 +1
	for(i = 0; i < tam; ++i)
		s_[i] = c;
	s_[i] = '\0';

}

/**
 * Constructor de copia
 */
Cadena::Cadena(const Cadena& cad) noexcept : tam_{cad.tam_} {

	s_ = new char[tam_ + 1];
	strcpy(s_, cad.s_);

}

/**
 * Constructor de movimiento
 */
Cadena::Cadena(Cadena&& cadena) noexcept : tam_{cadena.tam_} {

	s_ = cadena.s_;
	cadena.tam_ = 0;
	cadena.s_ = nullptr;
	
}

/**
 * Constructor de conversion const char* a Cadena
 */
Cadena::Cadena(const char* cad) noexcept {

	tam_ = strlen(cad);
	s_ = new char[tam_ + 1];
	strcpy(s_, cad);
	strcat(s_, "\0");

}

/**
 * Destructor
 */
Cadena::~Cadena(){

	delete[] s_;
	tam_ = 0;

}

/**
 * Muestra tamaño de la cadena
 */
inline unsigned long int Cadena::length() noexcept { return tam_; }

/**
 * Asignacion cad a cad
 */
Cadena& Cadena::operator = (const Cadena& cad) noexcept {

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
/**
 * Asignacion con movimiento
 */
Cadena&	Cadena::operator = (Cadena&& cad) noexcept {

	s_ = cad.s_;
	cad.s_ = nullptr;
	tam_ = cad.tam_;
	cad.tam_ = 0;

	return *this;
}

/**
 * Concatenacion con asignacion
 */
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

/**
 * Concatenacion
 */
Cadena operator + (const Cadena& cad1, const Cadena& cad2) noexcept {

	Cadena aux = cad1;
	aux += cad2;

	return aux;
}

// Comparacion de cadenas
bool operator < 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (strcmp(cad1.c_str(), cad2.c_str()) < 0); }
bool operator == 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (strcmp(cad1.c_str(), cad2.c_str()) == 0); }
bool operator > 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (cad2 < cad1); }
bool operator <= 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (!(cad2 < cad1)); }
bool operator >= 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (!(cad1 < cad2)); }
bool operator != 	(const Cadena& cad1, const Cadena& cad2) noexcept { return (!(cad1 == cad2)); }

/**
 * Operador [] para acceder a elemento Cadena constante
 */
const char 	Cadena::operator [] (unsigned long int n) const noexcept{ return s_[n]; }

/**
 * Operador [] para acceder a elemento Cadena
 */
char& 		Cadena::operator [] (unsigned long int n) noexcept{ return s_[n]; }

/**
 * Metodo para acceder a elemento Cadena constante
 */
const char Cadena::at(unsigned long int n) const { 

	if(n >= tam_ || n < 0) throw std::out_of_range("Índice no válido");

	return s_[n];
}

/**
 * Metodo para acceder a elemento Cadena
 */
char& Cadena::at(unsigned long int n) { 
	
	if(n >= tam_ || n < 0) throw std::out_of_range("Índice no válido");

	return s_[n]; 
}

/**
 * Metodo para devolver un substring de la cadena
 */
Cadena Cadena::substr(unsigned long int indice, unsigned long int tam) const {

	if(indice > tam_ || indice + tam > tam_) throw std::out_of_range("Rango substr no válido");

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

/**
 * funcion que devuelve const char*
 */
const char* Cadena::c_str() const noexcept { return s_; }

/**
 * Operador de inserccion
 */
std::ostream& operator << (std::ostream& o, const Cadena& cad) noexcept {

	o << cad.c_str();

	return o;
}

/**
 * Operador de extraccion
 */
std::istream& operator >> (std::istream& i, Cadena& cad) {

	char *buff = new char[32];
	i >> buff;

	cad = buff;
	delete[] buff;

	return i;
}

// Funciones de iteradores
Cadena::iterator 				Cadena::begin() 			{ return s_; }
Cadena::iterator 				Cadena::end() 				{ return s_ + tam_; }
Cadena::reverse_iterator 		Cadena::rbegin() 			{ return reverse_iterator(end()); }
Cadena::reverse_iterator 		Cadena::rend() 				{ return reverse_iterator(begin()); }
Cadena::const_iterator 			Cadena::begin() 	const 	{ return s_; }
Cadena::const_iterator 			Cadena::end() 		const 	{ return s_ + tam_; }
Cadena::const_iterator 			Cadena::cbegin() 	const 	{ return begin(); }
Cadena::const_iterator 			Cadena::cend() 		const 	{ return end(); }
Cadena::const_reverse_iterator 	Cadena::crbegin() 	const 	{ return const_reverse_iterator(cend()); }
Cadena::const_reverse_iterator 	Cadena::crend() 	const 	{ return const_reverse_iterator(cbegin()); }
Cadena::const_reverse_iterator 	Cadena::rbegin() 	const 	{ return const_reverse_iterator(end()); }
Cadena::const_reverse_iterator 	Cadena::rend() 		const 	{ return const_reverse_iterator(begin()); }