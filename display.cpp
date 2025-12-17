#include "Display.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>  
#include <iomanip>  

// Construtor que recebe o delta T da imagem
Display::Display(int deltaTImagem, const std::string& caminhoImagem, const std::string& caminhoSaida): deltaTImagem(deltaTImagem), valorDisplay("0.0"), caminhoSaida(caminhoSaida), janelaDisplay(nullptr) {
    imagemDeFundo.load(caminhoImagem.c_str());
    janelaDisplay = new CImgDisplay(imagemDeFundo, "Hidrometro Simulador");

}

Display::~Display() {
    delete janelaDisplay;
}

bool Display::estaFechado() {
    if (janelaDisplay) {
        return janelaDisplay->is_closed();
    }
    return true; // Retorna true se a janela nao existir
}

// Metodo que simula a exibicao do contador em tempo real
void Display::exibir(float valor) {
    if (janelaDisplay && !janelaDisplay->is_closed()) {
        // 1. Obter a parte inteira (metros cubicos)
        int metros_cubicos = static_cast<int>(floor(valor));
        
        // 2. Obter a parte fracionaria e converter para litros
        float parte_fracionaria_decimal = valor - static_cast<float>(metros_cubicos);
        int litros_total = static_cast<int>(round(parte_fracionaria_decimal * 1000.0f));

        // 3. Obter os digitos de centenas e dezenas de litros (apenas 2 digitos)
        int centenas_litros = (litros_total / 100) % 10;
        int dezenas_litros = (litros_total / 10) % 10;

        // 4. Formatar os valores para string
        std::string texto_metros = std::to_string(metros_cubicos);
        
        // Preencher com zeros a esquerda para um total de 4 digitos 
        while (texto_metros.length() < 4) {
            texto_metros = "0" + texto_metros;
        }

        // Converte os dois digitos de litros para string
        std::string texto_litros = std::to_string(centenas_litros) + std::to_string(dezenas_litros);

        // --- Logica de exibicao em janela ---
        CImg<unsigned char> imagemAtualizada = imagemDeFundo;

        const unsigned char cor_preta[] = {0, 0, 0};
        const unsigned char cor_vermelha[] = {255, 0, 0};
        
        int tamanho_fonte = 35;
        int espacamento_pixel = 3;

        int pos_x = 295; // Posicao inicial para os metros cubicos

        // Desenha cada digito dos metros cubicos separadamente
        for (char& caractere : texto_metros) {
            std::string caractere_str(1, caractere);
            imagemAtualizada.draw_text(
                pos_x, 310, caractere_str.c_str(), 
                cor_preta, 0, 1.0, tamanho_fonte
            );
            pos_x += tamanho_fonte + espacamento_pixel;
        }
        
        // Posicao para os digitos de litros 
        pos_x += 3;

        // Desenha os dois digitos de litros
        for (char& caractere : texto_litros) {
            std::string caractere_str(1, caractere);
            imagemAtualizada.draw_text(
                pos_x, 310, caractere_str.c_str(), 
                cor_vermelha, 0, 1.0, tamanho_fonte
            );
            pos_x += tamanho_fonte + espacamento_pixel;
        }

        // Armazena a imagem gerada no atributo privado
        imagemAtual = imagemAtualizada;

        janelaDisplay->display(imagemAtualizada);
    }
}

// Metodo que salva a imagem
void Display::salvarImagem(float contador) {
    // Este metodo agora so precisa salvar a imagem
    if (janelaDisplay) {
        std::string nomeArquivo = this->caminhoSaida + "/hidrometro_" + std::to_string(static_cast<int>(contador)) + ".bmp";
        imagemAtual.save(nomeArquivo.c_str());
        
        std::string nomeArquivoTxt = this->caminhoSaida + "/hidrometro_" + std::to_string(static_cast<int>(contador)) + ".txt";
        std::ofstream arquivoValor(nomeArquivoTxt);
        if (arquivoValor.is_open()) {
            arquivoValor << std::fixed << std::setprecision(3) << contador;
            arquivoValor.close();
        }
    }
}

// Metodo para retornar o delta T
int Display::obterDeltaTImagem() {
    return this->deltaTImagem;
}
