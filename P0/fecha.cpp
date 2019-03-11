#include "fecha.hpp"
#include <iostream>
#include <stdio.h>
#include <ctime>

using namespace std;

/**
 * Constructor de ningun parametro, a los 3
 */
Fecha::Fecha(int dia, int mes, int anno) : dia_{dia}, mes_{mes}, anno_{anno} {
    if(!fechaValida()) throw Invalida();
}

/**
 * Constructor de parametro cadena
 */
Fecha::Fecha(const char* fecha) {
    if(sscanf(fecha, "%i/%i/%i", &dia_, &mes_ ,&anno_) != 3) throw Invalida();
    if(!fechaValida()) throw Invalida();
}

bool Fecha::fechaValida() {

    time_t tiempo_calendario = time(nullptr);
    tm* fechaHoy = localtime(&tiempo_calendario);

    if(dia_ == 0){
        dia_ = fechaHoy->tm_mday;
    }
    if(mes_ == 0){
        mes_ = fechaHoy->tm_mon + 1;        //Mes 0..11
    }
    if(anno_ == 0){
        anno_ = fechaHoy->tm_year + 1900;   //Años desde 1900
    }

    fechaHoy->tm_mday = dia_;
    fechaHoy->tm_mon = mes_ - 1;
    fechaHoy->tm_year = anno_ - 1900;   

    mktime(fechaHoy);

    if(anno_ != fechaHoy->tm_year + 1900 || mes_ != fechaHoy->tm_mon + 1 || dia_ != fechaHoy->tm_mday || anno_ < AnnoMinimo || anno_ > AnnoMaximo)
        return false;

    return true;
}

/**
 * Post incremento
 */
Fecha Fecha::operator++(int dia){
    
    Fecha aux {*this};

    aux = aux + 1;

    return aux;
}

Fecha Fecha::operator++(){

    Fecha aux {*this};

    aux = aux + 1;

    return aux;
}

Fecha Fecha::operator+(int dia){
    time_t tiempo = time(nullptr);
    tm* fechaSumada = localtime(&tiempo);

    fechaSumada->tm_mday = this->dia_ + dia;
    fechaSumada->tm_mon = this->mes_ - 1;
    fechaSumada->tm_year = this->anno_ - 1900;

    mktime(fechaSumada);

    Fecha fechaAux {fechaSumada->tm_mday, fechaSumada->tm_mon + 1, fechaSumada->tm_year  + 1900};

    return fechaAux;
}

int Fecha::dia() const{
    return dia_;
}

int Fecha::mes() const{
    return mes_;
}

int Fecha::anno() const{
    return anno_;
}

int main() {
    Fecha f{1,1,2020};

    Fecha a = f;

    cout << f.dia() << "/" << f.mes() << "/" << f.anno() << endl;

    cout << a.dia() << "/" << a.mes() << "/" << a.anno() << endl;


    /*for(int i = 0; i < 40; ++i){
        cout << f.dia() << "/" << f.mes() << "/" << f.anno() << endl;
        f++;
    }*/
    return 0;
}