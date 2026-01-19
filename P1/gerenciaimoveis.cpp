    /****************************************************************************************
            Objetivo: Desenvolver um programa que gerencie um banco de dados de imóveis, permitindo a inclusão, busca, exclusão e exibição de imóveis com diversas características.      
    ****************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX = 200;


typedef struct { // Definição do registro do imóvel
    string tipo, finalidade, endereco, bairro, cidade, piso, conservacao;
    float area, valor, iptu;
    int quartos, suites, banheiros, vagas;
    bool cozinha, sala, varanda, areaServico;
    bool armarios, arCondicionado, aquecedor, ventilador;
}Imovel;


bool lerImovel(ifstream &arq, Imovel &imovel) { // Função para ler um imóvel dentro do arquivo
    arq >> imovel.tipo;
    if (imovel.tipo == "fim") return false;
    arq >> imovel.finalidade >> imovel.endereco >> imovel.bairro >> imovel.cidade;
    arq >> imovel.area >> imovel.valor >> imovel.iptu;
    arq >> imovel.quartos >> imovel.suites >> imovel.banheiros >> imovel.vagas;
    arq >> imovel.cozinha >> imovel.sala >> imovel.varanda >> imovel.areaServico;
    arq >> imovel.piso >> imovel.conservacao;
    arq >> imovel.armarios >> imovel.arCondicionado >> imovel.aquecedor >> imovel.ventilador;
    return true;
}


void exibirImovel(Imovel imovel) {  // Função para exibir o imóvel
    cout << "Tipo: " << imovel.tipo << ", Endereço: " << imovel.endereco
         << ", Cidade: " << imovel.cidade << ", Valor: " << imovel.valor
         << ", Quartos: " << imovel.quartos << ", Suites: " << imovel.suites << endl;
}


void salvarArquivo(Imovel imoveis[], int total, const string &nomeArquivo) {    // Função para salvar os imóveis no arquivo
    ofstream arq(nomeArquivo);
    arq << "tipo finalidade endereco bairro cidade area valor iptu quartos suites banheiros vagas cozinha sala varanda areaServico piso conservacao armarios arCondicionado aquecedor ventilador" << endl;
    for (int i = 0; i < total; i++) {
        arq << imoveis[i].tipo << " " << imoveis[i].finalidade << " " << imoveis[i].endereco << " "
            << imoveis[i].bairro << " " << imoveis[i].cidade << " " << imoveis[i].area << " "
            << imoveis[i].valor << " " << imoveis[i].iptu << " " << imoveis[i].quartos << " "
            << imoveis[i].suites << " " << imoveis[i].banheiros << " " << imoveis[i].vagas << " "
            << imoveis[i].cozinha << " " << imoveis[i].sala << " " << imoveis[i].varanda << " "
            << imoveis[i].areaServico << " " << imoveis[i].piso << " " << imoveis[i].conservacao << " "
            << imoveis[i].armarios << " " << imoveis[i].arCondicionado << " "
            << imoveis[i].aquecedor << " " << imoveis[i].ventilador << endl;
    }
    arq << "fim" << endl;
    arq.close();
}


int main() {    // Função principal
    Imovel imoveis[MAX];
    int total = 0;
    string nomeArquivo = "BD_Imoveis2.txt";
    
    // Leitura inicial do arquivo
    ifstream arq(nomeArquivo);
    string cabecalho;
    getline(arq, cabecalho); // Ignora a primeira linha do arquivo (cabeçalho)
    if (!arq.is_open()) {   //Indica caso o arquivo não possa ser aberto
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return 1;
    }

    while (total < MAX && lerImovel(arq, imoveis[total])) {
        total++;
    }
    arq.close();

    int opcao;  //Menu de opções
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Incluir novo imóvel\n";
        cout << "2. Buscar por rua (com exclusão)\n";
        cout << "3. Buscar imóveis por faixa de valor\n";
        cout << "4. Buscar por características (armários, ar-condicionado, aquecedor, ventilador)\n";
        cout << "5. Buscar por número de quartos e suítes\n";
        cout << "6. Estatísticas\n";
        cout << "7. Listar todos os imóveis\n";
        cout << "0. Sair\n";
        cout << "Opção: ";
        cin >> opcao;

        if (opcao == 1) {   // Incluir novo imóvel
            if (total < MAX) {
                cout << "Digite os dados do novo imóvel (tipo finalidade endereco bairro cidade area valor iptu quartos suites banheiros vagas cozinha sala varanda areaServico piso conservacao armarios arCondicionado aquecedor ventilador):\n";
                Imovel novo;
                cin >> novo.tipo >> novo.finalidade >> novo.endereco >> novo.bairro >> novo.cidade
                    >> novo.area >> novo.valor >> novo.iptu
                    >> novo.quartos >> novo.suites >> novo.banheiros >> novo.vagas
                    >> novo.cozinha >> novo.sala >> novo.varanda >> novo.areaServico
                    >> novo.piso >> novo.conservacao
                    >> novo.armarios >> novo.arCondicionado >> novo.aquecedor >> novo.ventilador;
                imoveis[total++] = novo;
                cout << "Imóvel adicionado com sucesso!\n";
            } else {
                cout << "Limite de imóveis atingido.\n";
            }
        }

        else if (opcao == 2) {  // Buscar por rua e / ou excluir
            string rua;
            cout << "Digite o nome da rua para busca: ";
            cin >> rua;
            for (int i = 0; i < total; i++) {
                if (imoveis[i].endereco == rua) {
                    exibirImovel(imoveis[i]);
                    char excluir;
                    cout << "Deseja excluir este imóvel? (s/n): ";
                    cin >> excluir;
                    if (excluir == 's') {
                        for (int j = i; j < total - 1; j++) {
                            imoveis[j] = imoveis[j + 1];
                        }
                        total--;
                        cout << "Imóvel excluído.\n";
                        break;
                    }
                }
            }
        }

        else if (opcao == 3) { // Buscar imóveis por faixa de valor
            float min, max;
            cout << "Digite valor mínimo e máximo: ";
            cin >> min >> max;
            for (int i = 0; i < total; i++) {
                if (imoveis[i].valor >= min && imoveis[i].valor <= max) {
                    exibirImovel(imoveis[i]);
                }
            }
        }

        else if (opcao == 4) { // Buscar por características
            bool a, b, c, d;
            cout << "Armários (0/1), Ar-condicionado (0/1), Aquecedor (0/1), Ventilador (0/1): ";
            cin >> a >> b >> c >> d;
            for (int i = 0; i < total; i++) {
                if (imoveis[i].armarios == a &&
                    imoveis[i].arCondicionado == b &&
                    imoveis[i].aquecedor == c &&
                    imoveis[i].ventilador == d) {
                    exibirImovel(imoveis[i]);
                }
            }
        }

        else if (opcao == 5) { // Buscar por número de quartos e suítes
            int q, s;
            cout << "Digite número mínimo de quartos e suítes: ";
            cin >> q >> s;
            for (int i = 0; i < total; i++) {
                if (imoveis[i].quartos >= q && imoveis[i].suites >= s) {
                    exibirImovel(imoveis[i]);
                }
            }
        }

        else if (opcao == 6) {  // Estatísticas do imovel 
            int venda = 0, locacao = 0, temporada = 0;
            int casasComSuite = 0;
            int salasComCeramica = 0;
            for (int i = 0; i < total; i++) {
                if (imoveis[i].finalidade == "venda") venda++;
                if (imoveis[i].finalidade == "locacao") locacao++;
                if (imoveis[i].finalidade == "temporada") temporada++;
                if (imoveis[i].tipo == "casa" && imoveis[i].suites > 0) casasComSuite++;
                if (imoveis[i].tipo == "sala" && imoveis[i].piso == "ceramica") salasComCeramica++;
            }
            cout << "Percentual venda: " << (venda * 100.0 / total) << "%\n";
            cout << "Percentual locacao: " << (locacao * 100.0 / total) << "%\n";
            cout << "Percentual temporada: " << (temporada * 100.0 / total) << "%\n";
            cout << "Casas com suíte: " << (casasComSuite * 100.0 / total) << "%\n";
            cout << "Salas com piso cerâmica: " << (salasComCeramica * 100.0 / total) << "%\n";
        }

        else if (opcao == 7) { // Listar todos os imóveis cadastradis
            for (int i = 0; i < total; i++) {
                exibirImovel(imoveis[i]);
            }
        }

    } while (opcao != 0);


    salvarArquivo(imoveis, total, nomeArquivo);     // Salva os dados atualizados no arquivo

    cout << "Dados salvos. Encerrando programa.\n";
    return 0;
}