//Para executar: ´´g++ main.cpp manipula_imagem.cpp -o out´´ e em seguida ´´./out´´

#include <iostream>
#include <string>
#include <limits>
#include "manipula_imagem.h"

using namespace std;

void exibirMenu() {
    cout << "\n--- MENU DE MANIPULACAO DE IMAGENS PGM ---\n";
    cout << "1. Ler imagem de entrada\n";
    cout << "2. Escurecer ou Clarear imagem\n";
    cout << "3. Binarizar imagem\n";
    cout << "4. Encontrar imagem negativa\n";
    cout << "5. Rotacionar 90 graus para a Direita\n";
    cout << "6. Rotacionar 90 graus para a Esquerda\n";
    cout << "7. Inverter imagem Horizontalmente\n";
    cout << "8. Inverter imagem Verticalmente\n";
    cout << "9. Iconizar imagem (reduzir para 64x64)\n";
    cout << "0. Sair\n";
    cout << "------------------------------------------\n";
    cout << "Escolha uma opcao: ";
}

int main() {
    Imagem imagem_atual = {nullptr, 0, 0, 0};
    int opcao;

    do {
        exibirMenu();
        cin >> opcao;
        //Garante que o Enter funcione
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (imagem_atual.pixels == nullptr && opcao != 1 && opcao != 0) {
            cout << "\nAVISO: Primeiro carregue uma imagem com a opcao 1.\n";
            continue;
        }

        Imagem imagem_nova = {nullptr, 0, 0, 0};
        bool operacao_realizada = false;

        switch (opcao) {
            case 1: {
                if (imagem_atual.pixels != nullptr) {
                    liberarImagem(imagem_atual);
                }
                cout << "Digite o nome do arquivo de imagem PGM de entrada (coloque .pgm no final do nome): ";
                string nome_arquivo_entrada;
                getline(cin, nome_arquivo_entrada);
                
                imagem_atual = lerImagemPGM(nome_arquivo_entrada);

                if (imagem_atual.pixels != nullptr) {
                    cout << "Imagem '" << nome_arquivo_entrada << "' carregada com sucesso!\n";
                } else {
                    cout << "Falha ao carregar a imagem.\n";
                }
                break;
            }
            case 2: {
                float fator;
                cout << "Digite o fator para clarear (Positivo) ou escurecer (Negativo): ";
                cin >> fator;
                imagem_nova = clarearEscurecer(imagem_atual, fator);
                operacao_realizada = true;
                break;
            }
            case 3: {
                int limiar;
                cout << "Digite o limiar para binarizacao (0 a " << imagem_atual.max_valor_cinza << "): ";
                cin >> limiar;
                imagem_nova = binarizarImagem(imagem_atual, limiar);
                operacao_realizada = true;
                break;
            }
            case 4:
                imagem_nova = encontrarNegativo(imagem_atual);
                operacao_realizada = true;
                break;
            case 5:
                imagem_nova = rotacionarDireita(imagem_atual);
                operacao_realizada = true;
                break;
            case 6:
                imagem_nova = rotacionarEsquerda(imagem_atual);
                operacao_realizada = true;
                break;
            case 7:
                imagem_nova = inverterHorizontalmente(imagem_atual);
                operacao_realizada = true;
                break;
            case 8:
                imagem_nova = inverterVerticalmente(imagem_atual);
                operacao_realizada = true;
                break;
            case 9:
                imagem_nova = iconizar(imagem_atual);
                operacao_realizada = true;
                break;
            case 0:
                cout << "Pograma encerrado\n";
                break;
            default:
                cout << "Insira um valor válido\n";
                break;
        }

        if (operacao_realizada) {
            liberarImagem(imagem_atual);
            imagem_atual = imagem_nova;
            
            salvarImagemPGM(imagem_atual);
            cout << "Imagem modificada com sucesso\n";
        }

    } while (opcao != 0);

    if (imagem_atual.pixels != nullptr) {
        liberarImagem(imagem_atual);
    }

    return 0;
}