#ifndef HIDROMETRO_HPP
#define HIDROMETRO_HPP

#include "Entrada.hpp"
#include "Saida.hpp"
#include "Display.hpp"

class Hidrometro {
private:
    float contador;
    float vazaoAtual;
    bool simulandoFaltaAgua;

    Entrada& entrada;
    Saida& saida;
    Display& display;

public:
    // Construtor
    Hidrometro(Entrada& entrada, Saida& saida, Display& display);

    // Metodos
    void iniciarSimulacao();
    void atualizarContador();
    void calcularVazao();
    void simularFaltaAgua(bool estado);
};

#endif // HIDROMETRO_HPP