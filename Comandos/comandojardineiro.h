//
// Created by Rodrigo on 29/10/2025.
//

#ifndef TRABALHOPRATICO_COMANDOJARDINEIRO_H
#define TRABALHOPRATICO_COMANDOJARDINEIRO_H


#include <string>
#include "../Jardim/jardim.h"
#include "comando.h"
#include "../jardineiro.h"

class comandojardineiro : public Comando {
private:
    std::string nomeComando;
    void processarEntradaNaPosicao(Jardim* jardim, Jardineiro* j, int l, int c);
public:
    comandojardineiro(const std::string& nome) : nomeComando(nome) {}

    string getNome() const override { return nomeComando; }
    bool executar(Jardim*& jardim, std::stringstream& parametros) override;


};



#endif //TRABALHOPRATICO_COMANDOJARDINEIRO_H
