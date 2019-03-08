#ifndef FECHA_HPP
#define FECHA_HPP

/**
 *
 */
class Fecha {
    public:
        int AnnoMinimo = 1902, AnnoMaximo = 2037;
        int dia() const;
        int mes() const;
        int anno() const;
        static const int dia_meses[];
        class Invalida{};
        Fecha(int dia = 0, int mes = 0, int anno = 0);
        Fecha(const Fecha& fecha);
        Fecha(const char*);
    private:
        int dia_, mes_, anno_;
        bool fechaValida() const;
        void normalizarFecha();
};

const int Fecha::dia_meses[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


#endif