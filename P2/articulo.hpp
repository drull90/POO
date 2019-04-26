#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <iostream>

#include "cadena.hpp"
#include "fecha.hpp"

class Articulo {

	public:
		// Constructor
		explicit Articulo(const Cadena&, const Cadena&, const Fecha&, double, size_t);

		// Constructores eliminados
		Articulo(Articulo&) = delete;

		// Operadores externos
		friend std::ostream& operator << (std::ostream& o, const Articulo&);

		// Metodos
		inline const 	Cadena&	referencia() 	const 	{ return ref_; 		}
		inline const 	Cadena&	titulo()		const 	{ return titulo_;	}
		inline const 	Fecha&	f_publi()		const 	{ return fecha_; 	}
		inline double 			precio()		const 	{ return precio_; 	}
		inline size_t 			stock()			const 	{ return stock_; 	}
		inline size_t& 			stock()					{ return stock_; 	}
		inline double& 			precio() 				{ return precio_; 	}

	private:
		// Atributos
		Cadena 	ref_;
		Cadena 	titulo_;
		Fecha	fecha_;
		double	precio_;
		size_t	stock_;

};

#endif