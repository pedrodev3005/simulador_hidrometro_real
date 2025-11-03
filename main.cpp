#include <iostream>
#include <string>
#include <stdexcept>
#include <thread> 
#include <vector>

//cabecalhos de todas as classes
#include "Configuracao.hpp"
#include "Entrada.hpp"
#include "Saida.hpp"
#include "Display.hpp"
#include "Hidrometro.hpp"
#include <filesystem> 
#include <sstream>

// Funcao auxiliar para converter string para float de forma segura
float stringToFloat(const std::string& str) {
    try {
        return std::stof(str);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro de conversao de string para float.");
    }
}

void rodarSimulador(int idSimulador, const std::string& arquivoConfig) {
    try {
        std::cout << "--- Simulador #" << idSimulador << " | Iniciando configuracao..." << std::endl;
        
        Configuracao config(arquivoConfig);
        config.carregarParametros();

        float nivelEntrada = stringToFloat(config.obterParametro("nivel_entrada"));
        float bitolaEntrada = stringToFloat(config.obterParametro("bitola_entrada"));
        float bitolaSaida = stringToFloat(config.obterParametro("bitola_saida"));
        int deltaTImagem = std::stoi(config.obterParametro("delta_t_imagem"));
        std::string caminhoImagemFundo = config.obterParametro("caminho_imagem_fundo");
        
        std::string prefixoCaminhoSaida = config.obterParametro("caminho_saida_imagens");
        std::string caminhoSaidaUnico = prefixoCaminhoSaida + "_" + std::to_string(idSimulador);
        
        if (!std::filesystem::exists(caminhoSaidaUnico)) {
            std::cout << "Simulador #" << idSimulador << " | Criando pasta de saida: " << caminhoSaidaUnico << std::endl;
            std::filesystem::create_directory(caminhoSaidaUnico);
        }

        Entrada entrada;
        entrada.definirNivel(nivelEntrada);
        entrada.definirBitola(bitolaEntrada);
        
        Saida saida(bitolaSaida);
        
        Display display(deltaTImagem, caminhoImagemFundo, caminhoSaidaUnico);
        
        Hidrometro hidrometro(entrada, saida, display);
        
        std::cout << "--- Simulador #" << idSimulador << " | Dependencias criadas. Iniciando simulacao." << std::endl;

        hidrometro.iniciarSimulacao();
        
        std::cout << "--- Simulador #" << idSimulador << " | Simulacao encerrada." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Erro fatal no Simulador #" << idSimulador << ": " << e.what() << std::endl;
    }
}
int main() {
    
    const int NUM_SIMULADORES = 5;
    std::vector<std::thread> threadsSimuladores;
    
    std::cout << "\nIniciando simulacao multithread para \n" << NUM_SIMULADORES << " hidrometros." << std::endl;

    for (int i = 1; i <= NUM_SIMULADORES; ++i) {
        threadsSimuladores.emplace_back(rodarSimulador, i, "config.txt");
    }

    for (std::thread& t : threadsSimuladores) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "\nTodas as simulacoes foram concluidas.\n" << std::endl;

    return 0;
}