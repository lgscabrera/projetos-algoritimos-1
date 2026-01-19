#include "manipula_imagem.h"
#include <fstream>
#include <iostream>

using namespace std;


int** alocarMatriz(int altura, int largura) {
    int** matriz = new int*[altura];
    for (int i = 0; i < altura; ++i) {
        matriz[i] = new int[largura];
    }
    return matriz;
}
//garantia que a memória vai ser desalocada
void liberarImagem(Imagem& imagem) {
    if (imagem.pixels == nullptr) return;
    for (int i = 0; i < imagem.altura; ++i) {
        delete[] imagem.pixels[i];
    }
    delete[] imagem.pixels;
    imagem.pixels = nullptr;
}

Imagem lerImagemPGM(string& nome_arquivo) {
    Imagem img = {nullptr, 0, 0, 0};
    ifstream arquivo(nome_arquivo);
    string linha_magica;

    if (!arquivo.is_open()) { return img; }

    arquivo >> linha_magica;
    if (linha_magica != "P2") { return img; }
    //Ignora o comentários
    while (arquivo.peek() == '\n' || arquivo.peek() == '\r') arquivo.get();
    while (arquivo.peek() == '#') { arquivo.ignore(1024, '\n'); }

    arquivo >> img.largura >> img.altura;
    arquivo >> img.max_valor_cinza;

    img.pixels = alocarMatriz(img.altura, img.largura);

    
    int** p_linha = img.pixels; 
    int** p_fim_matriz = img.pixels + img.altura; 

    while (p_linha < p_fim_matriz) {
        int* p_pixel = *p_linha; 
        int* p_fim_linha = *p_linha + img.largura; 
        
        while (p_pixel < p_fim_linha) {
            arquivo >> *p_pixel; 
            p_pixel++; 
        }
        p_linha++; 
    }

    arquivo.close();
    return img;
}

void salvarImagemPGM(Imagem& imagem) {
    ofstream arquivo("imagem_modificada.pgm");
    if (!arquivo.is_open()) { return; }

    arquivo << "P2\n" << imagem.largura << " " << imagem.altura << "\n" << imagem.max_valor_cinza << "\n";

    
    int** p_linha = imagem.pixels;
    int** p_fim_matriz = imagem.pixels + imagem.altura;

    while (p_linha < p_fim_matriz) {
        int* p_pixel = *p_linha;
        int* p_fim_linha = *p_linha + imagem.largura;
        
        while (p_pixel < p_fim_linha) {
            arquivo << *p_pixel << " ";
            p_pixel++;
        }
        arquivo << "\n";
        p_linha++;
    }
    arquivo.close();
}

Imagem clarearEscurecer(Imagem& original, int fator) {
    Imagem nova_img = { alocarMatriz(original.altura, original.largura), original.largura, original.altura, original.max_valor_cinza };

    int** p_linha_orig = original.pixels;
    int** p_linha_nova = nova_img.pixels;
    int** p_fim_matriz = original.pixels + original.altura;

    while (p_linha_orig < p_fim_matriz) {
        int* p_pixel_orig = *p_linha_orig;
        int* p_pixel_nova = *p_linha_nova;
        int* p_fim_linha = *p_linha_orig + original.largura;

        while (p_pixel_orig < p_fim_linha) {
    
            int novo_valor = *p_pixel_orig + fator;
            if (novo_valor > original.max_valor_cinza) {
                novo_valor = original.max_valor_cinza;
            } else if (novo_valor < 0) {
                novo_valor = 0;
            }
            
            *p_pixel_nova = novo_valor;

            p_pixel_orig++;
            p_pixel_nova++;
        }
        p_linha_orig++;
        p_linha_nova++;
    }
    return nova_img;
}

Imagem encontrarNegativo(Imagem& original) {
    Imagem nova_img = { alocarMatriz(original.altura, original.largura), original.largura, original.altura, original.max_valor_cinza };
    int** p_linha_orig = original.pixels;
    int** p_linha_nova = nova_img.pixels;
    int** p_fim_matriz = original.pixels + original.altura;

    while (p_linha_orig < p_fim_matriz) {
        int* p_pixel_orig = *p_linha_orig;
        int* p_pixel_nova = *p_linha_nova;
        int* p_fim_linha = *p_linha_orig + original.largura;
        while (p_pixel_orig < p_fim_linha) {
            *p_pixel_nova = original.max_valor_cinza - *p_pixel_orig;
            p_pixel_orig++;
            p_pixel_nova++;
        }
        p_linha_orig++;
        p_linha_nova++;
    }
    return nova_img;
}

