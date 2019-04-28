#ifndef TARJETA_HPP
#define TARJETA_HPP

#include <iostream>

#include "fecha.hpp"
#include "usuario.hpp"

class Usuario;
class Numero {
	public:
		// Constructor
		explicit Numero(const Cadena&);
		// Enum de error
		enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
		class Incorrecto {
			public:
				Incorrecto(Razon);
				inline Razon razon() { return razon_; }
			private:
				Razon razon_;
		};
		// Operadores
		inline 	operator const char* () const { return num_.c_str(); }
		bool 	operator < (Numero&);
	private:
		Cadena num_;
};

class Tarjeta {

	public:
		// Constructor
		explicit Tarjeta(const Numero&, Usuario* const, const Fecha&);

		// Destructor
		~Tarjeta();

		// Enum tipo
		enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

		// Constructor eliminado
		Tarjeta(Tarjeta& ) = delete;

		// Operador de asignacion eliminado
		void operator = (void*) = delete;

		// Sobrecarga de operadores
		// Internos
		bool operator < (Tarjeta&);
		// Externos
		friend std::ostream& operator << (std::ostream&, Tarjeta&);
		friend std::ostream& operator << (std::ostream&, Tipo);

		// Metodos
		void 			anula_titular();

		Tipo& 			tipo();
		Numero& 		numero();
		const Usuario* 	titular();
		Fecha& 			caducidad();
		bool 			activa();
		bool			activa(bool = true);

		// Clase de error Tarjeta Desactivada
		class Desactivada { };

		// Clase de error fecha caducada
		class Caducada {
			public:
				Caducada(const Fecha&);
				inline Fecha& cuando() { return fecha_; }
			private:
				Fecha fecha_;
		};

		// Clase de error Num duplicado
		class Num_duplicado {
			public:
				Num_duplicado(const Numero&);
				inline Numero& num() { return num_; }
			private:
				Numero num_;
		};

	private:
		Tipo tipoTarjeta();
		Tipo tipo_;
		Numero  num_;
		Fecha   caducidad_;
		bool    estado_;
		Usuario* const titular_;

};

#endif