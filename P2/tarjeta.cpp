#include <unordered_set>
#include <iomanip>
#include <ctype.h>

#include "tarjeta.hpp"
#include "fecha.hpp"
#include "cadena.hpp"
#include "usuario.hpp"


bool luhn(const Cadena&);

Numero::Numero(const Cadena& num) {

	char cad[20];
	int j = 0;

	for (auto i = num.begin(); i != num.end(); ++i) {
		if (!isspace(*i)){
			if (*i < '0' || *i > '9') throw Incorrecto(Razon::DIGITOS);
			cad[j] = *i;
			++j;
		}
  	}
	cad[j] = '\0';

	Cadena numAux{cad};

	int tam = j;

	if(tam < 13 || tam > 19) throw Incorrecto(LONGITUD);
	if(!luhn(numAux)) 		 throw Incorrecto(NO_VALIDO);

	num_ = numAux;
}

Numero::Incorrecto::Incorrecto(const Razon& r) : razon_{r} {}

bool Numero::operator < (const Numero& num) const noexcept { return this->num_ < num.num_; }

Tarjeta::Tarjetas Tarjeta::tarjetas_;

Tarjeta::Tarjeta(const Numero& num, Usuario& us, const Fecha& fe) : num_{num}, caducidad_{fe}, estado_{true}, titular_{&us} {

	if(caducidad_ < Fecha()) throw Tarjeta::Caducada(caducidad_);
	if(tarjetas_.insert(static_cast<Cadena>(num)).second == false) throw Tarjeta::Num_duplicado(num);

	const_cast<Usuario*>(titular_)->es_titular_de(*this);

	tipo_ = tipoTarjeta();

}

Tarjeta::~Tarjeta() {

	if(titular_ != nullptr) const_cast<Usuario*>(titular_)->no_es_titular_de(*this);

	tarjetas_.erase(static_cast<Cadena>(num_));

}

void Tarjeta::anula_titular(){

	estado_ 	= false;
	titular_	= nullptr;

}

Tarjeta::Tipo Tarjeta::tipoTarjeta(){

	Tipo tipo;

	switch (num_[0]) {
		case '3':
			if(num_[1] == '4' || num_[1] == '7')
				tipo = AmericanExpress;
			else
				tipo = JCB;
			break;
		case '4':
			tipo = VISA;
			break;
		case '5':
			tipo = Mastercard;
			break;
		case '6':
			tipo = Maestro;
			break;
		default:
			tipo = Otro;

	}

	return tipo;
}

std::ostream& operator << (std::ostream& o, const Tarjeta& t) {

	Cadena nomApell{t.titular()->nombre()};
	nomApell += " ";
	nomApell += t.titular()->apellidos();

	for(auto i = nomApell.begin(); i != nomApell.end(); ++i)
		*i = toupper(*i);

	o << t.tipo() 					<< std::endl;
	o << t.numero() 				<< std::endl;
	o << nomApell					<< std::endl;
	o << "Caduca:";
	o << std::setfill('0') 			<< std::setw(2);
	o << t.caducidad().mes() 		<< "/";
	o << (t.caducidad().anno() % 100);

	return o;
}

std::ostream& operator << (std::ostream& o, const Tarjeta::Tipo& t) {

	switch(t) {
        case Tarjeta::VISA: 			o << "VISA"; 			break;
        case Tarjeta::Mastercard: 		o << "Mastercard";		break;
        case Tarjeta::Maestro: 			o << "Maestro"; 		break;
        case Tarjeta::JCB: 				o << "JCB"; 			break;
        case Tarjeta::AmericanExpress: 	o << "AmericanExpress"; break; 
		default: 						o << "Otro";
    }
    return o;
}

bool Tarjeta::operator < (const Tarjeta& t) const noexcept{
	return this->num_ < t.num_;
}

Tarjeta::Caducada::Caducada(const Fecha& f) : fecha_{f} {}

Tarjeta::Num_duplicado::Num_duplicado(const Numero& n) : num_{n} {}