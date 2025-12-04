#include "erva.h"
#include "../Jardim/jardim.h"
#include "../Solo.h"
#include "../Settings.h"
#include "../Jardim/posicao.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

Erva::Erva() : idade(0), contadorReproducao(0) {
    agua = Settings::ErvaDaninha::inicial_agua;
    nutrientes = Settings::ErvaDaninha::inicial_nutrientes;
    simbolo = 'e';
}

void Erva::simular(Jardim& jardim, int l, int c) {
    Solo* solo = jardim.getSolo(l, c);

    // --- 1. ENVELHECIMENTO ---
    idade++;
    contadorReproducao++;

    // --- 2. ABSORÇÃO ---
    if (solo->getAgua() > 0) {
        solo->retirarAgua(Settings::ErvaDaninha::absorcao_agua);
        this->agua += Settings::ErvaDaninha::absorcao_agua;
    }

    if (solo->getNutrientes() > 0) {
        solo->retirarNutrientes(Settings::ErvaDaninha::absorcao_nutrientes);
        this->nutrientes += Settings::ErvaDaninha::absorcao_nutrientes;
    }

    // --- 3. MORTE (Velhice) ---
    if (idade >= Settings::ErvaDaninha::morre_instantes) {
        char L = (char)('a' + l);
        char C = (char)('a' + c);
        cout << "Erva Daninha morreu de velhice em " << L << C << "." << endl;

        solo->setPlanta(nullptr);
        return;
    }

    // --- 4. REPRODUÇÃO ---
    if (this->nutrientes > Settings::ErvaDaninha::multiplica_nutrientes_maior &&
        contadorReproducao >= Settings::ErvaDaninha::multiplica_instantes) {

        vector<Posicao> vizinhosAlvo;

        for (int dl = -1; dl <= 1; dl++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dl == 0 && dc == 0) continue;

                Solo* viz = jardim.getSolo(l + dl, c + dc);
                if (viz != nullptr) {
                    Plantas* plantaVizinha = viz->getPlanta();

                    if (plantaVizinha == nullptr) {
                        vizinhosAlvo.push_back(Posicao(l + dl, c + dc));
                    }
                    else if (plantaVizinha->getTipo() != 'e') { // Se for 'e', ignora.
                        vizinhosAlvo.push_back(Posicao(l + dl, c + dc));
                    }
                }
            }
        }

        if (!vizinhosAlvo.empty()) {
            // Escolhe uma vítima aleatória da lista filtrada
            int idx = rand() % vizinhosAlvo.size();
            Posicao p = vizinhosAlvo[idx];
            Solo* soloAlvo = jardim.getSolo(p.getLinha(), p.getColuna());

            // Se houver lá uma planta (que já sabemos que não é Erva), avisa
            if (soloAlvo->getPlanta() != nullptr) {
                cout << "A Erva Daninha invadiu e matou a planta ("
                     << soloAlvo->getPlanta()->getTipo() << ") em "
                     << (char)('a'+p.getLinha()) << (char)('a'+p.getColuna()) << "!" << endl;
            }else{
                cout << "A Erva Daninha se espalhou para "
                     << (char)('a'+p.getLinha()) << (char)('a'+p.getColuna()) << "." << endl;
            }

            // Planta a nova Erva
            soloAlvo->setPlanta(new Erva());

            contadorReproducao = 0;
        }
    }
}