#ifndef TARJETA_HPP
#define TARJETA_HPP

#include <iostream>
#include <unordered_set>

#include "fecha.hpp"
#include "usuario.hpp"
#include "cadena.hpp"

class Usuario;

class Numero {
	public:
		// Constructor
		explicit Numero(const Cadena&);
		// Enum de error
		enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
		class Incorrecto {
			public:
				Incorrecto(const Razon&);
				inline const Razon razon() 	const noexcept { return razon_; }
			private:
				Razon razon_;
		};
		// Operadores
		inline 	operator const char* () 	const noexcept { return num_.c_str(); }
		bool 	operator < (const Numero&) 	const noexcept;
	private:
		Cadena num_;
};

class Tarjeta {

	public:
		// Constructor
		explicit Tarjeta(const Numero&, Usuario&, const Fecha&);

		// Destructor
		~Tarjeta();

		// Enum tipo
		enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

		// Asignaciones eliminadas
		Tarjeta			(const Tarjeta&) 	= delete;
		Tarjeta			(Tarjeta&) 			= delete;
		void operator = (const Tarjeta&) 	= delete;
		void operator = (Tarjeta&) 			= delete;

		// Sobrecarga de operadores
		bool operator < (const Tarjeta&) const noexcept;

		typedef 	std::unordered_set<Cadena> Tarjetas;

		// Metodos
		inline const Tipo& 		tipo()					const 	{ return tipo_;			}
		inline const Numero& 	numero()				const 	{ return num_;  		}
		inline const Fecha& 	caducidad() 			const 	{ return caducidad_;	}
		inline const Usuario* 	titular() 				const	{ return titular_;		}
		inline const bool 		activa()				const 	{ return estado_;		}
		inline const bool		activa(bool b = true) 			{ return estado_ = b; 	}

		// Clase de error Tarjeta Desactivada
		class Desactivada { };

		// Clase de error fecha caducada
		class Caducada {
			public:
				Caducada(const Fecha&);
				inline const Fecha& cuando() const noexcept { return fecha_; }
			private:
				Fecha fecha_;
		};

		// Clase de error Num duplicado
		class Num_duplicado {
			public:
				Num_duplicado(const Numero&);
				inline const Numero& que() const noexcept { return num_; }
			private:
				Numero num_;
		};

	private:
		friend 		class Usuario;
		void 		anula_titular();
		Tipo 		tipoTarjeta();

		static		Tarjetas tarjetas_;
		
		Tipo 		tipo_;
		Numero  	num_;
		Fecha   	caducidad_;
		bool    	estado_;
		Usuario 	const* titular_;

};

std::ostream& operator << (std::ostream&, const Tarjeta::Tipo&);
std::ostream& operator << (std::ostream&, const Tarjeta&);

#endif