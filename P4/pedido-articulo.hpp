#ifndef PEDIDO_ARTICULO
#define PEDIDO_ARTICULO

#include <algorithm>
#include <map>

#include "articulo.hpp"
#include "pedido.hpp"

class Pedido;
class Articulo;

class LineaPedido {
	public:
		inline explicit LineaPedido	(double precio, unsigned cantidad = 1): precioVenta_(precio), cantidadVendida_(cantidad) {}

		inline double 	precio_venta() 	const noexcept { return precioVenta_;		}
		inline unsigned cantidad() 		const noexcept { return cantidadVendida_;	}

	private:
		double 		precioVenta_;
		unsigned 	cantidadVendida_;
};

std::ostream& operator << (std::ostream&, const LineaPedido&);

class OrdenaArticulos : public std::binary_function<const Articulo*, const Articulo*,bool> {
	public:
  		inline bool operator()(const Articulo* articulo1, const Articulo* articulo2) const { return (articulo1->referencia() < articulo2->referencia()); }
};

class OrdenaPedidos : public std::binary_function<const Pedido*, const Pedido*,bool> {
	public:
		bool operator()(const Pedido* pedido1, const Pedido* pedido2) const;
};

class Pedido_Articulo {

	public:
		
		typedef std::map<Articulo*, LineaPedido, 	OrdenaArticulos> 	ItemsPedido;
		typedef std::map<Pedido*, 	ItemsPedido, 	OrdenaPedidos> 		PedidoArticulo;

		typedef std::map<Pedido*, 	LineaPedido, 	OrdenaPedidos>		Pedidos;
		typedef std::map<Articulo*, Pedidos, 	 	OrdenaArticulos>	ArticuloPedido;

		void pedir(Pedido&, 	Articulo&, 	double, unsigned = 1);
		void pedir(Articulo&, 	Pedido&, 	double, unsigned = 1);

		const ItemsPedido& 	detalle(Pedido&);
		const Pedidos&		ventas (Articulo&);

		std::ostream& mostrarDetallePedidos (std::ostream&) const;
		std::ostream& mostrarVentasArticulos(std::ostream&) const;

	private:
		PedidoArticulo 		pedidoArticulo_;
		ArticuloPedido 		articuloPedido_;

};

std::ostream& operator << (std::ostream&, const Pedido_Articulo::ItemsPedido&);
std::ostream& operator << (std::ostream&, const Pedido_Articulo::Pedidos&);

#endif