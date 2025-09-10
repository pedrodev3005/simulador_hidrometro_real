#include "Display.hpp"
#include <iostream>

// Construtor que recebe o delta T da imagem
Display::Display(int deltaTImagem) : deltaTImagem(deltaTImagem), valorDisplay("0.0") {}

// Metodo que simula a exibicao do contador em tempo real
void Display::exibir(float valor) {
    // Para simplificar por enquanto, vamos apenas imprimir no console
    this->valorDisplay = std::to_string(valor);
    std::cout << "Display: " << this->valorDisplay << std::endl;
}

// Metodo que simula a geracao da imagem
void Display::gerarImagem(float contador, float vazao) {
    // simula a criacao de uma imagem com os dados atuais
    std::cout << "IMAGEM GERADA - Hidrometro: " << contador << " | Vazao: " << vazao << std::endl;
}

// Metodo para retornar o delta T
int Display::obterDeltaTImagem() {
    return this->deltaTImagem;
}