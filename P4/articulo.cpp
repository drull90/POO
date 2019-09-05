#include <iostream>
#include <iomanip>

#include "articulo.hpp"
#include "cadena.hpp"
#include "fecha.hpp"

Autor::Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& direccion) : nombre_{nombre}, apellido_{apellido}, direccion_{direccion} {}

Articulo::Articulo(const Articulo::Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio) : ref_{referencia}, titulo_{titulo}, fecha_{fecha}, precio_{precio}, autores_{autores}{
	if(autores.empty()) throw Autores_vacios();
}

std::ostream& operator << (std::ostream& o, const Articulo& articulo) {

	o << "[" << articulo.referencia() << "] " << "\"" << articulo.titulo() << "\", de ";

	auto autores = articulo.autores();
	auto i 		 = autores.begin();

	o << (*i)->apellidos();

	while( ++i != autores.end())
		o << ", " << (*i)->apellidos();

	o << ". " 		<< std::fixed 			<< articulo.f_publi().anno()
	  << ". " 		<< std::setprecision(2) << articulo.precio() << " €"
	  << std::endl 	<< "\t";
	  
	articulo.impresion_especifica(o);

	return o;
}

ArticuloAlmacenable::ArticuloAlmacenable(const Articulo::Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, size_t stock) : Articulo(autores, referencia, titulo, fecha, precio), stock_(stock) {}

LibroDigital::LibroDigital(const Articulo::Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, const Fecha& fechaExp) : Articulo(autores, referencia, titulo, fecha, precio), fechaExp_(fechaExp) {}

Libro::Libro(const Articulo::Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned pag, unsigned stock) : ArticuloAlmacenable(autores, referencia, titulo, fecha, precio, stock), pag_(pag){}

Cederron::Cederron(const Articulo::Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& fecha, double precio, unsigned tam, unsigned stock) : ArticuloAlmacenable(autores, referencia, titulo, fecha, precio, stock), tam_(tam){}

void LibroDigital::impresion_especifica(std::ostream& o) const {
	o << "A la venta hasta el " << fechaExp_ << ".";
}

void Libro::impresion_especifica(std::ostream& o) const {
	o << pag_ << " págs., " << stock_ << " unidades.";
}

void Cederron::impresion_especifica(std::ostream& o) const {
	o << tam_ << " MB, " << stock_ << " unidades.";
}