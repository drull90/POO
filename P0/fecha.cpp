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

    switch (mes_){
        //Meses con 31 dias
        case 1:case 3:case 5:case 7:
        case 8:case 10:case 12:
            if(dia_ > 31)
                return false;
            break;
        //Meses con 30 dias
        case 4:case 6:case 9:case 11:
            if(dia_ > 30)
                return false;
            break;
        //Febrero
        case 2:
            if(anno_ % 4 == 0 && ( anno_ % 400 == 0 || anno_ % 100 !=0) ){
                if(dia_ > 29)
                    return false;
            }
            else{
                if(dia_ > 28)
                    return false;
            }
            break;
        default:
            // Fecha no esta entre 1 y 12
            return false;
            break;
    }
    if(dia_ < 0)
        return false;
    if(anno_ > AnnoMaximo || anno_ < AnnoMinimo)
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

    Fecha f {"29/2/2020"};
    cout << f.dia() << "/" << f.mes() << "/" << f.anno() << endl;
    return 0;
}