#include <cstring>

#include "clave.hpp"
#include "cadena.hpp"
#include "sha256.hpp"

Clave::Clave(const Cadena& clave) {

	if(clave.length() < 5)
		throw Incorrecta(CORTA);

	clave_ = cifrar(clave);

}

Clave::Incorrecta::Incorrecta(Razon r) : razon_{r} {}

bool Clave::verifica(const Cadena& pass) noexcept {

	if( cifrar(pass) == clave_ )
		return true;

	return false;
}

const Cadena Clave::cifrar(const Cadena& pass) {

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