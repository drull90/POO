#include "fecha.hpp"
#include <iostream>
#include <stdio.h>
#include <ctime>

using namespace std;

/**
 * Constructor de ningun parametro, a los 3
 */
Fecha::Fecha(int dia, int mes, int anno) : dia_(dia), mes_(mes), anno_(anno) {
    Fecha::normalizarFecha();
    if(!Fecha::fechaValida()) throw Invalida();
}

/**
 * Constructor copia
 */
Fecha::Fecha(const Fecha& fecha) : dia_(fecha.dia()), mes_(fecha.mes()), anno_(fecha.anno()){}

Fecha::Fecha(const char* fecha) {
    if(sscanf(fecha, "%i/%i/%i", &dia_, &mes_ ,&anno_) != 3) throw Invalida();
    Fecha::normalizarFecha();
    if(!Fecha::fechaValida()) throw Invalida();
}

void Fecha::normalizarFecha(){
    std::time_t tiempo_calendario = std::time(nullptr);
    std::tm* fechaHoy = std::localtime(&tiempo_calendario);

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

bool Fecha::fechaValida() const{

    if(dia_ < 0)
        return false;
    if(dia_ > dia_meses[mes_ - 1] && mes_ !=2)
        return false;
    else{
        if( anno_ % 4 == 0 && ( anno_ % 400 == 0 || anno_ % 100 !=0)) {
            if(dia_ > dia_meses[mes_ - 1] + 1)
                return false;
        }
        else{
            if(dia_ > dia_meses[mes_ - 1]){

                return false;   
            }
                
        }
        
    }
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
    Fecha f {"29/2/2020"};
    cout << f.dia() << "/" << f.mes() << "/" << f.anno() << endl;
    return 0;
}