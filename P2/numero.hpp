#ifndef NUMERO_HPP
#define NUMERO_HPP

#include "cadena.hpp"

class Numero {

	public:
		// Constructor
		explicit Numero(const Cadena&);

		// Enum de error
		enum Razon {LONGITUD, DIGITOS, NO_VALIDO};

		// Clase Incorrecto
		class Incorrecto {
			public:
				Incorrecto(Razon);
				inline Razon razon() { return razon_; }
			private:
				Razon razon_;
		};

		// Operador de conversion
		inline operator const char* () const { return num_.c_str(); }

		// Operador de comparacion
		bool operator < (Numero&);
		
	private:
		Cadena num_;

};

#endif