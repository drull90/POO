#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena{

	public:
		explicit Cadena(unsigned int = 0, char = ' ');				// OK
		Cadena(const Cadena&);										// OK
		Cadena(const char*);										// OK

		~Cadena();													// OK

		Cadena& 		operator 	= 	(Cadena&);					// OK
		Cadena& 		operator 	= 	(const char*);				// OK
		friend Cadena& 	operator 	+= 	(Cadena&, Cadena&);			// OK
		friend Cadena 	operator	+	(Cadena&, Cadena&);			// OK
		friend bool 	operator	<	(Cadena&, Cadena&);			// OK
		friend bool 	operator	>	(Cadena&, Cadena&);			// OK
		friend bool 	operator	<=	(Cadena&, Cadena&);			// OK
		friend bool 	operator	>=	(Cadena&, Cadena&);			// OK
		friend bool 	operator	==	(Cadena&, Cadena&);			// OK
		friend bool 	operator	!=	(Cadena&, Cadena&);			// OK	
		const char		operator	[]	(unsigned int n) const;		// OK
		char			operator	[]	(unsigned int n);			// OK
		operator 		const char* 	() const;					// OK

		unsigned int 	length();									// OK
		char 			at(unsigned int);							// OK
		const char		at(unsigned int) const;						// OK
		Cadena 			substr(unsigned int, unsigned int) const;				
		
	private:
		char* s_;
		unsigned int tam_;

};

#endif