#ifndef SOLO_H
#define SOLO_H
#include <string>
#include "Plantas/plantas.h"
#include "Ferramentas/ferramentas.h"

class Solo {
private:
    int agua;
    int nutrientes;
    Plantas* planta;
    Ferramentas* ferramenta;

public:
    Solo();
    ~Solo();

    bool estaVazio() const;
    Plantas * getPlanta() const;
    void setPlanta(Plantas* p);
    void iniciarAleatorio();
    void setFerramenta(Ferramentas* f);
    Ferramentas * getFerramenta() const;
    Ferramentas* retirarFerramenta();
};
#endif //SOLO_H
