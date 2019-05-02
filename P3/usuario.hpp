#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <unordered_set>
#include <map>
#include <unordered_map>
#include <iostream>

#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA256_F1(x) (SHA2_ROTR(x,  2) ^ SHA2_ROTR(x, 13) ^ SHA2_ROTR(x, 22))
#define SHA256_F2(x) (SHA2_ROTR(x,  6) ^ SHA2_ROTR(x, 11) ^ SHA2_ROTR(x, 25))
#define SHA256_F3(x) (SHA2_ROTR(x,  7) ^ SHA2_ROTR(x, 18) ^ SHA2_SHFR(x,  3))
#define SHA256_F4(x) (SHA2_ROTR(x, 17) ^ SHA2_ROTR(x, 19) ^ SHA2_SHFR(x, 10))

#define SHA2_UNPACK32(x, str) {               \
	*((str) + 3) = (uint8) ((x)      );       \
	*((str) + 2) = (uint8) ((x) >>  8);       \
	*((str) + 1) = (uint8) ((x) >> 16);       \
	*((str) + 0) = (uint8) ((x) >> 24);       \
}

#define SHA2_PACK32(str, x) {                 \
	*(x) =   ((uint32) *((str) + 3)      )    \
		   | ((uint32) *((str) + 2) <<  8)    \
		   | ((uint32) *((str) + 1) << 16)    \
		   | ((uint32) *((str) + 0) << 24);   \
}

class Numero;
class Tarjeta;

class Clave {
	public:
		enum Razon{CORTA, ERROR_CRYPT};
		// Constructor
		Clave(const char*);

		class Incorrecta {
			public:
				Incorrecta(const Razon);
				inline Razon razon() const noexcept { return razon_; }
			private:
				Razon razon_;
		};

		class SHA256 {
			protected:
				typedef unsigned char 		uint8;
				typedef unsigned int 		uint32;
				typedef unsigned long long 	uint64;
				const static 				uint32 sha256_k[];
				static const unsigned int 	SHA224_256_BLOCK_SIZE = 64;
				unsigned int 				m_tot_len;
				unsigned int				m_len;
				unsigned char 				m_block[2*SHA224_256_BLOCK_SIZE];
				uint32 						m_h[8];
				void transform(const unsigned char *message, unsigned int block_nb);
			public:
				void init();
				void update	(const unsigned char *message, unsigned int len);
				void final	(unsigned char *digest);
				static const unsigned int DIGEST_SIZE = 32;
		};
		// Metodos
		inline const Cadena& clave() const 	noexcept { return clave_; }
		bool verifica(const Cadena&) const	noexcept;
	private:
		const Cadena cifrar(const Cadena&) const;
		Cadena clave_;
};

class Usuario {

	public:
		// Constructor
		explicit Usuario(const Cadena&, const Cadena&, const Cadena&, const Cadena&, const Clave&);

		// Eliminar la copia de usuarios
		Usuario(const Usuario&) 			= delete;
		Usuario(Usuario&) 					= delete;
		void operator = (const Usuario&) 	= delete;
		void operator = (Usuario&) 			= delete;

		// Destructor
		~Usuario();

		friend std::ostream& operator << (std::ostream&, const Usuario&);

		// Maps
		typedef std::map			<Numero, 	Tarjeta*> 		Tarjetas;
		typedef std::unordered_map	<Articulo*, unsigned int> 	Articulos;
		typedef std::unordered_set	<Cadena> 					Usuarios;

		// Clase de error
		class Id_duplicado {
			public:
				Id_duplicado(const Cadena&);
				inline const Cadena& idd() const noexcept { return iden_; }
			private:
				Cadena iden_;
		};

		// Metodos
		inline const 	Cadena& 	id()		const noexcept	{ return iden_; 	}
		inline const 	Cadena& 	nombre()	const noexcept	{ return nomb_;		}
		inline const	Cadena& 	apellidos()	const noexcept	{ return apell_;	}
		inline const 	Cadena& 	direccion()	const noexcept 	{ return dirr_;		}
		const 			Tarjetas& 	tarjetas()	const noexcept 	{ return tarjetas_;	}

		void 	es_titular_de		(const Tarjeta&);
		void 	no_es_titular_de	(const Tarjeta&);

		inline  const 	Articulos& compra	() const noexcept { return articulos_;	 		}
		inline 	int 	n_articulos			() const noexcept { return articulos_.size(); 	}

		void 	compra	(const Articulo&, size_t = 1);
		
	private:
		static 		Usuarios users;

		Cadena 		iden_;
		Cadena 		nomb_;
		Cadena 		apell_;
		Cadena 		dirr_;
		Clave  		clave_;
		
		Tarjetas 	tarjetas_;
		Articulos 	articulos_;

};

void mostrar_carro(std::ostream&, const Usuario&);

#endif