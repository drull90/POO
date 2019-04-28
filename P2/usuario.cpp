
#include "usuario.hpp"


Usuario::Usuario(const Cadena& iden, const Cadena& nomb, const Cadena& apell, const Cadena& dirr, const Clave& clave) : iden_{iden}, nomb_{nomb}, apell_{apell}, dirr_{dirr}, clave_{clave} {

    //Usuario::usuarios_.insert(iden);

}

Usuario::Id_duplicado::Id_duplicado(const Cadena& cad) : iden_{cad} {}

int main() {

    

    return 0;
}