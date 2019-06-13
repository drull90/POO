#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>

#include "usuario.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

class Pedido {

	public:
		Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, const Fecha& = Fecha());

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
				Articulo* articulo_;
		};

		inline int 				numero() 			const 	{ return nPedido_; 	 }
		inline Tarjeta const* 	tarjeta() 			const 	{ return tarjeta_; 	 }
		inline const Fecha& 	fecha() 			const 	{ return fecha_;	 }
		inline double 			total()				const 	{ return importe_;	 }
		inline static int 		n_total_pedidos() 			{ return total_;	 }

	private:
		int 		nPedido_;
		double 		importe_;
		static int 	total_;
		Fecha 		fecha_;
		Tarjeta 	const* tarjeta_;

};

std::ostream& operator << (std::ostream& o, const Pedido& pedido);

#endif