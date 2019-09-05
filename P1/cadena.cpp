#include <stdexcept>
#include <cstring>
#include <iostream>
#include <iomanip>

#include "cadena.hpp"

/**
 * Constructor tam y char, tam, o predeterminado
 */
Cadena::Cadena(size_t tam, char c) noexcept : s_{new char[tam + 1]}, tam_{tam} {
	memset(s_, c, tam);
	s_[tam] = '\0';
}

/**
 * Constructor de copia
 */
Cadena::Cadena(const Cadena& cad) noexcept : s_{new char[cad.tam_ + 1]}, tam_{cad.tam_} {
	std::memcpy(s_, cad.s_, cad.tam_ + 1);
}

/**
 * Constructor de movimiento
 */
Cadena::Cadena(Cadena&& cadena) noexcept : s_{nullptr}, tam_{0} {
	*this = std::move(cadena);
}

/**
 * Constructor de conversion const char* a Cadena
 */
Cadena::Cadena(const char* cad) noexcept : s_{new char[strlen(cad) + 1]}, tam_{strlen(cad)} {
	std::memcpy(s_, cad, tam_);
	s_[tam_] = '\0';
}

/**
 * Destructor
 */
Cadena::~Cadena(){

	delete[] s_;
	s_ = nullptr;
	tam_ = 0;

}

/**
 * Asignacion cad a cad
 */
Cadena& Cadena::operator = (const Cadena& cad) noexcept {

	if(this != &cad){
		delete[] s_;
		tam_ = cad.tam_;
		s_ = new char[tam_ + 1];
		strcpy(s_, cad.s_ );
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
	std::memcpy(s_, cad, tam_);
	s_[tam_] = '\0';

	return *this;
}
/**
 * Asignacion con movimiento
 */
Cadena&	Cadena::operator = (Cadena&& cad) noexcept {

	if( this != &cad) {
		delete[] s_;
		s_ = cad.s_;
		tam_ = cad.tam_;
		cad.tam_ = 0;
		cad.s_ = nullptr;
	}

	return *this;
}

/**
 * Concatenacion con asignacion
 */
Cadena& Cadena::operator +=	(const Cadena& cad2) noexcept {

	tam_ += cad2.tam_;
	char* buff = new char [tam_ + 1];

	strcpy(buff, s_);
	strcat(buff, cad2.s_);

	buff[tam_] = '\0';
	delete[] s_;

	s_ = buff;

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
const char Cadena::operator [] (size_t n) const noexcept{ return s_[n]; }

/**
 * Operador [] para acceder a elemento Cadena
 */
char& Cadena::operator [] (size_t n) noexcept{ return s_[n]; }

/**
 * Metodo para acceder a elemento Cadena constante
 */
const char Cadena::at(size_t n) const { 

	if(n >= tam_) throw std::out_of_range("Índice no válido");

	return s_[n];
}

/**
 * Metodo para acceder a elemento Cadena
 */
char& Cadena::at(size_t n) { 
	
	if(n >= tam_) throw std::out_of_range("Índice no válido");

	return s_[n]; 
}

/**
 * Metodo para devolver un substring de la cadena
 */
Cadena Cadena::substr(size_t indice, size_t tam) const {

	if(indice > tam_ ||  tam > tam_ - indice ) throw std::out_of_range("Rango substr no válido");

	char* buff = new char[tam + 1]{'\0'};
	int j = 0;
	for(size_t i = 0; i < tam; ++i){
		buff[j] = s_[i + indice];
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

	char* aux = new char[33]{'\0'};
	i >> std::setw(33) >> aux;
	cad = Cadena(aux);
	delete[] aux;

	return i;
}

// Funciones de iteradores
Cadena::iterator 				Cadena::begin() 			{ return s_; 		}
Cadena::iterator 				Cadena::end() 				{ return s_ + tam_; }
Cadena::const_iterator 			Cadena::begin() 	const 	{ return s_; 		}
Cadena::const_iterator 			Cadena::end() 		const 	{ return s_ + tam_; }

Cadena::reverse_iterator 		Cadena::rbegin() 			{ return reverse_iterator(end()); 			}
Cadena::reverse_iterator 		Cadena::rend() 				{ return reverse_iterator(begin()); 		}
Cadena::const_reverse_iterator 	Cadena::rbegin() 	const 	{ return const_reverse_iterator(cend()); 	}
Cadena::const_reverse_iterator 	Cadena::rend() 		const 	{ return const_reverse_iterator(cbegin()); 	}

Cadena::const_iterator 			Cadena::cbegin() 	const 	{ return begin(); 							}
Cadena::const_iterator 			Cadena::cend() 		const	{ return end();								}
Cadena::const_reverse_iterator 	Cadena::crbegin()	const 	{ return const_reverse_iterator(end());		}
Cadena::const_reverse_iterator 	Cadena::crend() 	const 	{ return const_reverse_iterator(begin());	}