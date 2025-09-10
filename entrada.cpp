#include "Entrada.hpp"

Entrada::Entrada() : NivelEntradaAgua(0.0f) {}

void Entrada::definirNivel(float nivel){
  if (nivel >= 0.0f)
  {
    this->NivelEntradaAgua = nivel;
  }
  
}

float Entrada::obterNivel(){
  return this->NivelEntradaAgua;
}

void Entrada::definirBitola(float bitola){
  if (bitola >= 0.0f)
  {
    this->Largurabitola = bitola;
  }
  
}

float Entrada::obterBitola(){
  return this->Largurabitola;
}