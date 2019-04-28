#include "tarjeta.hpp"

bool luhn(const Cadena&);

Numero::Numero(const Cadena& num) {
	Cadena cad = num;
	int j = 0;
	for(auto i = num.begin(); i != num.end(); ++i) {
		if(*i != ' ') {
			if(int(*i) >= 48 && int(*i) <= 57)
				cad[j++] = *i;
			else
				throw Incorrecto(DIGITOS);
		}
	}
	cad 	= cad.substr(0,j);
	int tam = cad.length();

	if(tam < 13 || tam > 19) 	throw Incorrecto(LONGITUD);
	if(luhn(cad) != true) 		throw Incorrecto(NO_VALIDO);

	num_ = cad;
}

Numero::Incorrecto::Incorrecto(const Razon& r) : razon_{r} {}

bool Numero::operator < (const Numero& num) const { return (this->num_ < num.num_); }

Tarjeta::Tarjeta(const Numero& num, Usuario& const us, const Fecha& fe) : num_{num}, titular_{&us}, caducidad_{fe}, estado_{true} {}