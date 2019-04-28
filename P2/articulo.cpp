#include <iostream>

#include "articulo.hpp"
#include "cadena.hpp"
#include "fecha.hpp"

Articulo::Articulo(const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double precio, size_t stock) : ref_{ref}, titulo_{titulo}, fecha_{fecha}, precio_{precio}, stock_{stock} {}

std::ostream& operator << (std::ostream& o, const Articulo& articulo) {

	o << "[" << articulo.referencia()<< "] " << "\"" << articulo.titulo() << "\"" ", " << articulo.f_publi().anno() << ". " << articulo.precio() << "€";

	return o;
}