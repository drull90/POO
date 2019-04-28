#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <unordered_set>
#include <iostream>

#include "cadena.hpp"
#include "clave.hpp"
#include "tarjeta.hpp"
#include "numero.hpp"
#include "articulo.hpp"

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

		// Operador externo
		friend std::ostream& operator << (std::ostream&, const Usuario&);

		// Funcion externa
		friend void mostrar_carro(std::ostream&, const Usuario&);

		// Metodos
		const 	Cadena& 	id();
		const 	Cadena& 	nombre();
		const	Cadena& 	apellidos();
		const 	Cadena& 	direccion();
		const 	Tarjeta& 	tarjetas();

		void 	es_titular_de		(const Tarjeta&);
		void 	no_es_titular_de	(const Tarjeta&);

		void 	compra				(const Articulo&, size_t = 1);
		const 	Articulos& compra	();
		int 	n_articulos			(const Articulos&);

		// Clase de error Id duplicado
		class Id_duplicado {
			public:
				Id_duplicado(const Cadena&);
				inline const Cadena& idd() { return iden_; }
			private:
				Cadena iden_;
		};

		// Maps
		map<Numero, Tarjeta*> Tarjetas;
		std::unordered_map<Articulo*, size_t> Articulos;

	private:
		Cadena 		iden_;
		Cadena 		nomb_;
		Cadena 		apell_;
		Cadena 		dirr_;
		Clave  		clave_;
		Tarjetas 	tarjetas_;
		Articulos 	articulos_;

};

#endif