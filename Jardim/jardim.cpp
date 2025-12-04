#include <iostream>
#include "jardim.h"
#include "../Solo.h"
#include "../Plantas/plantas.h"
#include "../Ferramentas/ferramentas.h"
#include "../Ferramentas/regador.h"
#include "../Ferramentas/adubo.h"
#include "../Ferramentas/tesoura.h"
#include "../Ferramentas/ferramentaZ.h"

using namespace std;

Jardim::Jardim(int l, int c) : linhas(l), colunas(c){
    jardineiro = new Jardineiro();

    area = new Solo*[linhas];
    for(int i = 0; i < linhas; i++) {
        area[i] = new Solo[colunas];
    }
    inicializarFerramentas();
}

Jardim::~Jardim() {
    for(int i = 0; i < linhas; i++) {
        delete[] area[i];
    }
    delete[] area;
    delete jardineiro;
}

void Jardim::desenhar() const {
    cout << "   ";
    for(int c = 0; c < colunas; c++) {
        cout << " " << static_cast<char>('A' + c);
    }
    cout << endl;

    cout << "  +";
    for(int c = 0; c < colunas; c++) {
        cout << "--";
    }
    cout << "-+" << endl;

    for(int l = 0; l < linhas; l++) {
        cout << static_cast<char>('A' + l) << " |";

        for(int c = 0; c < colunas; c++) {
            Solo* solo =  &area[l][c];

            if (jardineiro->estaNoJardim() &&
                jardineiro->getLinha() == l &&
                jardineiro->getColuna() == c) {
                cout << " *";
            } else if(solo->getPlanta() != nullptr) {
                cout << " " << solo->getPlanta()->getTipo();
            } else if (solo->getFerramenta() != nullptr) {
                cout << " " << solo->getFerramenta()->getTipo();
            } else {
                cout << "  ";
            }
        }
        cout << " |" << endl;
    }

    cout << "  +";
    for(int c = 0; c < colunas; c++) {
        cout << "--";
    }
    cout << "-+" << endl;
}

void Jardim::reporFerramenta() {
    int l, c;
    Solo* soloAlvo;
    // Antes: while (!soloAlvo->estaVazio() || ...) -> Bloqueava se houvesse plantas
    // Agora: while (soloAlvo->getFerramenta() != nullptr) -> Só bloqueia se já houver ferramenta
    int tentativas = 0;
    do {
        l = rand() % linhas;
        c = rand() % colunas;
        soloAlvo = getSolo(l, c);
        tentativas++;
        // Proteção extra: se tentar 1000 vezes e não conseguir (jardim cheio de ferramentas), desiste
        if (tentativas > 1000) return;

    } while (soloAlvo->getFerramenta() != nullptr);

    int tipo = rand() % 4;
    Ferramentas *novaFerramenta = nullptr;

    switch (tipo) {
        case 0: novaFerramenta = new Regador(); break;
        case 1: novaFerramenta = new Adubo(); break;
        case 2: novaFerramenta = new Tesoura(); break;
        case 3: novaFerramenta = new FerramentaZ(); break;
    }

    if (novaFerramenta != nullptr) {
        soloAlvo->setFerramenta(novaFerramenta);
    }
}

void Jardim::inicializarFerramentas() {
    int tipoFerramentas = 4;
    int areaTotal = linhas * colunas;
    int numeroFerramentas = (areaTotal < 3) ? areaTotal : 3;

    for (int i = 0; i < numeroFerramentas; i++) {
        int c, l;
        Solo* soloAlvo;

        // CORREÇÃO AQUI TAMBÉM:
        do {
            l = rand() % linhas;
            c = rand() % colunas;
            soloAlvo = getSolo(l,c);
        } while (soloAlvo->getFerramenta() != nullptr); // Permite spawnar em cima de plantas (embora no inicio nao existam)

        int tipo = rand() % tipoFerramentas;
        Ferramentas *novaFerramenta = nullptr;
        switch (tipo) {
            case 0: novaFerramenta = new Regador(); break;
            case 1: novaFerramenta = new Adubo(); break;
            case 2: novaFerramenta = new Tesoura(); break;
            case 3: novaFerramenta = new FerramentaZ(); break;
        }
        if(novaFerramenta != nullptr) {
            soloAlvo->setFerramenta(novaFerramenta);
        }
    }
}

void Jardim::simularInstante() {
    for (int l = 0; l < linhas; l++) {
        for (int c = 0; c < colunas; c++) {
            Solo* solo = getSolo(l, c);

            // 1. Plantas agem
            if (solo->getPlanta() != nullptr) {
                solo->getPlanta()->simular(*this, l, c);
            }

            // 2. Ferramentas agem (se o jardineiro estiver lá)
            if (jardineiro->estaNoJardim() &&
                jardineiro->getLinha() == l &&
                jardineiro->getColuna() == c) {

                Ferramentas* fer = jardineiro->getFerramentaNaMao();
                if (fer != nullptr) {
                    fer->simular(solo);
                }
            }
        }
    }

    // Verificar fim de vida da ferramenta
    if (jardineiro->estaNoJardim()) {
        jardineiro->verificarFerramentaNaMao();
    }
}

Solo* Jardim::getSolo(int linha, int coluna) {
    if(linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas)
        return &area[linha][coluna];
    return nullptr;
}