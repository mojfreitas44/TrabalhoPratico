#include <iostream>
#include "jardim.h"
#include "../Solo.h"       // Include necessário para .cpp
#include "../Plantas/plantas.h" // Include necessário para .cpp
#include "../Ferramentas/ferramentas.h" // Include necessário para .cpp
#include "../Ferramentas/regador.h"
#include "../Ferramentas/adubo.h"
#include "../Ferramentas/tesoura.h"
#include "../Ferramentas/gadanha.h"


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

    // 1. RÉGUA SUPERIOR (imprime tudo numa linha, acaba com endl)
    cout << "   ";
    for(int c = 0; c < colunas; c++) {
        cout << " " << static_cast<char>('A' + c);
    }
    cout << endl; // <-- SÓ 1 endl no fim

    // 2. LINHA SEPARADORA SUPERIOR
    cout << "  +";
    for(int c = 0; c < colunas; c++) {
        cout << "--";
    }
    cout << "-+" << endl; // <-- SÓ 1 endl no fim

    // 3. CONTEÚDO DO JARDIM (O loop principal)
    for(int l = 0; l < linhas; l++) {

        // Imprime a régua da linha (ex: "A |")
        cout << static_cast<char>('A' + l) << " |";

        // Loop das colunas: imprime TODOS os solos dessa linha
        for(int c = 0; c < colunas; c++) {

            Solo* solo =  &area[l][c];

            if (jardineiro->estaNoJardim() &&
                jardineiro->getLinha() == l &&
                jardineiro->getColuna() == c) {
                cout << " *";
            } else if(solo->getPlanta() != nullptr) {
                cout << " " << solo->getPlanta()->getTipo();  // 2. Planta
            } else if (solo->getFerramenta() != nullptr) {
                cout << " " << solo->getFerramenta()->getTipo(); // 3. Ferramenta
            } else {
                cout << "  ";  // 4. Vazio
            }
            // NENHUM endl aqui dentro
        }

        // Imprime a borda direita e SÓ AGORA salta a linha
        cout << " |" << endl;
    }

    // 4. LINHA SEPARADORA INFERIOR
    cout << "  +";
    for(int c = 0; c < colunas; c++) {
        cout << "--";
    }
    cout << "-+" << endl; // <-- SÓ 1 endl no fim
}

void Jardim::reporFerramenta() {
    int l, c;
    Solo* soloAlvo;

    // Procura uma posição vazia aleatória
    // Nota: Num jardim muito cheio isto pode demorar, mas para já serve
    do {
        l = rand() % linhas;
        c = rand() % colunas;
        soloAlvo = getSolo(l, c);
    } while (!soloAlvo->estaVazio() || soloAlvo->getFerramenta() != nullptr);

    int tipo = rand() % 4; // 0 a 3
    Ferramentas *novaFerramenta = nullptr;

    switch (tipo) {
        case 0: novaFerramenta = new Regador(); break;
        case 1: novaFerramenta = new Adubo(); break;
        case 2: novaFerramenta = new Tesoura(); break;
        case 3: novaFerramenta = new Gadanha(); break;
    }

    if (novaFerramenta != nullptr) {
        soloAlvo->setFerramenta(novaFerramenta);
        // cout << "DEBUG: Nova ferramenta apareceu em " << l << "," << c << endl;
    }
}

void Jardim::inicializarFerramentas() {
    int tipoFerramentas = 4;
    int areaTotal = linhas * colunas;
    int numeroFerramentas = (areaTotal < 3) ? areaTotal : 3;

    for (int i = 0; i < 3; i++) {
        int c, l;
        Solo* soloAlvo;
        do {
            l = rand() % linhas;
            c = rand() % colunas;
            soloAlvo = getSolo(l,c);
        } while (!soloAlvo->estaVazio() || soloAlvo->getFerramenta() != nullptr);

        int tipo = rand() % tipoFerramentas;
        Ferramentas *novaFerramenta = nullptr;
        switch (tipo) {
            case 0: novaFerramenta = new Regador(); break;
            case 1: novaFerramenta = new Adubo(); break;
            case 2: novaFerramenta = new Tesoura(); break;
            case 3: novaFerramenta = new Gadanha(); break;
        }
        if(novaFerramenta != nullptr) {
            soloAlvo->setFerramenta(novaFerramenta);
        }
    }
}

Solo* Jardim::getSolo(int linha, int coluna) {
    if(linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas)
        return &area[linha][coluna];
    return nullptr;
}



