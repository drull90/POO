#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <unordered_set>

#include "cadena.hpp"
#include "clave.hpp"
#include "tarjeta.hpp"

class Usuario {

	public:
		// Constructor
		explicit Usuario(const Cadena&, const Cadena&, const Cadena&, const Cadena&, const Clave&);

		// Destructor
		~Usuario();

		// Constructor eliminado
		Usuario(const Usuario&) = delete;

		// Operador de asignacion eliminado
		void operator = (void*) = delete;

		// Metodos
		const Cadena& 	id();
		const Cadena& 	nombre();
		const Cadena& 	apellidos();
		const Cadena& 	direccion();
		const Tarjeta& 	tarjetas();

		void es_titular_de		(const Tarjeta&);
		void no_es_titular_de	(const Tarjeta&);

		// Clase de error Id duplicado
		class Id_duplicado {
			public:
				Id_duplicado(const Cadena&);
				inline const Cadena& idd() { return iden_; }
			private:
				Cadena iden_;
		};

	private:
		Cadena iden_;
		Cadena nomb_;
		Cadena apell_;
		Cadena dirr_;
		Clave  clave_;

};

#endif