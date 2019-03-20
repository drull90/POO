#ifndef FECHA_HPP
#define FECHA_HPP

#include <iostream>

/**
 * Clase Fecha
 */
class Fecha {
    public:
        //Constructores
        Fecha(const char*);
        explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
        
        //Sobrecargas de operadores
        Fecha&  operator ++ ();
        Fecha&  operator -- ();
        Fecha   operator ++ (int);
        Fecha   operator -- (int);
        Fecha&  operator += (int);
        Fecha&  operator -= (int);
        Fecha   operator +  (int) const;
        Fecha   operator -  (int) const;
		friend bool operator <  (const Fecha&, const Fecha&) noexcept;
		friend bool operator == (const Fecha&, const Fecha&) noexcept;
		friend bool operator >  (const Fecha&, const Fecha&) noexcept;
		friend bool operator <= (const Fecha&, const Fecha&) noexcept;
		friend bool operator >= (const Fecha&, const Fecha&) noexcept;
		friend bool operator != (const Fecha&, const Fecha&) noexcept;
        friend std::ostream& operator << (std::ostream&, const Fecha&) noexcept;

        //Metodos
        inline int dia() 	const noexcept;
        inline int mes() 	const noexcept;
        inline int anno()	const noexcept;

        //Clases
        class Invalida{
            public:
                Invalida(const char*) noexcept;
                const char* por_que() const noexcept;
            private:
                const char* error_;
        };

        //Atributos
        static const int AnnoMinimo = 1902, AnnoMaximo = 2037;
        
    private:
        int dia_, mes_, anno_;
        void fechaValida();
        bool fechaEnRango() const noexcept;
};

#endif