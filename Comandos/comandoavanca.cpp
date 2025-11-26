//
// Created by Rodrigo on 30/10/2025.
//

#include "comandoavanca.h"

#include <sstream>
#include <iostream>
using namespace std;

bool Comandoavanca::executar(Jardim*& jardim, stringstream& parametros) {
    //cout << "DEBUG: Executando comando '" << nomeComando << "'" << endl;

    if (nomeComando == "avanca") {
        int n = 1;
        parametros >> n;

        if (n < 1) {
            cout << "Numero de instantes deve ser positivo." << endl;
            return false;
        }

        // Simular N instantes
        for (int i = 0; i < n; i++) {
            // AQUI ENTRARÁ A SIMULAÇÃO DAS PLANTAS (FUTURO)
            // jardim->simularInstante();
        }

        jardim->getJardineiro()->resetarAcoes();

        cout << "Avancou " << n << " instante(s)." << endl;
        return true;
    }
    return false;
}

