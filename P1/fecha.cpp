#include <cstdio>
#include <iostream>
 
#include "fecha.hpp"

/**
 * Constructor de ningun parametro, a los 3
 */
Fecha::Fecha(int dia, int mes, int anno) : dia_{dia}, mes_{mes}, anno_{anno} {
	fechaValida();
}

/**
 * Constructor de parametro const char*
 */
Fecha::Fecha(const char* fecha) {
	if(sscanf(fecha, "%i/%i/%i", &dia_, &mes_ ,&anno_) != 3)
		throw Invalida((const char*)"Cadena fecha introducida no válida");
	fechaValida();
}

/**
 * Destructor
 */
Fecha::~Fecha(){
	if(fecha != NULL)
		delete[] fecha;
	anno_ 	= 0;
	mes_ 	= 0;
	dia_ 	= 0;
}

/**
 * Constructor clase Invalida
 */
Fecha::Invalida::Invalida(const char* error) noexcept : error_{error} {}

/**
 * Metodo que devuelve el tipo de error
 */
const char* Fecha::Invalida::por_que() const noexcept {
	return error_;
}

/**
 * Validamos si la fecha es correcta
 */
void Fecha::fechaValida() {

	time_t tiempo_calendario = time(nullptr);
	tm* fechaHoy = localtime(&tiempo_calendario);
	const int diasMeses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	dia_    = (dia_ == 0)   ? fechaHoy->tm_mday         : dia_;

	mes_    = (mes_ == 0)   ? fechaHoy->tm_mon + 1      : mes_;

	anno_   = (anno_ == 0)  ? fechaHoy->tm_year + 1900  : anno_;
 
	if(dia_ < 1 || mes_ < 1 || mes_ > 12)
		throw Invalida((const char*)"Fecha fuera de rango");
	if(!fechaEnRango())
		throw Invalida((const char*)"Año fuera del rango");
	if(dia_ > diasMeses[mes_ - 1] && mes_ != 2)
		throw Invalida((const char*)"Dia fuera del rango del mes");
	else{
		if(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)){
			if(dia_ > diasMeses[mes_ - 1] + 1)
				throw Invalida((const char*)"Dia fuera del rango del mes");
		}
		else
			if(dia_ > diasMeses[mes_ - 1])
				throw Invalida((const char*)"Dia fuera del rango del mes");
	}
}

/**
 * Comprobar rango de los años de la fecha
 */
bool Fecha::fechaEnRango() const noexcept{
	return (this->anno_ >= AnnoMinimo || this->anno_ <= AnnoMaximo); 
}

/**
 * Suma con asignacion
 */
Fecha& Fecha::operator += (int dia){

	time_t tiempo = time(nullptr);
	tm* fechaSumada = localtime(&tiempo);

	fechaSumada->tm_mday	= (dia_		+ dia);
	fechaSumada->tm_mon     = (mes_		- 1);
	fechaSumada->tm_year    = (anno_	- 1900);
	fechaSumada->tm_hour    = 12;

	mktime(fechaSumada);

	dia_ 	= fechaSumada->tm_mday;
	mes_ 	= (fechaSumada->tm_mon + 1);
	anno_ 	= (fechaSumada->tm_year + 1900);
	
	if(!fechaEnRango()) throw Invalida((const char*)"Año fuera del rango");

	return *this;
}

/**
 * Pre incremento
 */
Fecha& Fecha::operator ++ (){  return (*this += 1); }

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
Fecha& Fecha::operator -- (){ return (*this += -1); }

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
Fecha Fecha::operator + (int dia) const{

	Fecha fechaAux = *this;

	fechaAux += dia; 

	return fechaAux;
}

/**
 * Resta de Fecha - entero
 */
Fecha Fecha::operator - (int dia) const{

	Fecha fechaAux = *this;

	fechaAux += -dia; 

	return fechaAux;
}

/**
 * Resta de fecha - entero
 */
Fecha& Fecha::operator -= (int dia){ return (*this += -dia); }

/**
 * Imprimir fecha 
 */
const char* Fecha::cadena() noexcept{

	fecha = new char[50];
	time_t tiempo = time(nullptr);
	tm* fechaTiempo = localtime(&tiempo);
	std::locale::global(std::locale(""));

	fechaTiempo->tm_mday    = this->dia_;
	fechaTiempo->tm_mon     = this->mes_ - 1;
	fechaTiempo->tm_year    = this->anno_ - 1900;
	fechaTiempo->tm_hour    = 12;

	mktime(fechaTiempo);

	strftime(fecha, 100, "%A %e de %B de %G", fechaTiempo);

	return fecha;
}

/**
 * Operador de comparacion de fecha
 */
bool operator < (const Fecha& fecha, const Fecha& fecha2) noexcept{ 

	if(fecha.anno() < fecha2.anno())
		return true;
	else{
		if(fecha.anno() > fecha2.anno())
			return false;
		else{
			if(fecha.mes() < fecha2.mes())
				return true;
			else{
				if(fecha.mes() > fecha2.mes())
					return false;
				else{
					if(fecha.mes() < fecha2.mes())
						return true;
					else{
						if(fecha.mes() > fecha2.mes())
							return false;
					}
				}
			}
		}
	}
	
	return false;
}

/**
 * Operador de comparacion de fecha
 */
bool operator == (const Fecha& fecha, const Fecha& fecha2) noexcept{
	return (fecha2.anno() == fecha.anno() && fecha2.mes() == fecha.mes() && fecha2.dia() == fecha.dia());
}

/**
 * Operador de comparacion de fecha
 */
bool operator > (const Fecha& fecha, const Fecha& fecha2) noexcept{
	return fecha2 < fecha;
}

/**
 * Operador de comparacion de fecha
 */
bool operator <= (const Fecha& fecha, const Fecha& fecha2) noexcept{
	return !(fecha2 < fecha);
}

/**
 * Operador de comparacion de fecha
 */
bool operator >= (const Fecha& fecha, const Fecha& fecha2) noexcept{
	return !(fecha < fecha2);
}

/**
 * Operador de comparacion de fecha
 */
bool operator != (const Fecha& fecha, const Fecha& fecha2) noexcept{
	return !(fecha == fecha2);
}

/**
 * Imprimir fecha 
 */
std::ostream& operator << (std::ostream& o, const Fecha& fecha) noexcept {

	char buffer[100];
	time_t tiempo = time(nullptr);
	tm* fechaTiempo = localtime(&tiempo);
	std::locale::global(std::locale(""));

	fechaTiempo->tm_mday    = fecha.dia_;
	fechaTiempo->tm_mon     = fecha.mes_ - 1;
	fechaTiempo->tm_year    = fecha.anno_ - 1900;
	fechaTiempo->tm_hour    = 12;

	mktime(fechaTiempo);

	strftime(buffer, 100, "%A %e de %B de %G", fechaTiempo);

	o << buffer;

	return o;
}

/**
 * Leer fecha
 */
std::istream& operator >> (std::istream& i, const Fecha& fecha) noexcept {


	return i;
}

int main(){

	Fecha f;

	std::cout << f << std::endl;

	return 0;
}