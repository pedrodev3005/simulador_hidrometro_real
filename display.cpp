#include "Display.hpp"
#include <iostream>
#include <string>
#include <cmath>

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
        
        // NOVO: Preencher com zeros a esquerda para um total de 4 digitos 
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

        // NOVO: Desenha cada digito dos metros cubicos separadamente
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

        // NOVO: Desenha os dois digitos de litros
        for (char& caractere : texto_litros) {
            std::string caractere_str(1, caractere);
            imagemAtualizada.draw_text(
                pos_x, 310, caractere_str.c_str(), 
                cor_vermelha, 0, 1.0, tamanho_fonte
            );
            pos_x += tamanho_fonte + espacamento_pixel;
        }

        janelaDisplay->display(imagemAtualizada);

        std::cout << "Mostrador: " << texto_metros << "." << texto_litros << " m3" << std::endl;
    }
}
// Metodo que simula a geracao da imagem
void Display::gerarImagem(float contador, float vazao) {
    // 1. Obter a parte inteira (metros cubicos)
    int metros_cubicos = static_cast<int>(round(contador));
    
    // 2. Obter a parte fracionaria e converter para litros
    float parte_fracionaria_decimal = contador - static_cast<float>(metros_cubicos);
    int litros_total = static_cast<int>(round(parte_fracionaria_decimal * 1000.0f));

    // 3. Obter os digitos de centenas, dezenas e unidades de litros
    int centenas_litros = (litros_total / 100) % 10;
    int dezenas_litros = (litros_total / 10) % 10;
    int unidades_litros = litros_total % 10;

    // 4. Converte os valores para string
    std::string texto_metros = std::to_string(metros_cubicos);
    std::string texto_litros = std::to_string(centenas_litros) + std::to_string(dezenas_litros) + std::to_string(unidades_litros);

    // --- Logica de geracao de imagem ---
    // Cria uma copia da imagem de fundo para desenhar
    CImg<unsigned char> imagemParaSalvar = imagemDeFundo;

    // Define as cores
    const unsigned char cor_preta[] = {0, 0, 0};
    const unsigned char cor_vermelha[] = {255, 0, 0};
    
    // Define o tamanho da fonte (ajuste conforme a sua imagem)
    int tamanho_fonte_metros = 35;
    int tamanho_fonte_litros = 35;

    // Desenha os metros cubicos (digitos pretos)
    // Ajuste as coordenadas X e Y para o seu hidrometro
    imagemParaSalvar.draw_text(
        295, 310, texto_metros.c_str(), 
        cor_preta, 0, 1.0, tamanho_fonte_metros
    );
    
    // Desenha os litros (digitos vermelhos)
    // Ajuste as coordenadas X e Y para o seu hidrometro
    imagemParaSalvar.draw_text(
        580, 310, texto_litros.c_str(), 
        cor_vermelha, 0, 1.0, tamanho_fonte_litros
    );

    // 5. Salva a imagem em um arquivo
    std::string nomeArquivo = this->caminhoSaida + "/hidrometro_" + std::to_string(static_cast<int>(contador)) + ".bmp";
    imagemParaSalvar.save(nomeArquivo.c_str());

    std::cout << "IMAGEM GERADA: " << nomeArquivo << std::endl;
}
// Metodo para retornar o delta T
int Display::obterDeltaTImagem() {
    return this->deltaTImagem;
}