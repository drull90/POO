#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <iostream>
#include <set>

#include "cadena.hpp"
#include "fecha.hpp"

class Autor {
	public:
		Autor(const Cadena&, const Cadena&, const Cadena&);

		inline Cadena nombre() 		const noexcept { return nombre_; 	}
		inline Cadena apellidos() 	const noexcept { return apellido_;  }
		inline Cadena direccion() 	const noexcept { return direccion_; }

	private:
		Cadena nombre_;
		Cadena apellido_;
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
		inline const 	Cadena&		referencia() const 	noexcept { return ref_; 	}
		inline const 	Cadena&		titulo()	 const 	noexcept { return titulo_;	}
		inline const 	Fecha&		f_publi()	 const 	noexcept { return fecha_; 	}
		inline double 				precio()	 const 	noexcept { return precio_; 	}
		inline double& 				precio() 			noexcept { return precio_; 	}
		inline const 	Autores&	autores() 	 const 			 { return autores_; }

		virtual void impresion_especifica(std::ostream&) const = 0;

	private:
		Cadena 	ref_;
		Cadena 	titulo_;
		Fecha	fecha_;
		double	precio_;
		const 	Autores autores_;

};

class ArticuloAlmacenable: public Articulo {
	public:
		ArticuloAlmacenable(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, size_t = 0);

		inline size_t& 	stock() 		{ return stock_; }
		inline size_t 	stock() const 	{ return stock_; }

	protected:
		size_t stock_;
};

class Libro: public ArticuloAlmacenable {

	public:
		Libro(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, unsigned, unsigned = 0);

		inline unsigned n_pag() const { return pag_; }

		void impresion_especifica(std::ostream&) const;

	private:
		const unsigned pag_;
};

class Cederron: public ArticuloAlmacenable {

	public:
		//Constructor
		Cederron(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, unsigned, unsigned = 0);

		inline unsigned tam() const { return tam_; }

		void impresion_especifica(std::ostream&) const;

	private:
		unsigned tam_;
};

class LibroDigital: public Articulo {

	public:
		LibroDigital(const Autores&, const Cadena&, const Cadena&, const Fecha&, double, const Fecha&);

		//Observador
		inline const Fecha& f_expir() const { return fechaExp_; }

		void impresion_especifica(std::ostream& o) const;

	private:
		const Fecha fechaExp_;
};

std::ostream& operator << (std::ostream&, const Articulo&);

#endif