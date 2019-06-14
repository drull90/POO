#include <cstring>
#include <iostream>
#include <unordered_set>
#include <map>
#include <utility>
#include <iomanip>
#include <random>

#include "usuario.hpp"

Clave::Clave(const char* clave) {
	if(strlen(clave) < 5) throw Incorrecta(CORTA);

	std::uniform_int_distribution<int> 	distribution(1000000,9999999);
	std::random_device					random_;
	std::default_random_engine 			generator(random_());

	// hasheamos la clave suministrada
	// hash(clave)
	clave_ = cifrar(clave);

	// Generamos un sal aleatorio
	int sal = distribution(generator);

	// Concatenamos el sal al hash de forma poco predecible
	// En este caso tenemos un numero de 7 cifras
	// lo haremos de la siguiente forma
	// 3 al principio de la Cadena y 4 al final

	// Pasamos el sal a una cadena
	char salS[7];
	sprintf(salS, "%d", sal);
	Cadena salCad{salS};

	// Creamos una Cadena auxiliar que nos guarde el valor
	// ClaveAux = hash + sal => SSS_hash_SSSS
	// S caracteres del sal
	Cadena claveAux;

	claveAux += salCad.substr(0, 3);
	claveAux += clave_;
	claveAux += salCad.substr(3, 4);

	// Volvemos a hashear el resultado
	// hash(clave + sal) => hashRobusto

	claveAux = cifrar(claveAux);
	
	// Agregamos el sal de nuevo al hashRobusto
	// Nos queda SSS_hasRobusto_SSSS
	// S es cada caracter del sal
	Cadena aux;
	aux = salCad.substr(0, 3);
	aux += claveAux;
	aux += salCad.substr(3, 4);

	clave_ = aux;

}

Clave::Incorrecta::Incorrecta(Razon r) : razon_{r} {}

bool Clave::verifica(const Cadena& pass) const noexcept {

	// Copiamos la cadena a cifrar en una cadena auxiliar
	Cadena passAux{pass};

	// hacemos hash sobre la clave suministrada
	passAux = cifrar(passAux);

	// Obtenemos el sal de la clave del usuario
	// SSS_hashRobusto_SSSS
	Cadena sal;
	
	sal += clave_.substr(0, 3);
	sal += clave_.substr(clave_.length() - 4, 4);

	// Agregamos sal al sal de la clave introducidad
	// SSS_hash_SSSS

	Cadena aux{};
	aux += sal.substr(0, 3);
	aux += passAux;
	aux += sal.substr(3, 4);

	// aux = SSS_hash_SSSS
	// hacemos nuevamente hash
	// passAux = hashRobusto
	passAux = cifrar(aux);

	// Ponemos el sal al hash robusto y comparamos
	aux = "";
	aux += sal.substr(0, 3);
	aux += passAux;
	aux += sal.substr(3, 4);

	if( aux == clave_)
		return true;

	return false;
}

const Cadena Clave::cifrar(const Cadena& pass) const {

	unsigned char digest[SHA256::DIGEST_SIZE];
	memset(digest,0,SHA256::DIGEST_SIZE);
 
	SHA256 ctx = SHA256();
	ctx.init();
	ctx.update( (unsigned char*) pass.c_str(), pass.length());
	ctx.final(digest);
 
	char buf[2*SHA256::DIGEST_SIZE+1];
	buf[2*SHA256::DIGEST_SIZE] = 0;
	for (int i = 0; i < SHA256::DIGEST_SIZE; i++)
		sprintf(buf+i*2, "%02x", digest[i]);

	return buf;
}

const unsigned int Clave::SHA256::sha256_k[64] = //UL = uint32
			{0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
			 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
			 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
			 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
			 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
			 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
			 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
			 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
			 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
			 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
			 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
			 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
			 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
			 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
			 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
			 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
 
void Clave::SHA256::transform(const unsigned char *message, unsigned int block_nb) {
	uint32 w[64];
	uint32 wv[8];
	uint32 t1, t2;
	const unsigned char *sub_block;
	int i;
	int j;
	for (i = 0; i < (int) block_nb; i++) {
		sub_block = message + (i << 6);
		for (j = 0; j < 16; j++) 
			SHA2_PACK32(&sub_block[j << 2], &w[j]);
		for (j = 16; j < 64; j++) 
			w[j] =  SHA256_F4(w[j -  2]) + w[j -  7] + SHA256_F3(w[j - 15]) + w[j - 16];
		for (j = 0; j < 8; j++)
			wv[j] = m_h[j];
		for (j = 0; j < 64; j++) {
			t1 = wv[7] + SHA256_F2(wv[4]) + SHA2_CH(wv[4], wv[5], wv[6])
				+ sha256_k[j] + w[j];
			t2 = SHA256_F1(wv[0]) + SHA2_MAJ(wv[0], wv[1], wv[2]);
			wv[7] = wv[6];
			wv[6] = wv[5];
			wv[5] = wv[4];
			wv[4] = wv[3] + t1;
			wv[3] = wv[2];
			wv[2] = wv[1];
			wv[1] = wv[0];
			wv[0] = t1 + t2;
		}
		for (j = 0; j < 8; j++)
			m_h[j] += wv[j];
	}
}
 
void Clave::SHA256::init() {
	m_h[0] = 0x6a09e667;
	m_h[1] = 0xbb67ae85;
	m_h[2] = 0x3c6ef372;
	m_h[3] = 0xa54ff53a;
	m_h[4] = 0x510e527f;
	m_h[5] = 0x9b05688c;
	m_h[6] = 0x1f83d9ab;
	m_h[7] = 0x5be0cd19;
	m_len = 0;
	m_tot_len = 0;
}
 
void Clave::SHA256::update(const unsigned char *message, unsigned int len) {
	unsigned int block_nb;
	unsigned int new_len, rem_len, tmp_len;
	const unsigned char *shifted_message;
	tmp_len = SHA224_256_BLOCK_SIZE - m_len;
	rem_len = len < tmp_len ? len : tmp_len;
	memcpy(&m_block[m_len], message, rem_len);
	if (m_len + len < SHA224_256_BLOCK_SIZE) {
		m_len += len;
		return;
	}
	new_len = len - rem_len;
	block_nb = new_len / SHA224_256_BLOCK_SIZE;
	shifted_message = message + rem_len;
	transform(m_block, 1);
	transform(shifted_message, block_nb);
	rem_len = new_len % SHA224_256_BLOCK_SIZE;
	memcpy(m_block, &shifted_message[block_nb << 6], rem_len);
	m_len = rem_len;
	m_tot_len += (block_nb + 1) << 6;
}
 
void Clave::SHA256::final(unsigned char *digest) {
	unsigned int block_nb;
	unsigned int pm_len;
	unsigned int len_b;
	int i;
	block_nb = (1 + ((SHA224_256_BLOCK_SIZE - 9)
					 < (m_len % SHA224_256_BLOCK_SIZE)));
	len_b = (m_tot_len + m_len) << 3;
	pm_len = block_nb << 6;
	memset(m_block + m_len, 0, pm_len - m_len);
	m_block[m_len] = 0x80;
	SHA2_UNPACK32(len_b, m_block + pm_len - 4);
	transform(m_block, block_nb);
	for (i = 0 ; i < 8; i++) {
		SHA2_UNPACK32(m_h[i], &digest[i << 2]);
	}
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