//
// Created by Rodrigo on 29/10/2025.
//

#include "comandojardim.h"
#include "../Jardim/jardim.h"
#include <iostream>
#include <sstream>

using namespace std;
ComandoJardim::ComandoJardim(){}

bool ComandoJardim::executar(Jardim*& jardim, stringstream& parametros){
    cout << "entrou no comando jardim" << endl;

    int l,c;
    if(parametros >> l && parametros >> c){
        if(l<1 || l>26 || c<1 || c>26){
            cout << "Dimensoes invalidas. Linhas e colunas devem estar entre 1 e 26." << endl;
            return false;
        }
        if (l * c < 3) {
            cout << "Erro: O jardim e demasiado pequeno para jogar." << endl;
            cout << "A area total (linhas x colunas) deve ser pelo menos 3." << endl;
            return false;
        }
        delete jardim; // eliminar jardim anterior, se existir
        jardim = new Jardim(l,c);
        cout << "Jardim criado com " << l << " linhas e " << c << " colunas." << endl;
        return true;
    }
    cout << "Parametros insuficientes para comando 'jardim' <linhas> <colunas>." << endl;
    return false;
}
