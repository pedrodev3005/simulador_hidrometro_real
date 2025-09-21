# Simulador de Hidrômetro em C++

## Visão Geral do Projeto

Este projeto é um simulador de hidrômetro modular, desenvolvido em C++ com uma arquitetura orientada a objetos. Ele foi projetado para simular o funcionamento de um hidrômetro, calculando o consumo de água, e gerando uma representação visual do seu mostrador. O simulador se comporta como um dispositivo que pode ser "observado" por outros softwares para obter leituras de consumo.

As principais funcionalidades incluem:

- Simulação de fluxo de água com base em parâmetros de entrada.
- Atualização em tempo real de um mostrador digital.
- Geração periódica de imagens do mostrador para consumo externo.
- Configuração por meio de um arquivo externo (`config.txt`).

---

## Arquitetura e Design

O projeto segue os princípios de **Programação Orientada a Objetos (POO)** e **Separação de Responsabilidades**. Cada classe tem um único e bem definido propósito, tornando o código robusto, escalável e fácil de manter.

A comunicação entre as classes é realizada através de **injeção de dependência**, onde a classe principal (`Hidrometro`) recebe referências para as outras classes das quais depende, em vez de criá-las por conta própria.

---

## 4. Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

- **`main.cpp`**: O ponto de entrada do programa. Orquestra a criação e a interação das classes.
- **`config.txt`**: O arquivo de configuração com os parâmetros da simulação.
- **`hidrometro_base.bmp`**: A imagem de fundo do mostrador do hidrômetro.
- **`Configuracao.hpp` / `Configuracao.cpp`**: A classe responsável por ler o arquivo de configuração e gerenciar os parâmetros.
- **`Entrada.hpp` / `Entrada.cpp`**: A classe que representa o fluxo de entrada de água e seus parâmetros físicos.
- **`Saida.hpp` / `Saida.cpp`**: A classe que representa a saída de água do hidrômetro.
- **`Hidrometro.hpp` / `Hidrometro.cpp`**: O núcleo da simulação. Gerencia a lógica de cálculo de consumo e vazão.
- **`Display.hpp` / `Display.cpp`**: A classe que gerencia a apresentação visual, tanto na tela quanto em arquivos de imagem.
- **`CImg.h`**: O arquivo de cabeçalho da biblioteca CImg.

---

## 5. Documentação das Classes

### `Configuracao`

- **Propósito**: Ler e gerenciar os parâmetros do simulador a partir de um arquivo de texto. Permite alterar o comportamento sem recompilar o código..

### `Entrada`

- **Propósito**: Representar as propriedades físicas da entrada de água, como o nível de entrada e a bitola do cano.

### `Saida`

- **Propósito**: Representar as propriedades físicas da saída de água do hidrômetro, como a bitola do cano.

### `Display`

- **Propósito**: Gerenciar a apresentação visual. A classe é responsável por exibir a leitura em tempo real, gerar imagens do mostrador e salvar essas imagens.

### `Hidrometro`

- **Propósito**: O motor da simulação. Ele coordena o fluxo de dados, realiza os cálculos de vazão e consumo e gerencia o estado do hidrômetro.

---

## 6. Como Compilar e Executar

### Pré-requisitos

Para compilar e rodar este projeto, você precisa do compilador `g++` e das seguintes bibliotecas externas:

- **CImg**: Biblioteca `header-only` (arquivo `CImg.h`).
- **Bibliotecas de Sistema**: `gdiplus`, `gdi32`, `user32` (para Windows).

### Configuração do Projeto

1. Baixe e salve os arquivos na mesma pasta.
2. modifique o arquivo `config.txt` com os parâmetros que deseja para testar:
3. Obs. Uma vez com o projeto compilado, para testar outras entradas, basta modificar o config.txt, salvá-lo e executar o executável novamente.

### Compilação

Abra o terminal na pasta do projeto e execute o seguinte comando para compilar todos os arquivos `.cpp` e linkar as bibliotecas necessárias:

```bash
g++ main.cpp Configuracao.cpp Entrada.cpp Saida.cpp Display.cpp Hidrometro.cpp -o simulador.exe -lgdiplus -lgdi32 -luser32
```

### Execução

Após a compilação, execute o programa com o comando:

```bash
./simulador.exe
```

O programa criará a pasta `saida_imagens` e começará a exibir o mostrador do hidrômetro em tempo real, salvando uma imagem a cada segundo. Feche a janela para encerrar a simulação.

---

## 7. Detalhamento das Funções

descrição detalhada das principais funções de cada classe.

### Classe `Configuracao`

- **`Configuracao(const std::string& arquivo)`**
    - **Propósito**: Construtor da classe. Inicializa o objeto `Configuracao` com o caminho para o arquivo de texto que será lido.
    - **Parâmetros**: `arquivo` - O caminho do arquivo de configuração (`config.txt`).
