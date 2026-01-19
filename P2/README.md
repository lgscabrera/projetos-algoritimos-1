Manipulador de Imagens PGM
Este projeto é uma aplicação em C++ desenvolvida para processar e manipular imagens em escala de cinza no formato PGM (Portable GrayMap - P2 ASCII). O programa utiliza alocação dinâmica de memória e aritmética de ponteiros para realizar operações de processamento de imagem de forma eficiente.

📋 Funcionalidades
O sistema oferece um menu interativo via terminal com as seguintes operações:

Leitura de Arquivo: Carrega imagens no formato .pgm (P2).

Ajuste de Brilho: Permite clarear ou escurecer a imagem com base em um fator numérico.

Binarização (Thresholding): Converte a imagem para preto e branco puro baseado em um limiar (0 a 255).

Negativo: Inverte as cores da imagem (o que é branco vira preto e vice-versa).

Rotação: Rotaciona a imagem em 90 graus para a direita ou esquerda.

Espelhamento: Inverte a imagem horizontalmente ou verticalmente.

Iconização: Reduz a imagem original para uma miniatura de 64x64 pixels utilizando a média dos blocos de pixels.

🛠️ Estrutura do Projeto
main.cpp: Contém a função principal, o menu de opções e a lógica de interação com o usuário.

manipula_imagem.h: Arquivo de cabeçalho que define a estrutura Imagem e os protótipos das funções.

manipula_imagem.cpp: Implementação das funções de manipulação de imagem, gerenciamento de memória e leitura/escrita de arquivos.

🚀 Como Compilar e Executar
Certifique-se de ter um compilador C++ (como o g++) instalado.

Compilação: Abra o terminal na pasta do projeto e execute o seguinte comando:

Bash

g++ main.cpp manipula_imagem.cpp -o out
Execução: Após compilar, inicie o programa com:

Bash

./out
(No Windows, utilize out.exe ou apenas out)

📖 Guia de Uso
Ao iniciar o programa, escolha a opção 1 para carregar uma imagem.

Digite o nome do arquivo (ex: entrada.pgm). O arquivo deve estar no mesmo diretório do executável.

Escolha uma das operações de manipulação (opções 2 a 9).

O resultado será salvo automaticamente em um arquivo chamado imagem_modificada.pgm após cada operação bem-sucedida.

Para sair, selecione a opção 0.

⚠️ Detalhes Técnicos e Requisitos
Formato de Entrada: O programa aceita apenas arquivos PGM do tipo P2 (ASCII). Linhas de comentários iniciadas com # são ignoradas durante a leitura.

Memória: O projeto utiliza alocação dinâmica de matrizes (int**) para armazenar os pixels, garantindo o uso adequado de memória para imagens de diferentes dimensões.

Saída: Todas as imagens modificadas são salvas sobrescrevendo o arquivo imagem_modificada.pgm.