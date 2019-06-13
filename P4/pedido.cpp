#include <iostream>
#include <iomanip>

#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

int Pedido::total_ = 0;

Pedido::Pedido(Usuario_Pedido& usPedido, Pedido_Articulo& peArticulo, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha) 
: fecha_{fecha}, tarjeta_{&tarjeta} {

	if(usuario.compra().empty())        throw Pedido::Vacio(&usuario);
	if(tarjeta.titular() != &usuario)   throw Pedido::Impostor(&usuario);
	if(tarjeta.caducidad() < fecha)     throw Tarjeta::Caducada(tarjeta.caducidad());
	if(tarjeta.activa() == false )		throw Tarjeta::Desactivada();

	for(auto i = usuario.compra().begin(); i != usuario.compra().end(); ++i){
		if( i->second > i->first->stock()){
			const_cast<Usuario::Articulos&>(usuario.compra()).clear();
			throw Pedido::SinStock(i->first);
		}
	}

	usPedido.asocia(*this, usuario);
	importe_ = 0;

	for( auto i = usuario.compra().begin(); i != usuario.compra().end(); ++i){
		importe_ += i->second * i->first->precio();
		peArticulo.pedir(*i->first, *this, i->first->precio(), i->second);
		i->first->stock() -= i->second;
	}

	nPedido_ = ++total_;
	const_cast<Usuario::Articulos&>(usuario.compra()).clear();

}

std::ostream& operator << (std::ostream& o, const Pedido& pedido) {

	o 	<< "Núm. pedido: " 	<< pedido.numero() 				<< std::endl
    	<< "Fecha:       " 	<< pedido.fecha() 				<< std::endl
    	<< "Pagado con:  " 	<< pedido.tarjeta()->tipo()
    	<< " n.º: " 		<< pedido.tarjeta()->numero() 	<< std::endl
    	<< "Importe:     "  
		<< std::fixed		<< std::setprecision(2) 							
		<< pedido.total()	<< " €" 						<< std::endl;

  return o;

}