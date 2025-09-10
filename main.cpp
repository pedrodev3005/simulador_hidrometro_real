#include <iostream>
#include <string>
#include <stdexcept>

// Inclua os cabecalhos de todas as classes
#include "Configuracao.hpp"
#include "Entrada.hpp"
#include "Saida.hpp"
#include "Display.hpp"
#include "Hidrometro.hpp"

// Funcao auxiliar para converter string para float de forma segura
float stringToFloat(const std::string& str) {
    try {
        return std::stof(str);
    } catch (const std::exception& e) {
        throw std::runtime_error("Erro de conversao de string para float.");
    }
}

int main() {
    try {
        // 1. Carregar a configuracao
        Configuracao config("config.txt");
        config.carregarParametros();

        // 2. Criar e configurar as dependencias
        float nivelEntrada = stringToFloat(config.obterParametro("nivel_entrada"));
        float bitolaEntrada = stringToFloat(config.obterParametro("bitola_entrada"));
        float bitolaSaida = stringToFloat(config.obterParametro("bitola_saida"));
        int deltaTImagem = std::stoi(config.obterParametro("delta_t_imagem"));
        
        Entrada entrada;
        entrada.definirNivel(nivelEntrada);
        entrada.definirBitola(bitolaEntrada);
        
        Saida saida(bitolaSaida);
        
        // Agora, a classe Display eh criada com o parametro deltaTImagem
        Display display(deltaTImagem);

        // 3. Injetar as dependencias no Hidrometro
        Hidrometro hidrometro(entrada, saida, display);
        
        // 4. Iniciar a simulacao
        hidrometro.iniciarSimulacao();

    } catch (const std::exception& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}