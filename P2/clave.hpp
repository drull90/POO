#ifndef CLAVE_HPP
#define CLAVE_HPP

#include "cadena.hpp"
#include "sha256.hpp"

class Clave {

	public:
		// Constructor
		Clave(const Cadena&);

		// Enum de error
		enum Razon{CORTA, ERROR_CRYPT};

		// Clase de error
		class Incorrecta {
			public:
				Incorrecta(const Razon);
				inline Razon razon() const noexcept { return razon_; }
			private:
				Razon razon_;
		};

		// Metodos
		inline const Cadena& clave() const 	noexcept { return clave_; }
		bool verifica(const Cadena&) 		noexcept;

	private:
		const Cadena cifrar(const Cadena&);
		Cadena clave_;

};

#endif