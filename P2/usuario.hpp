#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <unordered_set>
#include <map>
#include <unordered_map>
#include <iostream>

#include "clave.hpp"
#include "cadena.hpp"
#include "articulo.hpp"
#include "numero.hpp"

class Tarjeta;
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

		// Maps
		typedef std::map<Numero, Tarjeta*> Tarjetas;
		typedef std::unordered_map<Articulo*, unsigned int> Articulos;

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
		int 	n_articulos			(const Articulo&);

		// Clase de error Id duplicado
		class Id_duplicado {
			public:
				Id_duplicado(const Cadena&);
				inline const Cadena& idd() { return iden_; }
			private:
				Cadena iden_;
		};

	private:
		Cadena 		iden_;
		Cadena 		nomb_;
		Cadena 		apell_;
		Cadena 		dirr_;
		Clave  		clave_;
		
		Tarjetas 	tarjetas_;
		Articulos 	articulos_;

		typedef std::unordered_set<const Cadena&> Usuarios;
		static 	Usuarios 	usuarios_;

};

#endif