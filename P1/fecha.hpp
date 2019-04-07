#ifndef FECHA_HPP
#define FECHA_HPP

#include <iostream>

/**
 * Clase Fecha
 */
class Fecha {
	public:
		// Constructores
		Fecha(const char*);
		explicit Fecha(int dia = 0, int mes = 0, int anno = 0);

		// Destructor
		~Fecha();
		
		// Sobrecargas de operadores
		// Operadores internos
		Fecha&  operator ++ ();
		Fecha&  operator -- ();
		Fecha   operator ++ (int);
		Fecha   operator -- (int);
		Fecha&  operator += (int);
		Fecha&  operator -= (int);
		Fecha   operator +  (int) const;
		Fecha   operator -  (int) const;
		
		// Operadores externos
		friend std::ostream& operator << (std::ostream&, const Fecha&) noexcept;
		friend std::istream& operator >> (std::istream&, const Fecha&) noexcept;


		// Metodos
		inline int dia() const noexcept     { return dia_; };
		inline int mes() const noexcept     { return mes_; };
		inline int anno() const noexcept    { return anno_;};
		const char* cadena() noexcept;

		//Clases
		class Invalida{
			public:
				Invalida(const char*) noexcept;
				const char* por_que() const noexcept;
			private:
				const char* error_;
		};

		//Atributos
		static const int AnnoMinimo = 1902, AnnoMaximo = 2037;
		
	private:
		int dia_, mes_, anno_;
		char* fecha;
		void fechaValida();
		bool fechaEnRango() const noexcept;
};

//Operadores externos
bool operator <  (const Fecha&, const Fecha&) noexcept;
bool operator == (const Fecha&, const Fecha&) noexcept;
bool operator >  (const Fecha&, const Fecha&) noexcept;
bool operator <= (const Fecha&, const Fecha&) noexcept;
bool operator >= (const Fecha&, const Fecha&) noexcept;
bool operator != (const Fecha&, const Fecha&) noexcept;

#endif