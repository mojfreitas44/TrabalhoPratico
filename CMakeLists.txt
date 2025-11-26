cmake_minimum_required(VERSION 3.29)
project(TrabalhoPratico)

set(CMAKE_CXX_STANDARD 20)

add_executable(TrabalhoPratico main.cpp
interpretador.cpp
Jardim/jardim.cpp
        Jardim/posicao.cpp
        Solo.cpp
        Comandos/comando.cpp
        Comandos/comandojardim.cpp
        Plantas/plantas.cpp
        Plantas/cacto.cpp
        Plantas/roseira.cpp
        Plantas/erva.cpp
        Comandos/comandoplantas.cpp
        Comandos/comandojardineiro.cpp
        Comandos/comandoavanca.cpp
        Comandos/comandoplantas.cpp
        Ferramentas/ferramentas.cpp
        Ferramentas/regador.cpp
        Ferramentas/tesoura.cpp
        Ferramentas/adubo.cpp
        Ferramentas/gadanha.cpp
        Ferramentas/regador.h
        Comandos/comandoferramentas.cpp
        jardineiro.cpp
        Plantas/Exotica.cpp
        Comandos/comandocolhe.cpp

)
