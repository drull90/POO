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

        void asocia(const Usuario&, const Pedido&);
        void asocia(const Pedido&,  const Usuario&);

        const Pedidos& pedidos(const Usuario&);
        const Usuario* cliente(const Pedido&);

    private:

};

#endif