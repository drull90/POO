#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <unordered_set>
#include <map>
#include <unordered_map>
#include <iostream>

#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

class Numero;
class Tarjeta;

class Clave {
	public:
		enum Razon{CORTA, ERROR_CRYPT};
		// Constructor
		Clave(const char*);

		class Incorrecta {
			public:
				Incorrecta(const Razon);
				inline Razon razon() const noexcept { return razon_; }
			private:
				Razon razon_;
		};

		// Metodos
		inline const Cadena& clave() const 	noexcept { return clave_; }
		bool verifica(const Cadena&) const	noexcept;
	private:
		//const Cadena cifrar(const Cadena&) const;
		Cadena clave_;
};

class Usuario {

	public:
		// Constructor
		explicit Usuario(const Cadena&, const Cadena&, const Cadena&, const Cadena&, const Clave&);

		// Eliminar la copia de usuarios
		Usuario(const Usuario&) 			= delete;
		Usuario(Usuario&) 					= delete;
		void operator = (const Usuario&) 	= delete;
		void operator = (Usuario&) 			= delete;

		// Destructor
		~Usuario();

		friend std::ostream& operator << (std::ostream&, const Usuario&);

		// Maps
		typedef std::map			<Numero, 	Tarjeta*> 		Tarjetas;
		typedef std::unordered_map	<Articulo*, size_t> 		Articulos;
		typedef std::unordered_set	<Cadena> 					Usuarios;

		// Clase de error
		class Id_duplicado {
			public:
				Id_duplicado(const Cadena&);
				inline const Cadena& idd() const noexcept { return iden_; }
			private:
				Cadena iden_;
		};

		// Metodos
		inline const 	Cadena& 	id()		const noexcept	{ return iden_; 	}
		inline const 	Cadena& 	nombre()	const noexcept	{ return nomb_;		}
		inline const	Cadena& 	apellidos()	const noexcept	{ return apell_;	}
		inline const 	Cadena& 	direccion()	const noexcept 	{ return dirr_;		}
		const 			Tarjetas& 	tarjetas()	const noexcept 	{ return tarjetas_;	}

		void 	es_titular_de		(const Tarjeta&);
		void 	no_es_titular_de	(const Tarjeta&);

		inline  const 	Articulos& 	compra	() const noexcept { return articulos_;	 		}
		inline 	size_t 	n_articulos			() const noexcept { return articulos_.size(); 	}

		void 	compra	(const Articulo&, size_t = 1);
		
	private:
		static 		Usuarios users;

		Cadena 		iden_;
		Cadena 		nomb_;
		Cadena 		apell_;
		Cadena 		dirr_;
		Clave  		clave_;
		
		Tarjetas 	tarjetas_;
		Articulos 	articulos_;

};

void mostrar_carro(std::ostream&, const Usuario&);

#endif