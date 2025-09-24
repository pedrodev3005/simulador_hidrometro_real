#ifndef CONFIGURACAO_HPP
#define CONFIGURACAO_HPP

#include <string>
#include <map>
#include <stdexcept>

class Configuracao {
protected:
    std::string caminhoArquivo;
    std::map<std::string, std::string> parametros;

public:
    // Construtor
    Configuracao(const std::string& arquivo);

    // Metodo para carregar os parametros do arquivo
    void carregarParametros();

    // Metodo para obter um parametro especifico
    std::string obterParametro(const std::string& chave);
};

#endif // CONFIGURACAO_HPP