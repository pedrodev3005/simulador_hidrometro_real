#ifndef ENTRADA_HPP
#define ENTRADA_HPP

class Entrada
{
protected:
  float NivelEntradaAgua;
  float Largurabitola;

public:

  Entrada();

  void definirNivel(float nivel);
  float obterNivel();

  void definirBitola(float bitola);
  float obterBitola();

};

#endif