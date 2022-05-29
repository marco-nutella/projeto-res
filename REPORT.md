# Relatório de Projeto de Programação e Algoritmos 2021/2022 - IADE UE

## Grupo de trabalho

|     Número     |           Nome            |
|----------------|---------------------------|
|    20210046    |   Carolyne Melo           |
|    20211019    |   Marco Antônio Camargo   |
|    20210008    |   Diogo Carvalho          |
|    20210119    |   Paulino Muya            |

## Descrição da solução
Para a solução, foi utilizado como base o código disponibilizado pelo professor, em especial o código das listas. A solução é centrada ao redor de uma estrutura anônima de "Jogadores", que detém todas as suas estatícas individuais, os seus navios e um tabuleiro individual. Os tabuleiros 10x10 possuem uma referência à estruturas dos navios, que contém todos os seus detalhes e suas posições. Os jogadores possuem "pontos de vida" equivalentes à todas as partes de seus navios, permitindo o rápido término do jogo quando estes chegarem a zero, ao invés de ter de verificar o tabuleiro inteiro por partes ainda de pé. Assim, quando atingidos, os navios podem apenas remover o seu ponteiro de um quadrado no tabuleiro, uma das suas posições de sua lista de posições e subtrair um de suas partes ainda de pé, facilitando o processo de determinar qual navio foi atingido.

Os jogadores são inseridos em um único "jogo", onde podem ser colocados e retirados da lista de participantes. Apenas os participantes
possuem acesso ao jogo de batalha naval. Onde necessário, os comandos são traduzidos para um formato mais fácil de interpretar para o código (Ex: As letras das colunas são subtraídas por 65, a posição do "A" em ASCII, resultando em um número utilizável diretamente nos tabuleiros). Várias funções foram criadas para fazerem interface com as estruturas anônimas e seus dados, permitindo que o código seja legível e modular.

O código pode ser compilado com "make".

## Distribuição de tarefas
Devido à dificuldade do projeto e à grande variedade de níveis de experiência e familiaridade com programação nos membros do grupo, o projeto foi realizado em conjunto por meio do Live Share do Visual Studio Code, com todos a contibuir sugestões e ideias enquanto os membros mais experientes do grupo escreviam o código. O código também foi foi planejado com antecedência, facilitando o processo.

## Observações
O projeto não foi acabado por completo, mas grande parte do backend está completa, e parte dos comandos também.
O sorting em LJ corre, mas não faz sorting da lista. Não conseguimos encontrar uma solução. Há um Segmentation Fault que não foi indentificado em new_ship().