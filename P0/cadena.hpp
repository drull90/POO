#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena{

	public:
		// Constructores
		Cadena(const Cadena&) 							noexcept;
		Cadena(const char*) 							noexcept;
		explicit Cadena(unsigned long int  = 0, char = ' ') 	noexcept;
		
		// Destructor
		~Cadena();

		// Sobrecarga de operadores
		// Operadores internos
		Cadena& 		operator 	= 	(Cadena&) 				noexcept;
		Cadena& 		operator 	= 	(const char*) 			noexcept;
		const char		operator	[]	(unsigned int n) const 	noexcept;
		char&			operator	[]	(unsigned int n) 		noexcept;		

		// Operadores externos
		// Concatenacion
		friend Cadena 	operator	+	(const Cadena&, const Cadena&) 	noexcept;
		friend Cadena&	operator 	+= 	(Cadena&, const Cadena&) 		noexcept;

		//Comparacion
		// Como el compilador no sabe que metodo usar al pasar const char* y Cadena, ya que puede transformar
		// Cadena a const char* o const char* a cadena, hay que sobrecargar 2 veces mas los operadores para dejarlo claro
		friend bool 	operator	<	(const Cadena&, const char*)	noexcept;
		friend bool 	operator	>	(const Cadena&, const char*)	noexcept;
		friend bool 	operator	<=	(const Cadena&, const char*) 	noexcept;
		friend bool 	operator	>=	(const Cadena&, const char*) 	noexcept;
		friend bool 	operator	!=	(const Cadena&, const char*) 	noexcept;
		friend bool 	operator	==	(const Cadena&, const char*) 	noexcept;
		friend bool 	operator	>	(const Cadena&, const Cadena&)	noexcept;
		friend bool 	operator 	<	(const Cadena&, const Cadena&)	noexcept;
		friend bool 	operator	<=	(const Cadena&, const Cadena&) 	noexcept;
		friend bool 	operator	>=	(const Cadena&, const Cadena&) 	noexcept;
		friend bool 	operator	==	(const Cadena&, const Cadena&) 	noexcept;
		friend bool 	operator	!=	(const Cadena&, const Cadena&) 	noexcept;
		friend bool 	operator	<	(const char*,  	const Cadena&)	noexcept;
		friend bool 	operator	>	(const char*, 	const Cadena&)	noexcept;
		friend bool 	operator	<=	(const char*, 	const Cadena&) 	noexcept;
		friend bool 	operator	>=	(const char*, 	const Cadena&) 	noexcept;
		friend bool 	operator	!=	(const char*, 	const Cadena&) 	noexcept;
		friend bool 	operator	==	(const char*, 	const Cadena&) 	noexcept;
		
		// Operadores de conversion
		operator const char*() const;

		// Metodos
		inline unsigned int length() noexcept;
		char& 			at(unsigned int);
		const char		at(unsigned int) const;
		Cadena 			substr(unsigned int, unsigned int) const;	
		
	private:
		char* s_;
		unsigned long int tam_;

};

#endif