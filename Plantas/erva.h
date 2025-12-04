#ifndef TRABALHOPRATICO_ERVA_H
#define TRABALHOPRATICO_ERVA_H
#include "plantas.h"

class Erva : public Plantas {
    int idade;
    int contadorReproducao;
public:
    Erva();
    void simular(Jardim& jardim, int l, int c) override;
    char getTipo() const override { return 'e'; }
};

#endif //TRABALHOPRATICO_ERVA_H
