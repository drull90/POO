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
    if(!fechaValida()) throw Invalida("Fecha no valida constructor de enteros");
}

/**
 * Constructor de parametro cadena
 */
Fecha::Fecha(const char* fecha) {
    if(sscanf(fecha, "%i/%i/%i", &dia_, &mes_ ,&anno_) != 3 || !fechaValida()) 
        throw Invalida("Fecha no valida constructor de cadenas");
}

Fecha::Invalida::Invalida(const char* error){
    cout << error << endl;
}

/**
 * Validamos si la fecha es correcta
 */
bool Fecha::fechaValida() {

    time_t tiempo_calendario = time(nullptr);
    tm* fechaHoy = localtime(&tiempo_calendario);
    const int diasMeses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    dia_    = (dia_ == 0)   ? fechaHoy->tm_mday         : dia_;

    mes_    = (mes_ == 0)   ? fechaHoy->tm_mon + 1      : mes_;

    anno_   = (anno_ == 0)  ? fechaHoy->tm_year + 1900  : anno_;
 
    if(dia_ < 1 || mes_ < 1 || mes_ > 12 || !fechaEnRango())
        return false;
    if(dia_ > diasMeses[mes_ - 1] && mes_ != 2)
        return false;
    else{
        if(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)){
            if(dia_ > diasMeses[mes_ - 1] + 1)
                return false;
        }
        else
            if(dia_ > diasMeses[mes_ - 1])
                return false;
    }

    return true;
}

/**
 * Comprobar rango de los años de la fecha
 */
bool Fecha::fechaEnRango(){ 
    return (this->anno_ >= AnnoMinimo || this->anno_ <= AnnoMaximo); 
}

/**
 * Pre incremento
 */
Fecha& Fecha::operator ++ (){  return *this += 1; }

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
Fecha& Fecha::operator -- (){ return *this += -1; }

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
Fecha& Fecha::operator -= (int dia){ return *this += -dia; }

/** 
 * Suma de fecha + entero
 */
Fecha& Fecha::operator += (int dia){

    time_t tiempo = time(nullptr);
    tm* fechaSumada = localtime(&tiempo);

    fechaSumada->tm_mday    = this->dia_ + 1;
    fechaSumada->tm_mon     = this->mes_ - 1;
    fechaSumada->tm_year    = this->anno_ - 1900;
    fechaSumada->tm_hour    = 12;

    mktime(fechaSumada);

    Fecha aux {fechaSumada->tm_mday, fechaSumada->tm_mon + 1, fechaSumada->tm_year + 1900};

    *this = aux;
    
    if(!fechaEnRango()) throw Invalida("Fecha no en rango");

    return *this;
}

/**
 * Imprimir fecha 
 */
ostream& operator << (ostream& o, const Fecha& fecha){

    time_t tiempo = time(nullptr);
    tm* fechaTiempo = localtime(&tiempo);

    fechaTiempo->tm_mday    = fecha.dia();
    fechaTiempo->tm_mon     = fecha.mes() - 1;
    fechaTiempo->tm_year    = fecha.anno() - 1900;
    fechaTiempo->tm_hour    = 12;

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

bool Fecha::operator < (Fecha& fecha){ 

    if(this->anno_ < fecha.anno_) 
        return true;
    else{
        if(this->anno_ > fecha.anno_)
            return false;
        else{
            if(this->mes_ < fecha.mes_)
                return true;
            else{
                if(this->mes_ > fecha.mes_)
                    return false;
                else{
                    if(this->dia_ < fecha.dia_)
                        return true;
                    else{
                        if(this->dia_ > fecha.dia_)
                            return false;
                    }
                }
            }
        }
    }
    
    return false;
}

bool Fecha::operator == (Fecha& fecha){
    return (this->anno_ == fecha.anno_ && this->mes_ == fecha.mes_ && this->dia_ == fecha.dia_);
}

bool Fecha::operator > (Fecha& fecha){
    return fecha < *this;
}

bool Fecha::operator <= (Fecha& fecha){
    return !(fecha < * this);
}

bool Fecha::operator >= (Fecha& fecha){
    return !(*this < fecha);
}

bool Fecha::operator != (Fecha& fecha){
    return !(*this == fecha);
}

int Fecha::dia() const{ return dia_; }

int Fecha::mes() const{ return mes_; }

int Fecha::anno() const{ return anno_; }