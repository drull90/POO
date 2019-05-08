#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "tarjeta.hpp"
#include "fecha.hpp"

class Pedido {

	public:
		

	private:
		int 		nPedidos_;
		int 		importe;
		int 		total_;
		Fecha 		fecha_;
		Tarjeta* 	const tarjeta_;

};

#endif