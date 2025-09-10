#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>

class Display {
private:

    std::string valorDisplay;
    int deltaTImagem;

public:
    // Construtor
    Display(int deltaTImagem);

    // Metodo para exibir o valor numérico
    void exibir(float valor);

    // Metodo para gerar a "imagem" do hidrometro
    void gerarImagem(float contador, float vazao);
    
    // Metodo para obter o delta T da imagem, que a classe Hidrometro precisa
    int obterDeltaTImagem();
};

#endif // DISPLAY_HPP