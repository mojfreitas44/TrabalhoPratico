#include "comandosolo.h"
#include "../Jardim/posicao.h"
#include "../Solo.h"
#include <iostream>

using namespace std;

bool ComandoSolo::executar(Jardim*& jardim, stringstream& parametros) {
    if (nomeComando == "larea") {
        cout << "=== Conteudo da Area ===" << endl;
        bool vazio = true;

        for (int l = 0; l < jardim->getLinhas(); l++) {
            for (int c = 0; c < jardim->getColunas(); c++) {
                Solo* solo = jardim->getSolo(l, c);

                // Só mostra se tiver alguma coisa (Planta ou Ferramenta)
                if (!solo->estaVazio()) {
                    vazio = false;
                    char lChar = (char)('a' + l);
                    char cChar = (char)('a' + c);

                    cout << "[" << lChar << cChar << "] "
                         << "Agua:" << solo->getAgua() << " Nut:" << solo->getNutrientes();

                    if (solo->getPlanta())
                        cout << " | Planta: " << solo->getPlanta()->getTipo();

                    if (solo->getFerramenta())
                        cout << " | Ferr: " << solo->getFerramenta()->getTipo();

                    cout << endl;
                }
            }
        }
        if (vazio) cout << "Jardim vazio." << endl;
        return true;
    }
    else if (nomeComando == "lsolo") {
        string posStr;
        // Tenta ler a posição (ex: "aa")
        if (parametros >> posStr) {
            try {
                Posicao p = Posicao::deString(posStr);

                // Validar limites
                if (p.getLinha() < 0 || p.getLinha() >= jardim->getLinhas() ||
                    p.getColuna() < 0 || p.getColuna() >= jardim->getColunas()) {
                    cout << "Posicao fora do jardim." << endl;
                    return false;
                }

                Solo* solo = jardim->getSolo(p.getLinha(), p.getColuna());

                cout << "--- Solo " << posStr << " ---" << endl;
                cout << "Agua: " << solo->getAgua() << endl;
                cout << "Nutrientes: " << solo->getNutrientes() << endl;

                if (solo->getPlanta())
                    cout << "Planta: " << solo->getPlanta()->getTipo() << endl;
                else
                    cout << "Planta: Nenhuma" << endl;

                if (solo->getFerramenta())
                    cout << "Ferramenta: " << solo->getFerramenta()->getTipo() << endl;

                return true;

            } catch (...) {
                cout << "Posicao invalida." << endl;
                return false;
            }
        }
        cout << "Erro: Falta a posicao. Uso: lsolo <posicao>" << endl;
        return false;
    }

    return false;
}