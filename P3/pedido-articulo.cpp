#include <iostream>
#include <iomanip>

#include "pedido-articulo.hpp"

std::ostream& operator <<(std::ostream& o, const LineaPedido& lineaPedido) {

  o << std::fixed << std::setprecision(2) 
    << lineaPedido.precio_venta()
	<< " €\t"<< lineaPedido.cantidad();

	return o;
}

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, int cantidad ) {
  pedidoArticulo_[&p].insert(std::make_pair(&a, LineaPedido(precio, cantidad)));
  articuloPedido_[&a].insert(std::make_pair(&p, LineaPedido(precio, cantidad)));
}

void Pedido_Articulo::pedir(Articulo& articulo, Pedido& pedido, double precio, int cantidad ) {
  pedir(pedido, articulo, precio, cantidad);
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& pedido) {
  return pedidoArticulo_.find(&pedido)->second;
}

const Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo& articulo) {
    return articuloPedido_.find(&articulo)->second;
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& o) const {

    double total = 0;

    for(auto i = pedidoArticulo_.begin() ; i != pedidoArticulo_.end() ; ++i) {
        o   << "Pedido núm. "   << i->first->numero();
        o   << "\tCliente: "    << i->first->tarjeta()->titular()->nombre() 
            << " \n";
        o   << "Fecha: "        << i->first->fecha() 
            << i->second;

        total += i->first->total();
    }

    o   << "TOTAL VENTAS: " << std::setprecision(2) 
        << total            << " €" << std::endl;
    
    return o;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& o) const {

    for(auto i = articuloPedido_.begin(); i != articuloPedido_.end(); ++i) {
        o   << "Ventas de "     << "["                  << i->first->referencia() << "]";
        o   << "\""             << i->first->titulo()   << "\" \n" 
            << i->second        << std::endl;
    }

    return o;
}

std::ostream& operator <<(std::ostream& o, const Pedido_Articulo::ItemsPedido& itemsPedido) {

    double total = 0;

    o << " PVP    Cantidad    Articulo "                          << std::endl;
    o << "===================================================="   << std::endl;

    for(auto i = itemsPedido.begin(); i != itemsPedido.end(); ++i) {
        o << " "                    << i->second.precio_venta()     << "€ ";
        o << i->second.cantidad()   << "    ";
        o << "["                    << i->first->referencia()       << "] ";
        o << "\""                   << i->first->titulo() << "\" "  << std::endl;

        total += i->second.precio_venta() * i->second.cantidad();
    }
    o << "===================================================" << std::endl;
    o << std::setprecision(2) << total << " €" << std::endl;

  return o;
}

std::ostream& operator <<(std::ostream& o, const Pedido_Articulo::Pedidos& pedidos) {

    double precio = 0;
    unsigned total = 0;

    o << "====================================================" << std::endl;
    o << " PVP \t Cant. \t Fecha venta \n";
    o << "====================================================" << std::endl;

    for(auto i : pedidos){
        o << " "                    << i.second.precio_venta() << "€    ";
        o << i.second.cantidad()    << "    ";
        o << i.first->fecha()       << std::endl;

        precio += i.second.precio_venta() * i.second.cantidad();
        total += i.second.cantidad();
    }

    o << "====================================================" << std::endl;
    o << std::setprecision(2) << precio << " €    " << total      << std::endl ;

    return o;
}