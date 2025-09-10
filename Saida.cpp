#include "saida.hpp"

Saida::Saida(float bitola) : tamanho_bitola_saida(bitola) {}

float Saida::obter_bitola_saida(){
  return this->tamanho_bitola_saida;
}