
Como usar o programa:

1. Compile o programa em C++
   - Use um compilador como g++:
     g++ -o imoveis imoveis.cpp
   - Ou use uma IDE como Code::Blocks, Dev C++, Visual Studio ou outros.

2. Coloque o arquivo BD_Imoveis2.txt na mesma pasta do executável.

3. Execute o programa
   - No terminal:
     ./imoveis

Formato do Arquivo BD_Imoveis2.txt:

O arquivo deve conter os imóveis, um por linha, com os seguintes 22 campos separados por espaço:

1. tipo
2. finalidade
3. endereco (com _ no lugar dos espaços, ex: Rua_das_Flores)
4. bairro
5. cidade
6. area
7. valor
8. iptu
9. quartos
10. suítes
11. banheiros
12. vagas
13. cozinha
14. sala
15. varanda
16. area_servico
17. piso
18. conservacao
19. armarios
20. ar_condicionado
21. aquecedor
22. ventilador

Exemplo de linha no arquivo:
casa venda Rua_das_Flores Centro Alfenas 120.0 250000.0 1200.0 3 1 2 2 sim sim sim sim ceramica boa sim sim nao nao

- A primeira linha deve ser ignorada (cabeçalho).
- A última linha deve conter a palavra “fim” e será desconsiderada.

Funcionalidades disponíveis no Menu do Programa:

1. Inclusão de novo imóvel
2. Buscar imóvel por rua e permitir exclusão
3. Buscar imóveis por faixa de valor
4. Buscar imóveis pelas características: armários, ar-condicionado, aquecedor, ventilador
5. Buscar imóveis por número de quartos e suítes
6. Estatísticas:
   - % de imóveis por finalidade (venda/aluguel/temporada)
   - % de casas com suítes
   - % de salas comerciais com piso cerâmico
7. Listar todos os imóveis disponíveis
0. Sair (os dados são salvos no arquivo automaticamente)

Desenvolvido por:
Luiz Gabriel da Silva Cabrera
