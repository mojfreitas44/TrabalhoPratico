#include "interpretador.h"
#include <iostream>
#include <sstream>
#include "Jardim/jardim.h"
#include "Jardim/posicao.h"
#include "Comandos/comandojardim.h"
#include "Comandos/comandojardineiro.h"
#include "Comandos/comandoplantas.h"
#include "Comandos/comandoavanca.h"
#include "Comandos/comandoferramentas.h"
#include "Comandos/comandocolhe.h"
#include "Comandos/comandosolo.h"

using namespace std;

Interpretador::Interpretador() {
    // Inicializar os comandos disponíveis
    comandos.push_back(new ComandoJardim());
    comandos.push_back(new comandojardineiro("entra"));
    comandos.push_back(new comandojardineiro("sai"));
    comandos.push_back(new comandojardineiro("e"));
    comandos.push_back(new comandojardineiro("d"));
    comandos.push_back(new comandojardineiro("c"));
    comandos.push_back(new comandojardineiro("b"));
    comandos.push_back(new ComandoPlanta("planta"));
    comandos.push_back(new ComandoPlanta("lplantas"));
    comandos.push_back(new ComandoPlanta("lplanta"));
    comandos.push_back(new Comandoavanca("avanca"));
    comandos.push_back(new ComandoFerramentas("lferr"));
    comandos.push_back(new ComandoFerramentas("larga"));
    comandos.push_back(new ComandoFerramentas("pega"));
    comandos.push_back(new ComandoFerramentas("compra"));
    comandos.push_back(new ComandoColhe());
    comandos.push_back(new ComandoSolo("lsolo"));
    comandos.push_back(new ComandoSolo("larea"));
}

Interpretador::~Interpretador() {
    for (Comando* cmd : comandos) {
        delete cmd;
    }
}

bool Interpretador::processarComando(const std::string& linha, Jardim*& jardim) {
    std::stringstream ss(linha);
    std::string cmdNome;
    ss >> cmdNome;

    // Lógica de validação do Jardim (Req 1)
    bool precisaDeJardim = !(cmdNome == "jardim" || cmdNome == "fim" || cmdNome == "executa");
    if (precisaDeJardim && jardim == nullptr) {
        std::cout << "Erro: Crie primeiro o jardim com 'jardim <l> <c>'" << std::endl;
        return false;
    }

    // Procura o comando
    for (Comando* cmd : comandos) {
        if (cmd->getNome() == cmdNome) {
            //cout << cmd->getNome()<< endl;
            // Encontrou! Chama o 'executar' desse objeto específico.
            // Os argumentos (o resto da stringstream) são passados.
            cout << cmd->getNome() << endl;
            return cmd->executar(jardim, ss);
        }
    }
    std::cout << "Comando invalido: " << cmdNome << std::endl;
    return false;
}




