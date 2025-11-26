#ifndef TRABALHOPRATICO_JARDIM_H
#define TRABALHOPRATICO_JARDIM_H
#include "posicao.h"
//#include "../Solo.h"
//#include "../Plantas/plantas.h"
#include "../Ferramentas/ferramentas.h"
#include "../jardineiro.h"

class Solo;
class Plantas;
class Jardim{
private:
    int linhas;
    int colunas;
    Solo**area;
    Jardineiro *jardineiro;
    void inicializarFerramentas();
public:
    Jardim(int l, int c);
    ~Jardim();
    void desenhar() const;
    void reporFerramenta();

    Jardineiro* getJardineiro() const { return jardineiro; }
    Solo* getSolo(int linha, int coluna);

    int getLinhas() const { return linhas; }
    int getColunas() const { return colunas; }
};
#endif //TRABALHOPRATICO_JARDIM_H
