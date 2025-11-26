//
// Created by Rodrigo on 29/10/2025.
//

#include "comandoplantas.h"
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>

using namespace std;

bool ComandoPlanta::executar(Jardim*& jardim, std::stringstream& parametros)  {

    // COMANDO: planta <l><c> <tipo>
    if(nomeComando == "planta") {
        std::string posStr;
        char tipoChar;

        if (!(parametros >> posStr >> tipoChar)) {
            cout << "Parametros invalidos. Uso: planta <posicao> <tipo>" << endl;
            return false;
        }

        try {
            Posicao p = Posicao::deString(posStr);

            // Validar se está dentro dos limites do jardim
            if (p.getLinha() < 0 || p.getLinha() >= jardim->getLinhas() ||
                p.getColuna() < 0 || p.getColuna() >= jardim->getColunas()) {
                cout << "Posicao " << posStr << " fora dos limites do jardim." << endl;
                return false;
            }

            Solo *solo = jardim->getSolo(p.getLinha(), p.getColuna());

            // Verifica se já tem planta ou ferramenta
            if (!solo->estaVazio()) {
                cout << "A posicao " << posStr << " ja esta ocupada." << endl;
                return false;
            }

            Plantas *novaPlanta = nullptr;
            string nome;

            tipoChar = static_cast<char>(tolower(static_cast<unsigned char>(tipoChar)));

            switch (tipoChar) {
                case 'c':
                    novaPlanta = new Cacto();
                    nome = "cacto";
                    break;
                case 'r':
                    novaPlanta = new Roseira();
                    nome = "roseira";
                    break;
                case 'e':
                    novaPlanta = new Erva();
                    nome = "erva daninha";
                    break;
                case 'x': // Falta criar a classe da planta Exótica
                    novaPlanta = new Exotica();
                    nome = "planta exotica";
                    break;
                default:
                    cout << "Tipo de planta invalido. Use: c, r, e." << endl;
                    return false;
            }

            if (novaPlanta != nullptr) {
                solo->setPlanta(novaPlanta);
                // Usa o metodo getTipo() da planta acabada de criar para confirmar
                cout << "Plantou " << nome << " (" << novaPlanta->getTipo() << ") na posicao "
                     << posStr << endl;
                return true;
            }

        } catch (const exception& e) {
            cout << "Posicao invalida: " << e.what() << endl;
            return false;
        }
    }

    // COMANDO: lplantas
    else if(nomeComando == "lplantas") {
        cout << "=== Plantas no Jardim ===" << endl;
        bool encontrouPlantas = false;

        for (int l = 0; l < jardim->getLinhas(); l++) {
            for(int c = 0; c < jardim->getColunas(); c++) {
                Solo* solo = jardim->getSolo(l,c);

                if (solo) {
                    Plantas* planta = solo->getPlanta(); // Obtém a planta (pode ser nullptr)

                    // A CORREÇÃO PRINCIPAL É ESTA:
                    // Verifica se existe REALMENTE uma planta antes de tentar aceder a ela
                    if (planta != nullptr) {
                        encontrouPlantas = true;
                        string nomePlanta;

                        switch(planta->getTipo()) {
                            case 'c': nomePlanta = "Cacto"; break;
                            case 'r': nomePlanta = "Roseira"; break;
                            case 'e': nomePlanta = "Erva Daninha"; break;
                            case 'x': nomePlanta = "Planta Exotica"; break;
                            default: nomePlanta = "Desconhecida"; break;
                        }

                        // Constrói a string da posição (ex: "aa")
                        string posStr;
                        posStr += static_cast<char>('a' + l);
                        posStr += static_cast<char>('a' + c);

                        cout << " -> " << nomePlanta << " [" << planta->getTipo() << "] na posicao " << posStr << endl;

                        // NOTA: Para mostrares os nutrientes e água (requisito do enunciado),
                        // terás de adicionar int getAgua() e int getNutrientes() na classe Plantas.h
                        // cout << "    (Agua: " << planta->getAgua() << " | Nutrientes: " << planta->getNutrientes() << ")" << endl;
                    }
                }
            }
        }

        if(!encontrouPlantas) {
            cout << "Nenhuma planta no jardim." << endl;
        }
        return true;
    }

    return false;
}