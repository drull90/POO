#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <iostream>
#include <functional>

class Cadena{

	public:
		// Constructores
		Cadena(const Cadena&) 					noexcept;
		Cadena(Cadena&&)						noexcept;
		Cadena(const char*) 					noexcept;
		explicit Cadena(size_t = 0, char = ' ') noexcept;
		
		// Destructor
		~Cadena();

		// Sobrecarga de operadores 
		// Operadores internos
		Cadena& 		operator 	= 	(const Cadena&) noexcept;
		Cadena& 		operator 	= 	(const char*) 	noexcept;
		Cadena&			operator 	=	(Cadena&&)		noexcept;
		Cadena&			operator 	+= 	(const Cadena&) noexcept;
		const char		operator	[]	(size_t) const 	noexcept;
		char&			operator	[]	(size_t) 		noexcept;

		// Metodos
		inline size_t 	length() const noexcept { return tam_; }
		char& 			at(size_t);
		const char		at(size_t) const;
		Cadena 			substr(size_t, size_t) const;
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
		const_iterator 			begin() 	const;
		const_iterator 			end() 		const;
		const_iterator 			cbegin() 	const;
		const_iterator 			cend() 		const;
		
		const_reverse_iterator 	rbegin() 	const;
		const_reverse_iterator 	rend() 		const;
		const_reverse_iterator 	crbegin() 	const;
		const_reverse_iterator 	crend() 	const;
		
	private:
		// Atributos
		char* s_;
		size_t tam_;

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

std::ostream& operator << (std::ostream&, const Cadena&) noexcept;
std::istream& operator >> (std::istream&, Cadena&);

// Para P2 y ss.
// Especialización de la plantilla hash<T>para definir la
// función hash a utilizar con contenedores desordenados de
// Cadena, unordered_[set|map|multiset|multimap].
namespace std {
	template <> struct hash<Cadena> {
		size_t operator()(const Cadena& cad) const { // conversión const char* ->string
			return hash<string>{}(cad.c_str());
		}
	};
}

#endif