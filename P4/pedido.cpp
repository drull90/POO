#include <iostream>
#include <iomanip>

#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

size_t Pedido::total_ = 0;

Pedido::Pedido(Usuario_Pedido& usPedido, Pedido_Articulo& peArticulo, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha) 
: nPedido_{total_ + 1}, importe_{0.},fecha_{fecha}, tarjeta_{&tarjeta} {

	if(tarjeta.titular() != &usuario)   throw Pedido::Impostor(&usuario);
	if(tarjeta.caducidad() < fecha)     throw Tarjeta::Caducada(tarjeta.caducidad());
	if(tarjeta.activa() == false )		throw Tarjeta::Desactivada();

	auto compra = usuario.compra();

	for(auto i : compra) {
		if(ArticuloAlmacenable* articuloAlmacenable = dynamic_cast<ArticuloAlmacenable*>(i.first)) {
			if(i.second > articuloAlmacenable->stock()) {
				usuario.compra(*articuloAlmacenable, 0);
				throw SinStock(articuloAlmacenable);
			}
			articuloAlmacenable->stock() -= i.second;
			peArticulo.pedir(*this, *articuloAlmacenable, articuloAlmacenable->precio(), i.second);
			importe_ += articuloAlmacenable->precio() * i.second;
		}
		else {
			LibroDigital* libroDigital = dynamic_cast<LibroDigital*>(i.first);

			if(libroDigital->f_expir() < fecha) {
				usuario.compra(*libroDigital, 0);
			}
			else{
				peArticulo.pedir(*this, *libroDigital, libroDigital->precio(), i.second);
				importe_ += libroDigital->precio() * i.second;
			}
				
		}
	}

	// Puede quedarse a 0 si no hay stock
	if(usuario.compra().empty()) throw Pedido::Vacio(&usuario);

	usPedido.asocia(*this, usuario);
	
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