#include "comandocolhe.h"
#include "../Jardim/posicao.h"
#include "../Solo.h"
#include "../Settings.h"
#include <iostream>

using namespace std;

bool ComandoColhe::executar(Jardim*& jardim, std::stringstream& parametros) {
    string posStr;
    if (parametros >> posStr) {
        try {
            Posicao p = Posicao::deString(posStr);

            // 1. Validar limites
            if (p.getLinha() < 0 || p.getLinha() >= jardim->getLinhas() ||
                p.getColuna() < 0 || p.getColuna() >= jardim->getColunas()) {
                cout << "Posicao fora do jardim." << endl;
                return false;
                }

            // 2. Validar limite de ações do jardineiro
            Jardineiro* j = jardim->getJardineiro();
            if (!j->podeColher()) {
                cout << "O jardineiro ja atingiu o limite de colheitas por turno ("
                     << Settings::Jardineiro::max_colheitas << ")." << endl;
                cout << "Use 'avanca' para passar ao proximo turno." << endl;
                return false;
            }

            // 3. Validar existência de planta
            Solo* solo = jardim->getSolo(p.getLinha(), p.getColuna());
            if (solo->getPlanta() == nullptr) {
                cout << "Nao existe nenhuma planta na posicao " << posStr << " para colher." << endl;
                return false;
            }

            // 4. Executar Colheita
            char tipoPlanta = solo->getPlanta()->getTipo();

            // Remove a planta (o setPlanta faz delete da antiga se passarmos nullptr)
            solo->setPlanta(nullptr);

            j->registarColheita();

            cout << "Planta '" << tipoPlanta << "' colhida em " << posStr << "." << endl;
            return true;

        } catch (const exception& e) {
            cout << "Posicao invalida." << endl;
            return false;
        }
    }
    cout << "Sintaxe: colhe <posicao>" << endl;
    return false;
}