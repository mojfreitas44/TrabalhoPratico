//
// Created by Rodrigo on 17/11/2025.
//

#ifndef TRABALHOPRATICO_JARDINEIRO_H
#define TRABALHOPRATICO_JARDINEIRO_H

#include <vector>

class Ferramentas;

class Jardineiro {
private:
    bool dentroDoJardim;
    int linha;
    int coluna;
    Ferramentas* ferramentaNaMao;
    int movimentosFeitos;
    int plantasPlantadas;
    std::vector <Ferramentas*> mochila;
    int plantasColhidas;

public:
    Jardineiro();
    ~Jardineiro();

    //estado jardineiro
    bool estaNoJardim() const {return dentroDoJardim;}
    void entrar(int l, int c);
    void sair();
    void setPosicao(int l, int c);
    int getLinha() const {return linha;}
    int getColuna() const {return coluna;}

    //Gestao ferramentas
    void apanharFerramenta(Ferramentas* f);
    bool equiparFerramenta(int id);
    void largarFerramenta();
    Ferramentas* getFerramentaNaMao() const {return ferramentaNaMao;}

    const std::vector<Ferramentas*>& getMochila () const {return mochila;}

    //gestao turnos
    void resetarAcoes();
    bool podeMover() const;
    void registarMovimento();

    bool podeColher() const;
    void registarColheita();

};


#endif //TRABALHOPRATICO_JARDINEIRO_H
