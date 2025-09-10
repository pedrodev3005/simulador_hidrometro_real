#include "Configuracao.hpp"
#include <iostream>
#include <fstream>

Configuracao::Configuracao(const std::string& arquivo) : caminhoArquivo(arquivo) {}

void Configuracao::carregarParametros() {
    std::ifstream arquivo(caminhoArquivo);
    
    if (!arquivo.is_open()) {
        throw std::runtime_error("Erro: O arquivo de configuracao nao pode ser aberto.");
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (linha.empty() || linha.front() == '#') {
            continue;
        }

        size_t pos = linha.find('=');
        if (pos != std::string::npos) {
            std::string chave = linha.substr(0, pos);
            std::string valor = linha.substr(pos + 1);

            chave.erase(0, chave.find_first_not_of(" \t\n\r\f\v"));
            valor.erase(0, valor.find_first_not_of(" \t\n\r\f\v"));

            parametros[chave] = valor;
        }
    }
    arquivo.close();
    
    std::cout << "Parametros carregados com sucesso de " << caminhoArquivo << std::endl;
}

std::string Configuracao::obterParametro(const std::string& chave) {
    if (parametros.find(chave) != parametros.end()) {
        return parametros.at(chave);
    }
    throw std::invalid_argument("Erro: Chave de parametro nao encontrada.");
}