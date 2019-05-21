#include "usuario-pedido.hpp"
#include "pedido.hpp"

void Usuario_Pedido::asocia(Usuario& usuario, Pedido& pedido) {
	usuarioPedido_[&usuario].insert(&pedido);
	pedidoUsuario_[&pedido] = &usuario;
}

void Usuario_Pedido::asocia(Pedido& pedido, Usuario& usuario)               { asocia(usuario, pedido); }

const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& usuario)    { return usuarioPedido_.find(&usuario)->second; }

const Usuario* Usuario_Pedido::cliente(Pedido& pedido) 						{ return pedidoUsuario_.find(&pedido)->second; }