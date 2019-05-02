#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <iostream>

#include "cadena.hpp"
#include "fecha.hpp"

class Articulo {

	public:
		// Constructor
		explicit Articulo(const Cadena&, const Cadena&, const Fecha&, double, size_t);

		// Metodos
		inline const 	Cadena&	referencia() const 	noexcept { return ref_; 	}
		inline const 	Cadena&	titulo()	 const 	noexcept { return titulo_;	}
		inline const 	Fecha&	f_publi()	 const 	noexcept { return fecha_; 	}
		inline double 			precio()	 const 	noexcept { return precio_; 	}
		inline size_t 			stock()		 const 	noexcept { return stock_; 	}
		inline size_t& 			stock()			   	noexcept { return stock_; 	}
		inline double& 			precio() 			noexcept { return precio_; 	}

	private:
		Cadena 	ref_;
		Cadena 	titulo_;
		Fecha	fecha_;
		double	precio_;
		size_t	stock_;

};

// Operador <<
std::ostream& operator << (std::ostream& o, const Articulo&);

#endif