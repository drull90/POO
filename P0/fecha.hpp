#ifndef FECHA_HPP
#define FECHA_HPP

#include<iostream>

using namespace std;

/**
 * Clase Fecha
 */
class Fecha {
    public:
        int AnnoMinimo = 1902, AnnoMaximo = 2037;
        int dia() const;
        int mes() const;
        int anno() const;
        class Invalida{};
        explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
        Fecha(const char*);
        Fecha   operator ++(int);
        Fecha   operator --(int);
        Fecha&  operator ++();
        Fecha&  operator --();
        Fecha   operator +(int);
        Fecha   operator -(int);
        Fecha&  operator +=(int);
        Fecha&  operator -=(int);
        friend ostream& operator << (ostream& o, const Fecha& fecha);

    private:
        int dia_, mes_, anno_;
        bool fechaValida();
        bool rangoFecha();
};

char* fechaTraducida(const tm*);

#endif