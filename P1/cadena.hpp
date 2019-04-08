#ifndef CADENA_HPP_
#define CADENA_HPP_

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
		const char		operator	[]	(unsigned long int n) const 	noexcept;
		char&			operator	[]	(unsigned long int n) 			noexcept;
		Cadena&			operator 	+= 	(const Cadena&) 				noexcept;

		// Metodos
		inline unsigned long int length() noexcept;
		char& 			at(unsigned long int);
		const char		at(unsigned long int) const;
		Cadena 			substr(unsigned long int, unsigned long int) const;
		const char* 	c_str() const noexcept;
		
	private:
		// Atributos
		char* s_;
		unsigned long int tam_;

};

// Operadores externos
// Concatenacion
Cadena 	operator	+	(const Cadena&, const Cadena&) 	noexcept;

//Comparacion
bool operator >	 (const Cadena&, const Cadena&)	noexcept;
bool operator <	 (const Cadena&, const Cadena&)	noexcept;
bool operator <= (const Cadena&, const Cadena&) noexcept;
bool operator >= (const Cadena&, const Cadena&) noexcept;
bool operator == (const Cadena&, const Cadena&) noexcept;
bool operator != (const Cadena&, const Cadena&) noexcept;

#endif