#include "Hidrometro.hpp"
#include "display.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm> 

Hidrometro::Hidrometro(Entrada& entrada, Saida& saida, Display& display)
    : entrada(entrada),
      saida(saida),
      display(display),
      contador(0.0f),
      vazaoAtual(0.0f),
      simulandoFaltaAgua(false) 
{
    std::cout << "Hidrometro inicializado com sucesso." << std::endl;
}

void Hidrometro::calcularVazao() {
    float nivelEntrada = entrada.obterNivel();
    float bitolaEntrada = entrada.obterBitola();
    float bitolaSaida = saida.obter_bitola_saida();

    // A vazao eh limitada pela menor bitola
    float menorBitola = std::min(bitolaEntrada, bitolaSaida);

    // Usa uma formula simplificada para calcular a vazao
    if (simulandoFaltaAgua) {
        this->vazaoAtual = nivelEntrada * 0.05f; // 5% do valor original, por exemplo
    } else {
        this->vazaoAtual = nivelEntrada * (menorBitola * menorBitola) *  0.0000001f; 
    }
}

void Hidrometro::atualizarContador() {
    this->contador += this->vazaoAtual * 0.050f; // Incrementa o contador em m3
}

void Hidrometro::simularFaltaAgua(bool estado) {
    this->simulandoFaltaAgua = estado;
    if (estado) {
        std::cout << "Simulando falta de agua..." << std::endl;
    } else {
        std::cout << "Fluxo de agua normal restabelecido." << std::endl;
    }
}

void Hidrometro::iniciarSimulacao() {
    std::cout << "Iniciando simulacao ininterrupta..." << std::endl;
    display.exibir(0.0);

    // Obtem o delta T da imagem da classe Display
    int deltaTImagem = display.obterDeltaTImagem(); 

    // Usa o chrono para controlar o tempo e gerar as imagens
    auto ultimaAtualizacao = std::chrono::steady_clock::now();

    while (!display.estaFechado() && this->contador <=9999.0f) {
        calcularVazao();
        atualizarContador();

        auto agora = std::chrono::steady_clock::now();
        auto duracao = std::chrono::duration_cast<std::chrono::milliseconds>(agora - ultimaAtualizacao).count();

        // Checa se ja passou o tempo para gerar a imagem
        if (duracao >= deltaTImagem) {
            display.exibir(this->contador);
            std::cout << "Gerando imagem do hidrometro..." << std::endl;
            display.salvarImagem(this->contador, this->vazaoAtual);
            ultimaAtualizacao = agora;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Simula o tempo
    }
}