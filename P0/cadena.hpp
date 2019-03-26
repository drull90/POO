#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena{

	public:
		// Constructores
		Cadena(const Cadena&) 							noexcept;
		Cadena(const char*) 							noexcept;
		explicit Cadena(unsigned int = 0, char = ' ') 	noexcept;
		
		// Destructor
		~Cadena();

		// Sobrecarga de operadores
		// Operadores internos
		Cadena& 		operator 	= 	(Cadena&) 				noexcept;
		Cadena& 		operator 	= 	(const char*) 			noexcept;
		const char		operator	[]	(unsigned int n) const 	noexcept;
		char&			operator	[]	(unsigned int n) 		noexcept;

		// Operadores externos
		friend Cadena& 	operator 	+= 	(Cadena&, Cadena&) 	noexcept;
		friend Cadena 	operator	+	(Cadena&, Cadena&) 	noexcept;
		friend bool 	operator	<	(Cadena&, Cadena&) 	noexcept;
		friend bool 	operator	>	(Cadena&, Cadena&)	noexcept;
		friend bool 	operator	<=	(Cadena&, Cadena&) 	noexcept;
		friend bool 	operator	>=	(Cadena&, Cadena&) 	noexcept;
		friend bool 	operator	==	(Cadena&, Cadena&) 	noexcept;
		friend bool 	operator	!=	(Cadena&, Cadena&) 	noexcept;
		
		// Operadores de conversion
		operator const char*() const;

		// Metodos
		inline unsigned int length() noexcept;
		char& 			at(unsigned int);
		const char		at(unsigned int) const;
		Cadena 			substr(unsigned int, unsigned int) const;	
		
	private:
		char* s_;
		unsigned int tam_;

};

#endif