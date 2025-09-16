#include "CImg.h"
#include <iostream>
#include <string>

using namespace cimg_library;

int main() {
    try {
        // 1. CARREGAR A IMAGEM BASE
        CImg<unsigned char> imagem_modificada("hidrometro_base.bmp");
        std::cout << "Imagem base carregada!" << std::endl;

        // 2. ADICIONAR OS ELEMENTOS (DRAWING)
        const unsigned char cor_texto[] = {0, 0, 0};
        std::string texto_contador = "1   2  3  4   5  6";

        imagem_modificada.draw_text(
            295, 310,                
            texto_contador.c_str(),  
            cor_texto,               
            0,                       
            1.0,                     
            30                       
        );
        
        // 3. SALVAR A IMAGEM
        imagem_modificada.save("hidrometro_final.bmp");
        std::cout << "Imagem final salva como 'hidrometro_final.bmp'." << std::endl;

        // 4. MOSTRAR A IMAGEM EM UMA JANELA
        // Cria um objeto CImgDisplay com a imagem
        CImgDisplay display(imagem_modificada, "Hidrometro Simulador");

        // Loop para manter a janela aberta ate o usuario fechar
        while (!display.is_closed()) {
            display.wait();
        }
    
    } catch (const CImgException& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}