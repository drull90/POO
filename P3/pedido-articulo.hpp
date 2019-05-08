#ifndef PEDIDO_ARTICULO
#define PEDIDO_ARTICULO

#include <map>

#include "pedido.hpp"

class OrdenaArticulos {

};

class OrdenaPedidos {

};

class LineaPedido {

	public:
		
		typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> 	ItemsPedido;
		typedef std::map<Pedido*, 	ItemsPedido, OrdenaPedidos> 	PedidoArticulo;

		typedef std::map<Pedido*, 	LineaPedido, OrdenaPedidos>		Pedidos;
		typedef std::map<Articulo*, Pedidos, 	 OrdenaArticulos>	ArticuloPedido;

		void 	pedir(const Pedido&, 	const Articulo&, int, int = 1);
		void 	pedir(const Articulo&, 	const Pedido&, 	 int, int = 1);

		const ItemsPedido& detalle(const PedidoArticulo&);

	private:

};

#endif