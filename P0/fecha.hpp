#ifndef FECHA_HPP
#define FECHA_HPP

#include<iostream>

using namespace std;

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
        Fecha   operator +  (int);
        Fecha   operator -  (int);
        friend ostream& operator << (ostream& o, const Fecha& fecha);

        //Metodos
        int dia() const;
        int mes() const;
        int anno() const;

        //Clases
        class Invalida{
            public:
                Invalida(const char*);
        };

        //Atributos
        int AnnoMinimo = 1902, AnnoMaximo = 2037;
        
    private:
        int dia_, mes_, anno_;
        bool fechaValida();
        bool fechaEnRango();
        char* fechaTraducida(tm*) const;
};

#endif