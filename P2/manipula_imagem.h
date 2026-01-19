#include <string>

struct Imagem {
    int** pixels;
    int largura;
    int altura;
    int max_valor_cinza;
};

int** alocarMatriz(int altura, int largura);
void liberarImagem(Imagem& imagem);

Imagem lerImagemPGM(std::string& nome_arquivo);
void salvarImagemPGM(Imagem& imagem);

Imagem clarearEscurecer(Imagem& imagem_original, int fator);
Imagem encontrarNegativo(Imagem& imagem_original);
Imagem binarizarImagem(Imagem& imagem_original, int limiar);
Imagem rotacionarDireita(Imagem& imagem_original);
Imagem rotacionarEsquerda(Imagem& imagem_original);
Imagem inverterHorizontalmente(Imagem& imagem_original);
Imagem inverterVerticalmente(Imagem& imagem_original);
Imagem iconizar(Imagem& imagem_original);

