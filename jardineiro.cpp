#include "jardineiro.h"
#include "Ferramentas/ferramentas.h"
#include "Settings.h"
Jardineiro::Jardineiro()
        : dentroDoJardim(false), linha(0), coluna(0),
          ferramentaNaMao(nullptr), movimentosFeitos(0), plantasPlantadas(0),plantasColhidas(0) {}

Jardineiro::~Jardineiro() {
    // Limpar a memória das ferramentas na mochila
    for (Ferramentas* f : mochila) {
        delete f;
    }
    mochila.clear();
}

void Jardineiro::entrar(int l, int c) {
    dentroDoJardim = true;
    linha = l;
    coluna = c;
}

void Jardineiro::sair() {
    dentroDoJardim = false;
}

void Jardineiro::setPosicao(int l, int c) {
    linha = l;
    coluna = c;
}

// --- Gestão de Ferramentas ---

void Jardineiro::apanharFerramenta(Ferramentas* f) {
    if (f != nullptr) {
        mochila.push_back(f);
    }
}

bool Jardineiro::equiparFerramenta(int id) {
    // Procura na mochila
    for (Ferramentas* f : mochila) {
        if (f->getID() == id) {
            ferramentaNaMao = f; // Coloca na mão
            return true;
        }
    }
    return false; // Não encontrou
}

void Jardineiro::largarFerramenta() {
    ferramentaNaMao = nullptr; // Apenas tira da mão, continua na mochila (ou pointer fica solto se lógica for diferente)
}

// --- Gestão de Ações ---

void Jardineiro::resetarAcoes() {
    movimentosFeitos = 0;
    plantasPlantadas = 0;
    plantasColhidas = 0;
}

bool Jardineiro::podeMover() const {
    // Exemplo: limite de 10 movimentos (Settings::Jardineiro::max_movimentos)
    return movimentosFeitos < 10;
}

bool Jardineiro::podeColher() const {
    return plantasColhidas < Settings::Jardineiro::max_colheitas;
}

void Jardineiro::registarColheita() {
    plantasColhidas++;
}

void Jardineiro::registarMovimento() {
    movimentosFeitos++;
}