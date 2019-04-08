#ifndef FECHA_HPP
#define FECHA_HPP

/**
 * Clase Fecha
 */
class Fecha {
	public:
		// Constructores
		Fecha(const char*);
		explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
		
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
		operator const char* ()	const noexcept;

		// Metodos
		inline int dia() const noexcept     { return dia_; };
		inline int mes() const noexcept     { return mes_; };
		inline int anno() const noexcept    { return anno_;};

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