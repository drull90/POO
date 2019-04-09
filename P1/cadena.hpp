#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>

class Cadena{

	public:
		// Constructores
		Cadena(const Cadena&) 									noexcept;
		Cadena(Cadena&&)										noexcept;
		Cadena(const char*) 									noexcept;
		explicit Cadena(unsigned long int  = 0, char = ' ') 	noexcept;
		
		// Destructor
		~Cadena();

		// Sobrecarga de operadores
		// Operadores internos
		Cadena& 		operator 	= 	(const Cadena&) 				noexcept;
		Cadena& 		operator 	= 	(const char*) 					noexcept;
		Cadena&			operator 	=	(Cadena&&)						noexcept;
		Cadena&			operator 	+= 	(const Cadena&) 				noexcept;
		const char		operator	[]	(unsigned long int n) const 	noexcept;
		char&			operator	[]	(unsigned long int n) 			noexcept;

		// Operadores externos
		friend std::ostream& operator << (std::ostream&, const Cadena&) noexcept;
		friend std::istream& operator >> (std::istream&, Cadena&);

		// Metodos
		inline unsigned long int length() noexcept;
		char& 			at(unsigned long int);
		const char		at(unsigned long int) const;
		Cadena 			substr(unsigned long int, unsigned long int) const;
		const char* 	c_str() const noexcept;

		// Iteradores
		// No-const
		typedef char* iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;

		// Const
		typedef const char* const_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		// Funciones de Iteradores
		// No-const
		iterator 				begin();
		iterator 				end();
		reverse_iterator 		rbegin();
		reverse_iterator 		rend();

		// Const
		const_iterator 			cbegin() 	const;
		const_iterator 			cend() 		const;
		const_reverse_iterator 	crbegin() 	const;
		const_reverse_iterator 	crend() 	const;
		
	private:
		// Atributos
		char* s_;
		unsigned long int tam_;

};

// Operadores externos
// Concatenacion
Cadena 	operator +	(const Cadena&, const Cadena&) noexcept;

//Comparacion
bool operator >	 (const Cadena&, const Cadena&) noexcept;
bool operator <	 (const Cadena&, const Cadena&) noexcept;
bool operator <= (const Cadena&, const Cadena&) noexcept;
bool operator >= (const Cadena&, const Cadena&) noexcept;
bool operator == (const Cadena&, const Cadena&) noexcept;
bool operator != (const Cadena&, const Cadena&) noexcept;

#endif