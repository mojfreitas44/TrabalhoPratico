#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Jardim/jardim.h"
#include "Interpretador.h"
#include "Settings.h"

using namespace std;

// Função para desenhar o jardim (versão básica)


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    Jardim* jardim = nullptr;
    bool executando = true;
    Interpretador interpretador;
    cout << "=== Simulador de Jardim ===" << endl;
    cout << "Comandos: jardim, entra, sai, e/d/c/b, planta, lplantas, lplanta, avanca, lferr, lsolo, larea, larga, pega, compra, fim" << endl;
    bool aExecutar = true;
    while(aExecutar) {
        cout << "\n> ";
        string comando;
        getline(cin, comando);

        if(comando.empty()) continue;
        if(comando == "fim"){
            aExecutar = false;
            cout << "A terminar" << endl;
            break;
        }
        // Processar comando
        if(!interpretador.processarComando(comando, jardim)) {
            cout << "Erro no comando!" << endl;
        }

        // Redesenhar jardim se existir
        if(jardim != nullptr) {
            jardim->desenhar();
        }
        cout << "Comandos: jardim, entra, sai, e/d/c/b, planta, lplantas, lplanta, avanca, lferr, lsolo, larea, larga, pega, compra, fim" << endl;
    }
    delete jardim;
    return 0;
}
