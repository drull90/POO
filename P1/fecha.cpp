#include <cstdio>
#include <iostream>
#include <cstring>
#include <clocale>
#include <time.h>
#include <iomanip>

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

	if(sscanf(fecha, "%d/%d/%d", &dia_, &mes_ ,&anno_) != 3)
		throw Invalida("Cadena fecha introducida no válida");

	fechaValida();
}

/**
 * Constructor clase Invalida
 */
Fecha::Invalida::Invalida(const char* error) noexcept : error_{error} {}

/**
 * Validamos si la fecha es correcta
 */
void Fecha::fechaValida() {

	time_t rawtime;
	struct tm* fechaHoy;

	time(&rawtime);
	fechaHoy = localtime(&rawtime);

	if(dia_  == 0) 	dia_ 	= fechaHoy->tm_mday;
  	if(mes_  == 0) 	mes_ 	= fechaHoy->tm_mon 	+ 1;
  	if(anno_ == 0) 	anno_ 	= fechaHoy->tm_year + 1900;

	const int diasMeses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 
	if(dia_ < 1 || mes_ < 1 || mes_ > 12)
		throw Invalida("Fecha fuera de rango");
	if(!fechaEnRango())
		throw Invalida("Año fuera del rango");
	if(dia_ > diasMeses[mes_ - 1] && mes_ != 2)
		throw Invalida("Dia fuera del rango del mes");
	else{
		if(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)){
			if(dia_ > diasMeses[mes_ - 1] + 1)
				throw Invalida("Dia fuera del rango del mes");
		}
		else
			if(dia_ > diasMeses[mes_ - 1])
				throw Invalida("Dia fuera del rango del mes");
	}
}

/**
 * Comprobar rango de los años de la fecha
 */
bool Fecha::fechaEnRango() const noexcept{
	return (this->anno_ >= AnnoMinimo && this->anno_ <= AnnoMaximo); 
}

/**
 * Suma con asignacion
 */
Fecha& Fecha::operator += (int dia){

	time_t rawtime;
	struct tm* fechaSumada;

	time ( &rawtime );
	fechaSumada = localtime ( &rawtime );
	fechaSumada->tm_mday	= (dia_		+ dia);
	fechaSumada->tm_mon 	= (mes_		- 1);
	fechaSumada->tm_year 	= (anno_	- 1900);

	mktime(fechaSumada);

	dia_ 	= fechaSumada->tm_mday;
	mes_ 	= fechaSumada->tm_mon 	+ 1;
	anno_ 	= fechaSumada->tm_year 	+ 1900;
	
	if(!fechaEnRango()) throw Invalida("Año fuera del rango");

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
const char* Fecha::cadena() const noexcept{

	static char fecha[50];

	time_t rawtime;
	struct tm* fechaTiempo;

	time ( &rawtime );
	fechaTiempo = localtime ( &rawtime );

	std::locale::global(std::locale(""));

	fechaTiempo->tm_mday    = dia_;
	fechaTiempo->tm_mon     = mes_ - 1;
	fechaTiempo->tm_year    = anno_ - 1900;

	mktime(fechaTiempo);

	strftime(fecha, 50, "%A %e de %B de %Y", fechaTiempo);

	return fecha;
}

/**
 * Operador << inserccion
 */
std::ostream& operator << (std::ostream& o, const Fecha& fecha) noexcept{

	o << fecha.cadena();

	return o;
}

/**
 * Operador >> extraccion
 */
std::istream& operator >> (std::istream& i, Fecha& fecha) {

	char f[11];

	i >> std::setw(11) >> f;

	try{
		fecha = Fecha(f);
	}
	catch(const Fecha::Invalida& e){
		i.setstate(std::ios_base::failbit);
		throw;
	}

	return i;
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
					if(fecha.dia() < fecha2.dia())
						return true;
					else{
						if(fecha.dia() > fecha2.dia())
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