Imagem binarizarImagem(Imagem& original, int limiar) {
     Imagem nova_img = { alocarMatriz(original.altura, original.largura), original.largura, original.altura, original.max_valor_cinza };
    int** p_linha_orig = original.pixels;
    int** p_linha_nova = nova_img.pixels;
    int** p_fim_matriz = original.pixels + original.altura;

    while (p_linha_orig < p_fim_matriz) {
        int* p_pixel_orig = *p_linha_orig;
        int* p_pixel_nova = *p_linha_nova;
        int* p_fim_linha = *p_linha_orig + original.largura;
        while (p_pixel_orig < p_fim_linha) {
            *p_pixel_nova = (*p_pixel_orig < limiar) ? 0 : original.max_valor_cinza;
            p_pixel_orig++;
            p_pixel_nova++;
        }
        p_linha_orig++;
        p_linha_nova++;
    }
    return nova_img;
}



Imagem rotacionarDireita(Imagem& original) {
    Imagem nova_img = { alocarMatriz(original.largura, original.altura), original.altura, original.largura, original.max_valor_cinza };
    for (int i = 0; i < original.altura; ++i) {
        for (int j = 0; j < original.largura; ++j) {
            nova_img.pixels[j][original.altura - 1 - i] = original.pixels[i][j];
        }
    }
    return nova_img;
}

Imagem rotacionarEsquerda(Imagem& original) {
    Imagem nova_img = { alocarMatriz(original.largura, original.altura), original.altura, original.largura, original.max_valor_cinza };
    for (int i = 0; i < original.altura; ++i) {
        for (int j = 0; j < original.largura; ++j) {
            nova_img.pixels[original.largura - 1 - j][i] = original.pixels[i][j];
        }
    }
    return nova_img;
}

Imagem inverterHorizontalmente(Imagem& original) {
    Imagem nova_img = { alocarMatriz(original.altura, original.largura), original.largura, original.altura, original.max_valor_cinza };
    for (int i = 0; i < original.altura; ++i) {
        for (int j = 0; j < original.largura; ++j) {
            nova_img.pixels[i][j] = original.pixels[i][original.largura - 1 - j];
        }
    }
    return nova_img;
}

Imagem inverterVerticalmente(Imagem& original) {
    Imagem nova_img = { alocarMatriz(original.altura, original.largura), original.largura, original.altura, original.max_valor_cinza };
    for (int i = 0; i < original.altura; ++i) {
        for (int j = 0; j < original.largura; ++j) {
            nova_img.pixels[i][j] = original.pixels[original.altura - 1 - i][j];
        }
    }
    return nova_img;
}

Imagem iconizar(Imagem& original) {
    int TAM = 64;
    Imagem icone = { alocarMatriz(TAM, TAM), TAM, TAM, original.max_valor_cinza };
    
    float bloco_largura = static_cast<float>(original.largura) / TAM;
    float bloco_altura = static_cast<float>(original.altura) / TAM;

    for (int i = 0; i < TAM; ++i) {
        for (int j = 0; j < TAM; ++j) {
            
            int* p_pixel_icone = *(icone.pixels + i) + j;


            int inicio_linha = i * bloco_altura;
            int fim_linha = (i + 1) * bloco_altura;
            int inicio_coluna = j * bloco_largura;
            int fim_coluna = (j + 1) * bloco_largura;

            long long soma = 0;
            int contador_pixels = 0;

            for (int k = inicio_linha; k < fim_linha; ++k) {
                int* p_pixel_bloco = *(original.pixels + k) + inicio_coluna;
                int* p_fim_pixel_bloco = *(original.pixels + k) + fim_coluna;

                while (p_pixel_bloco < p_fim_pixel_bloco) {
                    soma += *p_pixel_bloco;
                    contador_pixels++;
                    p_pixel_bloco++;
                }
            }

            *p_pixel_icone = (contador_pixels > 0) ? (soma / contador_pixels) : 0;
        }
    }
    return icone;
}