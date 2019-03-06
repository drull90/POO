#ifndef FECHA_HPP
#define FECHA_HPP

/**
 *
 */
class Fecha {
    public:
        int AnnoMinimo, AnnoMaximo;
        int dia() const;
        int mes() const;
        int anno() const;
    private:
        int dia, mes, anno;
        bool fechaValida() const;
        class Invalida{};

    
};



#endif