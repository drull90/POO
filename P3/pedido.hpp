#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>

#include "tarjeta.hpp"
#include "fecha.hpp"

class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

class Pedido {

	public:
		Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, const Fecha());

		class Vacio{
			public:
				Vacio(Usuario* usuario) : usuario_(usuario){}
				const Usuario& usuario() const { return *usuario_; }
			private:
				Usuario* usuario_;
		};
		
		class Impostor{
			public:
				Impostor(Usuario* usuario) : usuario_(usuario){}
				const Usuario& usuario() const { return *usuario_; }
			private:
				Usuario* usuario_;
		};

		class SinStock{
			public:
				SinStock(Articulo* articulo): articulo_(articulo){}
				const Articulo& articulo() const { return *articulo_; }
			private:
				Articulo * articulo_;
		};

		inline int 				numero() 			const 	{ return nPedido; 	 }
		inline Tarjeta const* 	tarjeta() 			const 	{ return tarjeta_; 	 }
		inline Fecha 			fecha() 			const 	{ return fecha_;	 }
		inline double 			total()				const 	{ return importe_;	 }
		inline int 				n_total_pedidos() 			{ return total_;	 }

	private:
		int 		nPedido_;
		int 		importe_;
		int 		total_;
		Fecha 		fecha_;
		Tarjeta 	const* tarjeta_;

};

ostream& operator << (ostream& o, const Pedido& pedido);

#endif