
#include "tarjeta.hpp"


Tarjeta::Tarjeta(const Numero& num, Usuario* const us, const Fecha& fe) : num_{num}, titular_{us}, caducidad_{fe} {}
