#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena{

	public:
		explicit Cadena(unsigned int = 0, char = ' ') noexcept;				// OK
		Cadena(const Cadena&) noexcept;										// OK
		Cadena(const char*) noexcept;										// OK

		~Cadena();															// OK

		Cadena& 		operator 	= 	(Cadena&) noexcept;					// OK
		Cadena& 		operator 	= 	(const char*) noexcept;				// OK
		Cadena& 		operator 	+= 	(Cadena&) noexcept;					// OK
		Cadena 			operator	+	(Cadena&) noexcept;					// OK
		friend bool 	operator	<	(Cadena&, Cadena&) noexcept;		// OK
		friend bool 	operator	>	(Cadena&, Cadena&) noexcept;		// OK
		friend bool 	operator	<=	(Cadena&, Cadena&) noexcept;		// OK
		friend bool 	operator	>=	(Cadena&, Cadena&) noexcept;		// OK
		friend bool 	operator	==	(Cadena&, Cadena&) noexcept;		// OK
		friend bool 	operator	!=	(Cadena&, Cadena&) noexcept;		// OK	
		const char		operator	[]	(unsigned int n) const noexcept;	// OK
		char			operator	[]	(unsigned int n) noexcept;			// OK
		operator 		const char* 	() const;							// OK

		inline unsigned int length() noexcept;								// OK
		char 			at(unsigned int);									// OK
		const char		at(unsigned int) const;								// OK
		Cadena 			substr(unsigned int, unsigned int) const;				
		
	private:
		char* s_;
		unsigned int tam_;

};

#endif