#ifndef CADENA_HPP_
#define CADENA_HPP_

#include <cstddef>

class Cadena{

	public:
		// Constructores
		Cadena(const Cadena&) 									noexcept;
		Cadena(const char*) 									noexcept;
		explicit Cadena(size_t = 0, char = ' ') 				noexcept;
		
		// Destructor
		~Cadena();

		// Sobrecarga de operadores
		// Operadores internos
		Cadena& 		operator 	= 	(Cadena&) 						noexcept;
		Cadena& 		operator 	= 	(const char*) 					noexcept;
		const char		operator	[]	(size_t) 		const 			noexcept;
		char&			operator	[]	(size_t) 						noexcept;
		Cadena&			operator 	+= 	(const Cadena&) 				noexcept;
		
		// Operadores de conversion
		operator const char*() const;

		// Metodos
		inline size_t 	length() const noexcept { return tam_; }
		char& 			at(size_t);
		const char		at(size_t) const;
		Cadena 			substr(size_t, size_t) const;	
		
	private:
		// Atributos
		char* s_;
		size_t tam_;

};

// Operadores externos
// Concatenacion
Cadena 	operator	+	(const Cadena&, const Cadena&) 	noexcept;

// Comparacion
// Como el compilador no sabe que metodo usar al pasar const char* y Cadena, ya que puede transformar
// Cadena a const char* o const char* a cadena, hay que sobrecargar 2 veces mas los operadores para dejarlo claro
bool operator <	 (const Cadena&, const char*)	noexcept;
bool operator >	 (const Cadena&, const char*)	noexcept;
bool operator <= (const Cadena&, const char*) 	noexcept;
bool operator >= (const Cadena&, const char*) 	noexcept;
bool operator != (const Cadena&, const char*) 	noexcept;
bool operator == (const Cadena&, const char*) 	noexcept;
bool operator >	 (const Cadena&, const Cadena&)	noexcept;
bool operator <	 (const Cadena&, const Cadena&)	noexcept;
bool operator <= (const Cadena&, const Cadena&) noexcept;
bool operator >= (const Cadena&, const Cadena&) noexcept;
bool operator == (const Cadena&, const Cadena&) noexcept;
bool operator != (const Cadena&, const Cadena&) noexcept;
bool operator <	 (const char*,   const Cadena&)	noexcept;
bool operator >	 (const char*, 	 const Cadena&)	noexcept;
bool operator <= (const char*, 	 const Cadena&) noexcept;
bool operator >= (const char*, 	 const Cadena&) noexcept;
bool operator != (const char*, 	 const Cadena&) noexcept;
bool operator == (const char*, 	 const Cadena&) noexcept;

#endif