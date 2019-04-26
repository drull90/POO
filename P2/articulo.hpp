#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "cadena.hpp"
#include "fecha.hpp"

class Articulo {

	public:

		explicit Articulo(const Cadena&, const Cadena&, const Fecha&, size_t, size_t);

	private:
		// Atributos
		Cadena 	ref_;
		Cadena 	titulo_;
		Fecha	fecha_;
		size_t	precio_;
		size_t	stock_;

};

#endif