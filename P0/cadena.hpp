#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena{

	public:
		explicit Cadena(unsigned int = 0, char = ' ');
		Cadena(const Cadena&);
		Cadena(const char*);
		~Cadena();

		Cadena& 	operator 	= 	(Cadena&);
		Cadena& 	operator 	+= 	(Cadena&);
		Cadena& 	operator	+	(Cadena&);
		Cadena& 	operator	<	(Cadena&);
		Cadena& 	operator	>	(Cadena&);
		Cadena& 	operator	<=	(Cadena&);
		Cadena& 	operator	>=	(Cadena&);
		Cadena& 	operator	==	(Cadena&);
		Cadena& 	operator	!=	(Cadena&);
		const char	operator	[]	(int n) const;
		char		operator	[]	(int n);

		unsigned int 	length();
		char 			at(int n);
		const char		at(int n) const;
		char* 			substr(unsigned int, unsigned int);
		
	private:
		char* s_;
		unsigned int tam_;

};

#endif