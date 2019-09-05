#include <cstring>
#include <iostream>
#include <unordered_set>
#include <map>
#include <utility>
#include <iomanip>
#include <random>
#include <unistd.h>

#include "usuario.hpp"

Clave::Clave(const char* clave) {
	if(strlen(clave) < 5) throw Incorrecta(CORTA);

	std::uniform_int_distribution<int> 	distribution(0,63);
	std::random_device					random_;
	std::default_random_engine 			generator(random_());

	char const saltChar[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	char salt[2];
	salt[0] = saltChar[distribution(generator)];
	salt[1] = saltChar[distribution(generator)];

	char* pass = crypt(clave, salt);

	if(!pass) throw Incorrecta(Razon::ERROR_CRYPT);
	clave_ = pass;

}

Clave::Incorrecta::Incorrecta(Razon r) : razon_{r} {}

bool Clave::verifica(const Cadena& pass) const noexcept {
	return strcmp(crypt(pass.c_str(), clave_.c_str()), clave_.c_str()) == 0;
}

Usuario::Usuarios Usuario::users;

Usuario::Usuario(const Cadena& iden, const Cadena& nomb, const Cadena& apell, const Cadena& dirr, const Clave& clave) : iden_{iden}, nomb_{nomb}, 
apell_{apell}, dirr_{dirr}, clave_{clave} {

	if(users.insert(iden_).second == false) throw Usuario::Id_duplicado(iden_);

}

Usuario::~Usuario(){

	for(auto i : tarjetas_)
		i.second->anula_titular();

	users.erase(iden_);

}

Usuario::Id_duplicado::Id_duplicado(const Cadena& cad) : iden_{cad} {}

void Usuario::es_titular_de(const Tarjeta& t){

	if(this == t.titular()) tarjetas_[t.numero()] = const_cast<Tarjeta*>(&t);

}

void Usuario::no_es_titular_de(const Tarjeta& t) { tarjetas_.erase(t.numero()); }

void Usuario::compra(const Articulo& articulo, size_t unidades) {

	if(unidades > 0){
		articulos_[const_cast<Articulo*>(&articulo)] = unidades;
	}
	else
		articulos_.erase(const_cast<Articulo*>(&articulo));

}

std::ostream& operator << (std::ostream& o, const Usuario& us) {

	o << us.iden_ 		<< " [" << us.clave_.clave() << "] " << us.nomb_ << " " << us.apell_ << std::endl;
	o << us.dirr_ 		<< std::endl;
	o << "Tarjetas:" 	<< std::endl;
	
	for(auto i : us.tarjetas_)
		o << *i.second << std::endl;

	return o;
}

void mostrar_carro(std::ostream& o, const Usuario& us) {

	o << "Carrito de compra de " 	<< us.id() << " [Artículos: " 		<< us.n_articulos() << "] " << std::endl;
	o << " Cant.   Artículo" 		<< std::endl;
	o << "==========================================================="	<< std::endl;

	for(auto i : us.compra()) {
		o << "   " 			<< i.second 				<< "   ";
		o << "[" 			<< i.first->referencia() 	<< "] " 
		  << "\"" << i.first->titulo() 					<< "\", " 
		  << i.first->f_publi().anno() 					<< ". " 
		  << std::fixed 	<< std::setprecision(2) 	<< i.first->precio() 
		  << " €" 			<< std::endl;
	}

	o << std::endl;
	
}