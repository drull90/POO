#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "cadena.hpp"
#include "clave.hpp"

class Usuario {

	public:

	private:
		Cadena iden_;
		Cadena nomb_;
		Cadena apell_;
		Cadena dirr_;
		Clave  clave_;

};

#endif