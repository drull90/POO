#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena{

	public:
		// Constructores
		Cadena(const Cadena&) 									noexcept;
		Cadena(const char*) 									noexcept;
		explicit Cadena(unsigned long int  = 0, char = ' ') 	noexcept;
		
		// Destructor
		~Cadena();

		// Sobrecarga de operadores
		// Operadores internos
		Cadena& 		operator 	= 	(Cadena&) 						noexcept;
		Cadena& 		operator 	= 	(const char*) 					noexcept;
		const char		operator	[]	(unsigned long int n) const 	noexcept;
		char&			operator	[]	(unsigned long int n) 			noexcept;
		Cadena&			operator 	+= 	(const Cadena&) 				noexcept;
		
		// Operadores de conversion
		operator const char*() const;

		// Metodos
		inline unsigned long int length() noexcept;
		char& 			at(unsigned long int);
		const char		at(unsigned long int) const;
		Cadena 			substr(unsigned long int, unsigned long int) const;	
		
	private:
		// Atributos
		char* s_;
		unsigned long int tam_;

};

// Operadores externos
// Concatenacion
Cadena 	operator	+	(const Cadena&, const Cadena&) 	noexcept;

//Comparacion
// Como el compilador no sabe que metodo usar al pasar const char* y Cadena, ya que puede transformar
// Cadena a const char* o const char* a cadena, hay que sobrecargar 2 veces mas los operadores para dejarlo claro
bool 	operator	<	(const Cadena&, const char*)	noexcept;
bool 	operator	>	(const Cadena&, const char*)	noexcept;
bool 	operator	<=	(const Cadena&, const char*) 	noexcept;
bool 	operator	>=	(const Cadena&, const char*) 	noexcept;
bool 	operator	!=	(const Cadena&, const char*) 	noexcept;
bool 	operator	==	(const Cadena&, const char*) 	noexcept;
bool 	operator	>	(const Cadena&, const Cadena&)	noexcept;
bool 	operator 	<	(const Cadena&, const Cadena&)	noexcept;
bool 	operator	<=	(const Cadena&, const Cadena&) 	noexcept;
bool 	operator	>=	(const Cadena&, const Cadena&) 	noexcept;
bool 	operator	==	(const Cadena&, const Cadena&) 	noexcept;
bool 	operator	!=	(const Cadena&, const Cadena&) 	noexcept;
bool 	operator	<	(const char*,  	const Cadena&)	noexcept;
bool 	operator	>	(const char*, 	const Cadena&)	noexcept;
bool 	operator	<=	(const char*, 	const Cadena&) 	noexcept;
bool 	operator	>=	(const char*, 	const Cadena&) 	noexcept;
bool 	operator	!=	(const char*, 	const Cadena&) 	noexcept;
bool 	operator	==	(const char*, 	const Cadena&) 	noexcept;

#endif