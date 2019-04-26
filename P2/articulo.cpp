#include <iostream>

#include "articulo.hpp"
#include "cadena.hpp"
#include "fecha.hpp"

Articulo::Articulo(const Cadena& ref, const Cadena& titulo, const Fecha& fecha, double precio, size_t stock) : ref_{ref}, titulo_{titulo}, fecha_{fecha}, precio_{precio}, stock_{stock} {}

std::ostream& operator << (std::ostream& o, const Articulo& articulo) {

    o << articulo.ref_ << ", " << articulo.fecha_.anno << ". " << articulo.precio;

    return o;
}

int main(){

    Articulo a{"0001", "Fundamentos de C++", "20/11/2012", 29.95, 10};

    std::cout << a << std::endl;

    return 0;
}