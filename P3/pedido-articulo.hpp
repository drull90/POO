#ifndef PEDIDO_ARTICULO
#define PEDIDO_ARTICULO

#include <map>

#include "pedido.hpp"

class LineaPedido {
    public:
      explicit 	LineaPedido	(double precio, unsigned c = 1u): precio_(precio), cantidad_(c){}

      double 	precio_venta() 	const {return precio_;}
      unsigned 	cantidad() 		const {return cantidad_;}

    private:
      double 	precioVenta_;
      unsigned 	cantidadVendida_;
};

ostream& operator << (ostream&, const LineaPedido&);

class OrdenaArticulos {

};

class OrdenaPedidos {

};

class Pedido_Articulo {

	public:
		
		typedef std::map<Articulo*, LineaPedido, 	OrdenaArticulos> 	ItemsPedido;
		typedef std::map<Pedido*, 	ItemsPedido, 	OrdenaPedidos> 		PedidoArticulo;

		typedef std::map<Pedido*, 	LineaPedido, 	OrdenaPedidos>		Pedidos;
		typedef std::map<Articulo*, Pedidos, 	 	OrdenaArticulos>	ArticuloPedido;

		void pedir(const Pedido&, 	const Articulo&, double, int = 1);
		void pedir(const Articulo&, const Pedido&, 	 double, int = 1);

		const ItemsPedido& 	detalle(const Pedido&);
		const Pedidos&		ventas (const Articulo&);

		ostream& mostrarDetallePedidos (ostream&) const;
		ostream& mostrarVentasArticulos(ostream&) const;

	private:
		ItemsPedido 		ItemsPedido_;
		PedidoArticulo 		pedidoArticulo_;

		Pedidos 			pedidos_;
		ArticuloPedido 		articuloPedido_;

};

ostream& operator << (ostream&, const Pedido_Articulo::ItemsPedido&);
ostream& operator << (ostream&, const Pedido_Articulo::Pedidos&);

#endif