#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena{

	public:
		explicit Cadena(int = 0, char = ' ');
		Cadena(Cadena&);
		Cadena(const char*);
		~Cadena();

		Cadena& operator 	= 	(Cadena&);
		Cadena& operator 	+= 	(Cadena&);
		Cadena& operator	+	(Cadena&);
		Cadena& operator	<	(Cadena&);
		Cadena& operator	>	(Cadena&);
		Cadena& operator	<=	(Cadena&);
		Cadena& operator	>=	(Cadena&);
		Cadena& operator	==	(Cadena&);
		Cadena& operator	!=	(Cadena&);

		unsigned int length();


	private:

		char* s_;
		unsigned int tam_;

};

#endif