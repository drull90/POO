#include <iostream>
#include <stdio.h>
#include <ctime>
#include <string.h>

#include "fecha.hpp"

using namespace std;

/**
 * Constructor de ningun parametro, a los 3
 */
Fecha::Fecha(int dia, int mes, int anno) : dia_{dia}, mes_{mes}, anno_{anno} {
    if(!fechaValida()) throw Invalida("Fecha no valida parametros");
}

Fecha::Invalida::Invalida(const char* error){
    cout << error << endl;
}

/**
 * Constructor de parametro cadena
 */
Fecha::Fecha(const char* fecha) {
    if(sscanf(fecha, "%i/%i/%i", &dia_, &mes_ ,&anno_) != 3 || !fechaValida()) throw Invalida("Fecha no valida cadenas");
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

    if(anno_ != fechaHoy->tm_year + 1900 || mes_ != fechaHoy->tm_mon + 1 || dia_ != fechaHoy->tm_mday || !fechaEnRango())
        return false;

    return true;
}

/**
 * Comprobar rango de los años de la fecha
 */
bool Fecha::fechaEnRango(){

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

    fechaSumada->tm_mday = this->dia_ + 1;
    fechaSumada->tm_mon = this->mes_ - 1;
    fechaSumada->tm_year = this->anno_ - 1900;

    mktime(fechaSumada);

    Fecha aux {fechaSumada->tm_mday, fechaSumada->tm_mon + 1, fechaSumada->tm_year + 1900};

    if(!fechaEnRango()) throw Invalida("Fecha no en rango");

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

    o << fecha.fechaTraducida(fechaTiempo) <<  endl;

    return o;
}

char* Fecha::fechaTraducida(tm* fecha) const{

    const char* diaSemana[] = { "domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};

    const char* mesAnno[] = { "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

    char* cad;
    char buffer[20];

    mktime(fecha);

    strcpy(cad, diaSemana[fecha->tm_wday]);
    snprintf(buffer, 20, " %i de ", fecha->tm_mday);
    strcat(cad, buffer);
    strcat(cad, mesAnno[fecha->tm_mon]);
    snprintf(buffer, 20, " de %i ", fecha->tm_year + 1900);
    strcat(cad, buffer);

    return cad;
}

int Fecha::dia() const{ return dia_; }

int Fecha::mes() const{ return mes_; }

int Fecha::anno() const{ return anno_; }

int main() {

    Fecha f{12, 9, 2010};

    cout << f << endl;

    return 0;
}