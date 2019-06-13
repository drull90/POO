#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <iostream>
#include <set>

#include "cadena.hpp"
#include "fecha.hpp"

class Autor {

	public:
		
		Autor(const Cadena&, const Cadena&, const Cadena&);

		inline Cadena nombre() 		const noexcept { return nombre_; 	};
		inline Cadena apellidos() 	const noexcept { return apellidos_; };
		inline Cadena direccion() 	const noexcept { return direccion_; };

	private:
		Cadena nombre_;
		Cadena apellidos_;
		Cadena direccion_;
};

class Articulo {

	public:

		typedef std::set<Autor*> Autores;

		// Constructor
		explicit Articulo(const Autores&, const Cadena&, const Cadena&, const Fecha&, double);

		virtual ~Articulo(){}

		class Autores_vacios{};

		// Metodos
		inline const 	Cadena&	referencia() const 	noexcept { return ref_; 	}
		inline const 	Cadena&	titulo()	 const 	noexcept { return titulo_;	}
		inline const 	Fecha&	f_publi()	 const 	noexcept { return fecha_; 	}
		inline double 			precio()	 const 	noexcept { return precio_; 	}
		inline size_t 			stock()		 const 	noexcept { return stock_; 	}
		inline size_t& 			stock()			   	noexcept { return stock_; 	}
		inline double& 			precio() 			noexcept { return precio_; 	}

		virtual void impresion_especifica(std::ostream& os) const = 0;

	private:
		Cadena 	ref_;
		Cadena 	titulo_;
		Fecha	fecha_;
		double	precio_;
		size_t	stock_;

};

class ArticuloAlmacenable: public Articulo {

	public:
		ArticuloAlmacenable(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, unsigned = 0);

		inline unsigned stock() const { return stock_; };
		unsigned stock();

	protected:
		unsigned stock_;
};

class Libro: public ArticuloAlmacenable {

	public:
		Libro(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, unsigned, unsigned = 0);

		inline unsigned n_pag() const { return n_pag_; };

		void impresion_especifica(std::ostream& os) const;

	private:
		const unsigned n_pag_;
};

class Cederron: public ArticuloAlmacenable {

	public:
		//Constructor
		Cederron(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, unsigned, unsigned = 0);

		inline unsigned tam() const { return tam_; };

		void impresion_especifica(std::ostream& os) const;

	private:
		unsigned tam_;
};

class LibroDigital: public Articulo {

	public:
		LibroDigital(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, const Fecha&);

		//Observador
		inline const Fecha& f_expir() const { return f_expir_; };

		void impresion_especifica(std::ostream& os) const;

	private:
		const Fecha f_expir_;
};

std::ostream& operator << (std::ostream& o, const Articulo&);

#endif