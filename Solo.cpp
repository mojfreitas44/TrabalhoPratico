#include "Solo.h"
#include <cstdlib>  // para rand()
#include <ctime>    // para time()
#include "settings.h"

Solo::Solo() : agua(0), nutrientes(0), planta(nullptr), ferramenta(nullptr) {
    iniciarAleatorio();
}

Solo::~Solo(){
        delete planta;
        delete ferramenta;
}

void Solo::setPlanta(Plantas *p) {
    if(planta != nullptr) {
        delete planta;
    }
    planta = p;
}
void Solo::setFerramenta(Ferramentas *f) {
    if(ferramenta != nullptr) {
        delete ferramenta;
    }
    ferramenta = f;
}

void Solo::iniciarAleatorio() {
    static bool plantado = false;
    if (!plantado) {
        srand(static_cast<unsigned>(time(nullptr)));
        plantado = true;
    }
    // INICIAR ALEATORIAMENTE OS VALORES DE AGUA E NUTRIENTES
    int range_agua = Settings::Jardim::agua_max - Settings::Jardim::agua_min;
    agua = Settings::Jardim::agua_min + (rand() % (range_agua + 1));

    int range_nutrientes = Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min;
    nutrientes = Settings::Jardim::nutrientes_min + (rand() % (range_nutrientes + 1));

}

bool Solo::estaVazio() const {
    return planta == nullptr && ferramenta == nullptr;
}

Plantas * Solo::getPlanta() const {
    return planta;
}

Ferramentas * Solo::getFerramenta() const {
    return ferramenta;
}
Ferramentas* Solo::retirarFerramenta() {
    Ferramentas* temp = ferramenta;
    ferramenta = nullptr; // Desliga a ferramenta do solo sem a apagar
    return temp;
}
