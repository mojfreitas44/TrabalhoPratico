//
// Created by Rodrigo on 29/10/2025.
//

#include "comandojardineiro.h"
#include "../Solo.h"
#include <sstream>
#include <iostream>
using namespace std;

void comandojardineiro::processarEntradaNaPosicao(Jardim* jardim, Jardineiro* j, int l, int c) {
    // Atualizar posição do jardineiro
    j->setPosicao(l, c);

    // Verificar se há ferramenta no chão
    Solo* solo = jardim->getSolo(l, c);

    // Se houver ferramenta, retiramo-la com segurança
    if (solo->getFerramenta() != nullptr) {

        // CORREÇÃO: Usar o novo método que não faz delete
        Ferramentas* f = solo->retirarFerramenta();

        // Jardineiro guarda na mochila
        j->apanharFerramenta(f);

        cout << "Apanhou ferramenta: " << f->getTipo() << " (ID: " << f->getID() << ")" << endl;

        jardim->reporFerramenta();
    }
}

bool comandojardineiro::executar(Jardim*& jardim, std::stringstream& parametros) {
    cout << "DEBUG: Executando comando '" << nomeComando << "'" << endl;
    Jardineiro* j = jardim->getJardineiro();
    if (nomeComando == "entra") {
        string pos;
        if (parametros >> pos) {
            try {
                Posicao p = Posicao::deString(pos);

                // 1. Validar se a posição existe no jardim
                if (p.getLinha() >= 0 && p.getLinha() < jardim->getLinhas() &&
                    p.getColuna() >= 0 && p.getColuna() < jardim->getColunas()) {

                    // 2. Usar o método do Jardineiro
                    j->entrar(p.getLinha(), p.getColuna());
                    cout << "Entrou na posicao " << pos << "." << endl;
                    processarEntradaNaPosicao(jardim, j, p.getLinha(), p.getColuna());
                    return true;
                } else {
                    cout << "Posicao " << pos << " fora dos limites do jardim." << endl;
                    return false;
                }
            } catch (const std::exception& e) {
                cout << "Posicao invalida: " << e.what() << endl;
                return false;
            }
        }
        cout << "Parametro de posicao faltando para 'entra'." << endl;
        return false;
    }
    else if (nomeComando == "sai"){
        if(j->estaNoJardim()){
            j->sair(); // Método do jardineiro
            cout << "Saiu do jardim." << endl;
        }else{
            cout << "Nao esta no jardim." << endl;
        }
        return true;
    }
    else if(nomeComando =="e" || nomeComando == "d" || nomeComando == "c" || nomeComando == "b") {
        if (!j->estaNoJardim()) {
            cout << "O jardineiro tem de entrar no jardim primeiro." << endl;
            return false;
        }

        if (!j->podeMover()) {
            cout << "O jardineiro esta cansado (max movimentos atingido)." << endl;
            return false;
        }

        int l = j->getLinha();
        int c = j->getColuna();

        // Calcular nova posição
        switch(nomeComando[0]) {
            case 'e': c--; break; // Esquerda
            case 'd': c++; break; // Direita
            case 'c': l--; break; // Cima
            case 'b': l++; break; // Baixo
        }

        // Verificar limites do jardim
        if (l >= 0 && l < jardim->getLinhas() && c >= 0 && c < jardim->getColunas()) {
            j->setPosicao(l, c);
            j->registarMovimento(); // Importante para contar ações
            cout << "Movimento " << nomeComando << " executado." << endl;
            processarEntradaNaPosicao(jardim, j, l, c);
            return true;
        } else {
            cout << "Movimento impossivel (limites do jardim)." << endl;
            return false;
        }
    }



    return false;
}