#include "interpretador.h"
#include <iostream>
#include <sstream>
#include "Jardim/jardim.h"
#include "Jardim/posicao.h"
#include "Comandos/comandojardim.h"
#include "Comandos/comandojardineiro.h"
#include "Comandos/comandoplantas.h"
#include "Comandos/comandoavanca.h"
#include "Comandos/comandoferramentas.h"
#include "Comandos/comandocolhe.h"

using namespace std;

Interpretador::Interpretador() {
    // Inicializa os comandos disponíveis
    comandos.push_back(new ComandoJardim());
    comandos.push_back(new comandojardineiro("entra"));
    comandos.push_back(new comandojardineiro("sai"));
    comandos.push_back(new comandojardineiro("e"));
    comandos.push_back(new comandojardineiro("d"));
    comandos.push_back(new comandojardineiro("c"));
    comandos.push_back(new comandojardineiro("b"));
    comandos.push_back(new ComandoPlanta("planta"));
    comandos.push_back(new ComandoPlanta("lplantas"));
    comandos.push_back(new Comandoavanca("avanca"));
    comandos.push_back(new ComandoFerramentas("lferr"));
    comandos.push_back(new ComandoFerramentas("larga"));
    comandos.push_back(new ComandoFerramentas("pega"));
    comandos.push_back(new ComandoFerramentas("compra"));
    comandos.push_back(new ComandoColhe());
    // Adicione outros comandos aqui, por exemplo:
    // comandos.push_back(new ComandoEntra());
    // comandos.push_back(new ComandoSai());
    // comandos.push_back(new ComandoMover());
    // comandos.push_back(new ComandoPlanta());
    // comandos.push_back(new ComandoAvanca());
    // comandos.push_back(new ComandoFim());
}

Interpretador::~Interpretador() {
    for (Comando* cmd : comandos) {
        delete cmd;
    }
}

bool Interpretador::processarComando(const std::string& linha, Jardim*& jardim) {
    std::stringstream ss(linha);
    std::string cmdNome;
    ss >> cmdNome;

    // Lógica de validação do Jardim (Req 1)
    bool precisaDeJardim = !(cmdNome == "jardim" || cmdNome == "fim" || cmdNome == "executa");
    if (precisaDeJardim && jardim == nullptr) {
        std::cout << "Erro: Crie primeiro o jardim com 'jardim <l> <c>'" << std::endl;
        return false;
    }

    // Procura o comando
    for (Comando* cmd : comandos) {
        if (cmd->getNome() == cmdNome) {
            //cout << cmd->getNome()<< endl;
            // Encontrou! Chama o 'executar' desse objeto específico.
            // Os argumentos (o resto da stringstream) são passados.
            cout << cmd->getNome() << endl;
            return cmd->executar(jardim, ss);
        }
    }

    std::cout << "Comando invalido: " << cmdNome << std::endl;
    return false;
}

/*bool Interpretador::processarComando(const string& comando, Jardim*& jardim, bool& executa){
    stringstream ss(comando);
    string cmd;
    ss >> cmd;

    bool precisaDeJardim = !(cmd == "jardim" || cmd == "fim");
    if (precisaDeJardim && jardim == nullptr) {
        cout << "Erro: Crie primeiro o jardim com 'jardim <linhas> <colunas>'" << endl;
        return false;
    }

    else if (cmd == "entra") {
        string pos;
        if (ss >> pos) {
            try {
                Posicao p = Posicao::deString(pos);
                if (jardim->entrarJardim(p.getLinha(), p.getColuna())) {
                    cout << "Entrou na posicao " << pos << "." << endl;
                } else {
                    cout << "Nao foi possivel entrar na posicao " << pos << "." << endl;
                }
                return true;
            } catch (const std::exception& e) {
                cout << "Posicao invalida: " << e.what() << endl;
                return false;
            }
        }
        cout << "Parametro de posicao faltando para 'entra'." << endl;
        return false;
    }
    else if (cmd == "sai"){
        // exige que Jardim::sairJardim retorne bool
        if(jardim->sairJardim()){
            cout << "Saiu do jardim." << endl;
        }else{
            cout << "Nao esta no jardim." << endl;
        }
        return true;
    }
    else if(cmd =="e" || cmd == "d" || cmd == "c" || cmd == "b") {
        if (jardim->moverJardineiro(cmd[0])) {
            cout << "Movimento " << cmd << " executado." << endl;
            return true;
        } else {
            cout << "Movimento " << cmd << " invalido." << endl;
            return false;
        }
    }
    else if(cmd == "planta") {
        string pos, tipo;
        if(ss >> pos >> tipo) {
            try {
                Posicao p = Posicao::deString(pos);

                // Verificar se a posição é válida no jardim
                if(!p.ehValida(jardim->getLinhas(), jardim->getColunas())) {
                    cout << "Posicao " << pos << " fora dos limites do jardim." << endl;
                    return false;
                }

                Solo* solo = jardim->getSolo(p.getLinha(), p.getColuna());

                if(!solo->estaVazio()) {
                    cout << "Posicao " << pos << " ja esta ocupada." << endl;
                    return false;
                }

                // Validar tipo de planta
                char tipoChar = tolower(tipo[0]);
                if(tipoChar != 'c' && tipoChar != 'r' && tipoChar != 'e' && tipoChar != 'x') {
                    cout << "Tipo de planta invalido. Use: c (cacto), r (roseira), e (erva), x (exótica)" << endl;
                    return false;
                }

                // PLANTAR - meter a planta no solo!
                solo->setConteudo(tipoChar);

                // Mensagem conforme o tipo
                string nome;
                switch(tipoChar) {
                    case 'c': nome = "cacto"; break;
                    case 'r': nome = "roseira"; break;
                    case 'e': nome = "erva daninha"; break;
                    case 'x': nome = "planta exotica"; break;
                }
                cout << "Plantou " << nome << " na posicao " << pos << endl;
                return true;

            } catch(const exception& e) {
                cout << "Posicao invalida: " << e.what() << endl;
                return false;
            }
        }
        cout << "Parametros em falta. Use: planta <posicao> <tipo>" << endl;
        cout << "Exemplo: planta aa c" << endl;
        cout << "Tipos: c (cacto), r (roseira), e (erva), x (exotica)" << endl;
        return false;
    }
    else if(cmd == "avanca") {
        int n=1;
        ss >> n;// isto vai tentar ler n, se falhar fica com o valor 1
        if(n < 1) {
            cout << "Numero de instantes deve ser positivo." << endl;
            return false;
        }
        cout << "Avancou " << n << " instante(s)." << endl;
        return true;
    }
    else if(cmd == "fim"){
        executa = false;
        cout << "A terminar" << endl;
        return true;
    }

    cout << "Comando invalido: " << comando << endl;
    return false;
}*/


