#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <map>
#include <set>

#include "usuario.hpp"
#include "pedido.hpp"

class Pedido;
class Usuario;

class Usuario_Pedido {

	public:
		typedef std::set<Pedido*>  Pedidos;
		typedef std::map<Usuario*, Pedidos>     UsuarioPedido;
		typedef std::map<Pedido*,  Usuario*>    PedidoUsuario;

		void asocia(Usuario&, Pedido&);
		void asocia(Pedido&,  Usuario&);

		const Pedidos& pedidos(Usuario&);
		const Usuario* cliente(Pedido&);

	private:
		UsuarioPedido usuarioPedido_;
		PedidoUsuario pedidoUsuario_;
};

#endif