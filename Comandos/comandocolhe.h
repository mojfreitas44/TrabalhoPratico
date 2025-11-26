//
// Created by Utilizador on 26/11/2025.
//

#ifndef COMANDOCOLHE_H
#define COMANDOCOLHE_H

#include "comando.h"

class ComandoColhe : public Comando {
public:
    std::string getNome() const override { return "colhe"; }
    bool executar(Jardim*& jardim, std::stringstream& parametros) override;
};

#endif //COMANDOCOLHE_H
