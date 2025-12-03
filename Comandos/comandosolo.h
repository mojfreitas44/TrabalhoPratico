#ifndef COMANDOSOLO_H
#define COMANDOSOLO_H
#include "comando.h"

class ComandoSolo : public Comando {
    std::string nomeComando;
public:
    ComandoSolo(const std::string& nome) : nomeComando(nome) {}
    std::string getNome() const override { return nomeComando; } // ou 'lsolo' conforme enunciado
    bool executar(Jardim*& jardim, std::stringstream& parametros) override;
};
#endif