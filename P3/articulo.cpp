#include <iostream>
#include <iomanip>

#include "articulo.hpp"
#include "cadena.hpp"
#include "fecha.hpp"

Articulo::Articulo(const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double precio, size_t stock) : ref_{ref}, titulo_{titulo}, fecha_{fecha}, precio_{precio}, stock_{stock} {}

std::ostream& operator << (std::ostream& o, const Articulo& articulo) {

	char art[5];
	sprintf(art, "%d", articulo.f_publi().anno());

	o << "[" << articulo.referencia() << "] " << "\"" << articulo.titulo() << "\"" ", ";
	o << art;
	o << ". " << std::fixed << std::setprecision(2) << articulo.precio() << " €";

	return o;
}