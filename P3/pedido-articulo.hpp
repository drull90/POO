#ifndef PEDIDO_ARTICULO
#define PEDIDO_ARTICULO

#include <algorithm>
#include <map>

#include "pedido.hpp"

class Pedido;
class Articulo;

class LineaPedido {
	public:
		explicit 	LineaPedido	(double precio, unsigned cantidad = 1u): precioVenta_(precio), cantidadVendida_(cantidad) {}

		double 		precio_venta() 	const { return precioVenta_;}
		unsigned 	cantidad() 		const { return cantidadVendida_;}

	private:
		double 		precioVenta_;
		unsigned 	cantidadVendida_;
};

std::ostream& operator << (std::ostream&, const LineaPedido&);

class OrdenaArticulos : public std::binary_function<Articulo*,Articulo*,bool> {
	public:
  		bool operator()(const Articulo* a1,const Articulo* a2) const { return (a1->referencia() < a2->referencia()); }
};

class OrdenaPedidos : public std::binary_function<Pedido*,Pedido*,bool> {
	public:
		bool operator()(const Pedido* p1,const Pedido* p2) const { return p1->numero() < p2->numero(); }
};

class Pedido_Articulo {

	public:
		
		typedef std::map<Articulo*, LineaPedido, 	OrdenaArticulos> 	ItemsPedido;
		typedef std::map<Pedido*, 	ItemsPedido, 	OrdenaPedidos> 		PedidoArticulo;

		typedef std::map<Pedido*, 	LineaPedido, 	OrdenaPedidos>		Pedidos;
		typedef std::map<Articulo*, Pedidos, 	 	OrdenaArticulos>	ArticuloPedido;

		void pedir(Pedido&, 	Articulo&, 	double, int = 1);
		void pedir(Articulo&, 	Pedido&, 	double, int = 1);

		const ItemsPedido& 	detalle(Pedido&);
		const Pedidos&		ventas (Articulo&);

		std::ostream& mostrarDetallePedidos (std::ostream&) const;
		std::ostream& mostrarVentasArticulos(std::ostream&) const;

	private:
		ItemsPedido 		ItemsPedido_;
		PedidoArticulo 		pedidoArticulo_;

		Pedidos 			pedidos_;
		ArticuloPedido 		articuloPedido_;

};

std::ostream& operator << (std::ostream&, const Pedido_Articulo::ItemsPedido&);
std::ostream& operator << (std::ostream&, const Pedido_Articulo::Pedidos&);

#endif