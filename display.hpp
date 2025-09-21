#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string>

#include "CImg.h"

using namespace cimg_library;

class Display {
private:
    std::string valorDisplay;
    int deltaTImagem;
    // Atributo para armazenar a imagem de fundo
    CImg<unsigned char> imagemDeFundo;
    CImgDisplay *janelaDisplay;
    std::string caminhoSaida; // Novo atributo para o caminho da pasta
    CImg<unsigned char> imagemAtual; // Novo atributo para a imagem mais recente

public:
    // CImgDisplay *janelaDisplay;
    // Construtor agora recebe o delta T e o caminho para a imagem de entrada e de saída
    Display(int deltaTImagem, const std::string& caminhoImagem, const std::string& caminhoSaida);
    ~Display();

    // Metodo para exibir o valor numérico
    void exibir(float valor);

    // Metodo para salvar a "imagem" do hidrometro
    void salvarImagem(float contador);
    
    // Metodo para obter o delta T da imagem, que a classe Hidrometro precisa
    int obterDeltaTImagem();

    bool estaFechado(); 
};

#endif // DISPLAY_HPP