- **`carregarParametros()`**
    - **Propósito**: Lê o arquivo de configuração e armazena os pares de chave-valor em um `map` interno. Realiza validação de arquivo.
    - **Retorno**: `void` (não retorna um valor, mas popula o atributo `parametros`).
- **`obterParametro(const std::string& chave)`**
    - **Propósito**: Retorna o valor associado a uma chave específica do arquivo de configuração.
    - **Parâmetros**: `chave` - A chave do parâmetro a ser obtido (ex: "nivel_entrada").
    - **Retorno**: `std::string` - O valor do parâmetro como uma string. Lança uma exceção se a chave não for encontrada.

### Classe `Entrada`

- **`Entrada()`**
    - **Propósito**: Construtor padrão. Inicializa os atributos `nivelEntradaAgua` e `bitola` com o valor 0.0f.
- **`definirNivel(float nivel)`**
    - **Propósito**: Define o nível de entrada de água.
    - **Parâmetros**: `nivel` - O nível de entrada de água em milímetros (mm).
- **`obterNivel()`**
    - **Propósito**: Retorna o nível de entrada de água atual.
    - **Retorno**: `float` - O nível de água em mm.
- **`definirBitola(float bitola)`**
    - **Propósito**: Define a bitola do cano de entrada.
    - **Parâmetros**: `bitola` - A bitola do cano em milímetros (mm).
- **`obterBitola()`**
    - **Propósito**: Retorna a bitola do cano de entrada.
    - **Retorno**: `float` - A bitola em mm.

### Classe `Saida`

- **`Saida(float bitola)`**
    - **Propósito**: Construtor da classe. Inicializa o objeto `Saida` com o valor da bitola.
    - **Parâmetros**: `bitola` - O valor da bitola de saída em milímetros (mm).
- **`obterBitola()`**
    - **Propósito**: Retorna o valor da bitola de saída.
    - **Retorno**: `float` - A bitola em mm.

### Classe `Display`

- **`Display(int deltaTImagem, const std::string& caminhoImagem, const std::string& caminhoSaida)`**
    - **Propósito**: Construtor. Inicializa o display com o tempo de geração de imagem, o caminho da imagem de fundo e o diretório de saída. Ele também carrega a imagem de fundo e cria a janela de exibição.
- **`exibir(float valor)`**
    - **Propósito**: Atualiza a janela de exibição em tempo real. Pega o valor total do contador, o formata em metros cúbicos e litros, e desenha os números na imagem de fundo, atualizando a tela.
    - **Parâmetros**: `valor` - O valor atual do contador do hidrômetro em metros cúbicos (`m³`).
- **`gerarImagem(float contador)`**
    - **Propósito**: Salva a imagem do mostrador em um arquivo no disco. Apenas pega o display já atualizado pelo método `exibir` e salva esse display de acordo com o valor do `contador`.
    - **Parâmetros**: `contador` - O valor atual do contador.
- **`obterDeltaTImagem()`**
    - **Propósito**: Retorna o intervalo de tempo para a geração de imagens, lido do arquivo de configuração.
    - **Retorno**: `int` - O `Delta T` em milissegundos.

### Classe `Hidrometro`

- **`Hidrometro(Entrada& entrada, Saida& saida, Display& display)`**
    - **Propósito**: Construtor. Inicializa o estado interno do hidrômetro e recebe referências para as outras classes, injetando suas dependências.
- **`iniciarSimulacao()`**
    - **Propósito**: Inicia o loop principal do programa. O loop é ininterrupto e executa a lógica de simulação em um ciclo contínuo até que o contador atinja o valor máximo ou a janela seja fechada.
- **`calcularVazao()`**
    - **Propósito**: Calcula a vazão de água atual em `m³/s`, usando o nível de entrada e as bitolas de entrada e saída. A lógica também considera o estado de "falta de água" para reduzir a vazão.
- **`atualizarContador()`**
    - **Propósito**: Adiciona a vazão calculada ao valor total do contador.
- **`simularFaltaAgua(bool estado)`**
    - **Propósito**: Alterna o estado de simulação de falta de água, afetando a `vazaoAtual`.

### `main.cpp` (Função `main()`)

- **Propósito**: É o ponto de entrada do programa e a classe de orquestração. Sua responsabilidade é configurar todo o sistema:
    1. Ler os parâmetros do `config.txt`.
    2. Criar as instâncias das classes `Entrada`, `Saida` e `Display`.
    3. Passar os parâmetros de configuração para essas classes.
    4. Criar a instância da classe `Hidrometro`, injetando as dependências.
    5. Chamar `hidrometro.iniciarSimulacao()` para iniciar o loop principal.
