#include "fecha.hpp"
#include <iostream>
#include <stdio.h>
#include <ctime>

using namespace std;

/**
 * Constructor de ningun parametro, a los 3
 */
Fecha::Fecha(int dia, int mes, int anno) : dia_{dia}, mes_{mes}, anno_{anno} {
    normalizarFecha();
    if(!fechaValida()) throw Invalida();
}

/**
 * Constructor copia
 */
Fecha::Fecha(const Fecha& fecha) : dia_{fecha.dia_}, mes_{fecha.mes_}, anno_{fecha.anno_}{}

Fecha::Fecha(const char* fecha) {
    if(sscanf(fecha, "%i/%i/%i", &dia_, &mes_ ,&anno_) != 3) throw Invalida();
    normalizarFecha();
    if(!fechaValida()) throw Invalida();
}

void Fecha::normalizarFecha(){
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
}

bool Fecha::fechaValida() {

    time_t tiempo_calendario = time(nullptr);
    tm* fechaHoy = localtime(&tiempo_calendario);

    fechaHoy->tm_year = anno_ - 1900;
    fechaHoy->tm_mon = mes_ - 1;
    fechaHoy->tm_mday = dia_;

    mktime(fechaHoy);

    if(anno_ != fechaHoy->tm_year + 1900 || mes_ != fechaHoy->tm_mon + 1 || dia_ != fechaHoy->tm_mday)
        return false;

    return true;
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
    Fecha f {"0/0/0"};
    cout << f.dia() << "/" << f.mes() << "/" << f.anno() << endl;
    return 0;
}