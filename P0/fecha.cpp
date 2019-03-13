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

/**
 * Validamos si la fecha es correcta
 */
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

    if(anno_ != fechaHoy->tm_year + 1900 || mes_ != fechaHoy->tm_mon + 1 || dia_ != fechaHoy->tm_mday || !rangoFecha())
        return false;
        

    return true;
}

/**
 * Comprobar rango de la fecha
 */
bool Fecha::rangoFecha(){

    if(this->anno_ < AnnoMinimo || this->anno_ > AnnoMaximo)
        return false;
    
    return true;
}

/**
 * Pre incremento
 */
Fecha& Fecha::operator ++ (){

    *this = *this + 1;

    if(!rangoFecha()) throw Invalida();

    return *this;
}

/**
 * Post incremento
 */
Fecha Fecha::operator ++ (int){

    Fecha aux {*this};

    *this = *this + 1;

    if(!rangoFecha()) throw Invalida();

    return aux;
}

/**
 * Pre decremento
 */
Fecha& Fecha::operator -- (){

    *this = *this - 1;

    if(!rangoFecha()) throw Invalida();

    return *this;
}

/**
 * Post decremento
 */
Fecha Fecha::operator -- (int){

    Fecha aux {*this};

    *this = *this - 1;

    if(!rangoFecha()) throw Invalida();

    return aux;
}

/**
 * Suma de Fecha + entero
 */
Fecha Fecha::operator + (int dia){
    time_t tiempo = time(nullptr);
    tm* fechaSumada = localtime(&tiempo);

    fechaSumada->tm_mday = this->dia_ + dia;
    fechaSumada->tm_mon = this->mes_ - 1;
    fechaSumada->tm_year = this->anno_ - 1900;

    mktime(fechaSumada);

    Fecha fechaAux {fechaSumada->tm_mday, fechaSumada->tm_mon + 1, fechaSumada->tm_year  + 1900};

    return fechaAux;
}

/**
 * Resta de Fecha - entero
 */
Fecha Fecha::operator - (int dia){

    time_t tiempo = time(nullptr);
    tm* fechaSumada = localtime(&tiempo);

    fechaSumada->tm_mday = this->dia_ - dia;
    fechaSumada->tm_mon = this->mes_ - 1;
    fechaSumada->tm_year = this->anno_ - 1900;

    mktime(fechaSumada);

    Fecha fechaAux {fechaSumada->tm_mday, fechaSumada->tm_mon + 1, fechaSumada->tm_year  + 1900};

    return fechaAux;
}

/** 
 * Suma de fecha - entero
 */
Fecha& Fecha::operator += (int dia){
    
    *this = *this + dia;

    if(!rangoFecha()) throw Invalida();

    return *this;
}

/**
 * Resta de fecha - entero
 */
Fecha& Fecha::operator -= (int dia){
    
    *this = *this - dia;

    if(!rangoFecha()) throw Invalida();

    return *this;
}

/**
 * Imprimir fecha 
 */
ostream& operator << (ostream& o, Fecha& fecha){

    cout << "hola" << endl;

    const char * diaSemana[] = { "Domingo", "Lunes",
                             "Martes", "Miércoles",
                             "Jueves", "Viernes", "Sábado"};

    time_t tiempo = time(nullptr);
    tm* fechaTiempo = localtime(&tiempo);

    fechaTiempo->tm_mday = fecha.dia_;
    fechaTiempo->tm_mon = fecha.mes_ - 1;
    fechaTiempo->tm_year = fecha.anno_ - 1900;

    mktime(fechaTiempo);

    o << diaSemana[fechaTiempo->tm_wday] << endl;
    

    return o;
}

ostream& operator << (ostream& o, Fecha fecha){

    const char * diaSemana[] = { "Domingo", "Lunes",
                             "Martes", "Miércoles",
                             "Jueves", "Viernes", "Sábado"};

    time_t tiempo = time(nullptr);
    tm* fechaTiempo = localtime(&tiempo);

    fechaTiempo->tm_mday = fecha.dia_;
    fechaTiempo->tm_mon = fecha.mes_ - 1;
    fechaTiempo->tm_year = fecha.anno_ - 1900;

    mktime(fechaTiempo);

    o << diaSemana[fechaTiempo->tm_wday] << endl;
    

    return o;
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

    Fecha f{11}, a;

    cout << ++f << endl;

    cout << ++f << endl;

    cout << ++f << endl;

    cout << ++f << endl;
    
    cout << ++f << endl;

    cout << ++f << endl;

    cout << ++f << endl;

    /*for(int i = 0; i < 367; ++i){
        cout << f.dia() << "/" << f.mes() << "/" << f.anno() << endl;
        ++f;
    }*/
    return 0;
}