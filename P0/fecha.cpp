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
 * Comprobar rango de los años de la fecha
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

    *this += 1;

    return *this;
}

/**
 * Post incremento
 */
Fecha Fecha::operator ++ (int){

    Fecha aux = *this;

    *this += 1;

    return aux;
}

/**
 * Pre decremento
 */
Fecha& Fecha::operator -- (){

    *this += -1;

    return *this;
}

/**
 * Post decremento
 */
Fecha Fecha::operator -- (int){

    Fecha aux = *this;

    *this += -1;

    return aux;
}

/**
 * Suma de Fecha + entero
 */
Fecha Fecha::operator + (int dia){

    Fecha fechaAux = *this;

    fechaAux += dia; 

    return fechaAux;
}

/**
 * Resta de Fecha - entero
 */
Fecha Fecha::operator - (int dia){

    Fecha fechaAux = *this;

    fechaAux += -dia; 

    return fechaAux;
}

/**
 * Resta de fecha - entero
 */
Fecha& Fecha::operator -= (int dia){
    
    *this = *this += - dia;

    return *this;
}

/** 
 * Suma de fecha + entero
 */
Fecha& Fecha::operator += (int dia){

    time_t tiempo = time(nullptr);
    tm* fechaSumada = localtime(&tiempo);

    fechaSumada->tm_mday = this->dia_ + dia;
    fechaSumada->tm_mon = this->mes_ - 1;
    fechaSumada->tm_year = this->anno_ - 1900;

    mktime(fechaSumada);

    Fecha aux {fechaSumada->tm_mday, fechaSumada->tm_mon + 1, fechaSumada->tm_year + 1900};

    if(!rangoFecha()) throw Invalida();

    *this = aux;
    
    return *this;
}

/**
 * Imprimir fecha 
 */
ostream& operator << (ostream& o, const Fecha& fecha){

    time_t tiempo = time(nullptr);
    tm* fechaTiempo = localtime(&tiempo);

    fechaTiempo->tm_mday = fecha.dia();
    fechaTiempo->tm_mon = fecha.mes() - 1;
    fechaTiempo->tm_year = fecha.anno() - 1900;

    o << fechaTraducida(fechaTiempo) <<  endl;
    
    return o;
}

char* fechaTraducida(const tm* fecha){

    const char* diaSemana[] = { "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};

    const char* mesAnno[] = { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Nobiembre", "Diciembre"};

    
    
}

int Fecha::dia() const{ return dia_; }

int Fecha::mes() const{ return mes_; }

int Fecha::anno() const{ return anno_; }

int main() {

    Fecha f{11,0};

    cout << f << endl;

    return 0;
}