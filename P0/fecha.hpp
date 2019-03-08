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
        class Invalida{};
        Fecha(int dia = 0, int mes = 0, int anno = 0);
        Fecha(const Fecha& fecha);
        Fecha(const char*);
    private:
        int dia_, mes_, anno_;
        bool fechaValida();
        void normalizarFecha();
};

#endif