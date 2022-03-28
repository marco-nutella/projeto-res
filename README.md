# Programação e Algoritmos 2021 2022 - [IADE - UE](https://www.iade.europeia.pt/) <!-- omit in toc -->

## Projeto <!-- omit in toc -->

- [Datas Relevantes](#datas-relevantes)
- [Descrição](#descrição)
  - [Frota disponível](#frota-disponível)
  - [Colocação de Navios](#colocação-de-navios)
- [Instruções](#instruções)
  - [Registar jogador (RJ)](#registar-jogador-rj)
  - [Remover jogador (EJ)](#remover-jogador-ej)
  - [Listar jogadores (LJ)](#listar-jogadores-lj)
  - [Iniciar Jogo (IJ)](#iniciar-jogo-ij)
  - [Iniciar Combate (IC)](#iniciar-combate-ic)
  - [Desistir (D)](#desistir-d)
  - [Colocar Navios (CN)](#colocar-navios-cn)
  - [Remover Navios (RN)](#remover-navios-rn)
  - [Disparar Tiro (T)](#disparar-tiro-t)
  - [Visualizar Resultado (V)](#visualizar-resultado-v)
  - [Gravar (G)](#gravar-g)
  - [Ler (L)](#ler-l)
- [Estrutura do projeto](#estrutura-do-projeto)
- [Testes de *input*/*output*](#testes-de-inputoutput)
  - [Utilização de testes](#utilização-de-testes)
- [Entrega](#entrega)
- [Prova de Autoria](#prova-de-autoria)
- [Tecnologias](#tecnologias)
- [Grupo de trabalho](#grupo-de-trabalho)
- [Avaliação](#avaliação)

## Datas Relevantes

| Data                      | Evento                         |
| ------------------------- | ------------------------------ |
| 28/03/2022                | Disponibilização do enunciado. |
| 22/05/2022 23:59:59 UTC+1 | Entrega final do trabalho.     |
| 23/05/2022 --- 27/05/2022 | Provas de autoria.             |

## Descrição

Neste projeto pretende-se a implementação do jogo da Batalha Naval. O jogo consiste em opor duas frotas, cada uma posicionada numa grelha de 10 x 10. Cada jogador só conhece o posicionamento da sua frota. Cada navio na frota ocupa um conjunto de posições na grelha, de acordo com as suas características.

Alternadamente, cada jogador dispara tiros para posições na grelha do adversário, podendo acertar num navio ou na água. Assim que um navio recebe tiros em todas as posições que ocupa, fica afundado. O jogo termina quando um jogador afunda toda a frota do adversário.

A figura seguinte apresenta o cenário de batalha, com o sistema de coordenadas a utilizar: números para linhas, letras maiúsculas para colunas. Todos os navios têm de estar contidos no cenário, e não é permitido efetuar tiros para fora do cenário.

![](figures/grid.png)

Cada jogador mantém 2 cenários: um com a posição dos seus navios, e os tiros do adversário; e outro com os seus próprios tiros.

Os navios ocupam casas contíguas no cenário, apenas e só na vertical, ou apenas e só na horizontal. A posição de um navio é determinada por um par de coordenadas iniciais, o seu tamanho, e orientação. A orientação é representada pela Norte (N), Este (E), Sul (S), Oeste (O). Por exemplo, [(2, A), 3, E] indica um navio a iniciar na posição (2, A), com tamanho 3, em direção a Este.

A interação com a aplicação efetua-se através de um conjunto de instruções com as quais os jogadores, através do terminal, interagem com o programa. O output gerado por esta interação deve seguir rigorosamente as regras descritas, já que o programa será testado automaticamente.

Será disponibilizado um conjunto de testes de treino, semelhantes aos utilizados na validação (ver a secção sobre [testes](#testes-de-inputoutput) e a secção sobre [Avaliação](#avaliação)).

### Frota disponível

Existem 5 tipos de navios, em várias quantidade e tamanhos. A tabela seguinte apresenta o detalhe.

| Nome         | Código | Tamanho | Quantidade |
| ------------ | :----: | :-----: | :--------: |
| Lancha       |   L    |    1    |     4      |
| Submarino    |   S    |    2    |     3      |
| Fragata      |   F    |    3    |     2      |
| Cruzador     |   C    |    4    |     1      |
| Porta Aviões |   P    |    5    |     1      |

### Colocação de Navios

Os navios podem ser colocados em qualquer posição no cenário, se:

- A sua coordenada de início pertencer ao cenário;
- Existir espaço livre desde a coordenada inicial até ao final do navio, de acordo com o seu tamanho e orientação indicada;
- Não ficar encostado a nenhum outro navio. Por *encostado* entende-se a distância de uma posição no tabuleiro, com vizinhança de 8 posições, i.e., distâncias de uma posição na horizontal, vertical, e diagonal de cada posição ocupada pelo navio.

Os navios podem ficar encostados à fronteira do cenário.

Todos os navios têm de ser colocados em posições válidas antes de iniciar o jogo.

Os navios são colocados através da [instrução CN](#colocar-navios-cn).

Considere a seguinte sequência para a colocação de navios, e a consequência no cenário do jogo (ver detalhe sobre formato na secção sobre [Instruções](#instruções)).

        CN Jogador1 P 1 A E
        CN Jogador1 C 1 I S
        CN Jogador1 F 3 B S
        CN Jogador1 F 10 H E
        CN Jogador1 S 3 F S
        CN Jogador1 S 8 F S
        CN Jogador1 S 10 C O
        CN Jogador1 L 8 B
        CN Jogador1 L 6 E
        CN Jogador1 L 6 G
        CN Jogador1 L 7 I

![](figures/placement.png)

## Instruções

Na descrição das várias instruções é indicada a sua sintaxe. Quer para as entradas, como para as saídas, as palavras são separadas por espaços em branco, e cada linha é terminada por um caráter fim de linha (`\n`).

Para cada instrução são indicadas as expressões de saída, quer para execuções com sucesso, quer para insucesso.

No caso de insucesso só deve surgir uma mensagem de erro. Verificando-se várias situações de insucesso em simultâneo, deve surgir apenas a mensagem do primeiro cenário de insucesso considerado, de acordo com a ordem de saídas de insucesso descritas para cada instrução. Qualquer cenário de insucesso não considerado pode ser ignorado, porque não será testado.

Caso o utilizador introduza uma instrução inválida, ou seja, não prevista na lista de instruções desta secção, ou um número de parâmetros errado para uma instrução existente, o programa deve escrever:

    Instrução inválida.

Pode assumir que não existem erros de representação de informação (e.g., texto em vez de valores numéricos).

A descrição de cada instrução pretende ser exaustiva, sem ambiguidades, e suficiente. Não deve ser possível optar entre vários comportamentos possíveis na mesma situação. Se essa situação ocorrer deve entrar em contacto com equipa docente.

A implementação não deve suportar mais instruções do que [as que estão descritas](#instruções). No entanto, nos testes públicos e privados não existirão instruções a começar pela letra `X`, pelo que pode ser utilizada para instruções convenientes ao desenvolvimento.

O programa termina quando for introduzida uma linha em branco, fora do contexto de uma instrução.

### Registar jogador (RJ)

Regista um novo jogador. Cada jogador tem um nome único. Não existe limite para o número de jogadores registados.

`Nome` é um nome de um jogador.

Entrada:

        RJ Nome

Saída com sucesso:

        Jogador registado com sucesso.

Saída com insucesso:

- Quando já existe um jogador com o mesmo nome:

        Jogador existente.

### Remover jogador (EJ)

Remove um jogador previamente registado, se este não estiver a participar no jogo em curso.

`Nome` é um nome de um jogador.

Entrada:

        EJ Nome

Saída com sucesso:

        Jogador removido com sucesso.

Saída com insucesso:

- Quando o jogador indicado não existe:

        Jogador não existente.

- Quando o jogador indicado participa no jogo em curso:

        Jogador participa no jogo em curso.

### Listar jogadores (LJ)

Lista os jogadores registados por ordem alfabética de `Nome`, indicando o número de jogos jogados e vitórias.

`Nome` é um nome de um jogador, `Jogos` é o número de jogos jogados por um jogador, e `Vitórias` é o número de vitórias de um jogador.

Entrada:

        LJ

Saída com sucesso (deve surgir uma linha por cada jogador registado):

        Nome Jogos Vitórias
        Nome Jogos Vitórias
        ...

Saída com insucesso:

- Quando não existem jogadores registados.

        Não existem jogadores registados.

### Iniciar Jogo (IJ)

Inicia um novo jogo, se não existir já um jogo iniciado.

É necessário indicar o nome dos jogadores que irão participar. Estes jogadores têm de estar previamente registados. O jogo entra em curso, sem combate iniciado, indicando, por ordem alfabética, os jogadores que nele participam

`Nome` é um nome de um jogador.

Entrada:

        IJ Nome Nome

Saída com sucesso:

        Jogo iniciado entre Nome e Nome.

Saída com insucesso:

- Quando já existe um jogo em curso:

        Existe um jogo em curso.

- Quando pelo menos um dos jogadores indicados não estão registados.

        Jogador não registado.

### Iniciar Combate (IC)

Inicia o combate no jogo em curso, se ainda não estiver iniciado. Todos os navios dos dois jogadores têm de estar colocados.

Entrada:

        IC

Saída com sucesso:

        Combate iniciado.

Saída com insucesso:

- Quando não existe um jogo em curso:

        Não existe jogo em curso.

- Quando existem navios não colocados para algum dos jogadores:

        Navios não colocados.

### Desistir (D)

Um jogador pode desistir do jogo em curso do qual faz parte, pelo que o outro jogador regista uma vitória. Ambos registam mais um jogo jogado. Caso os dois jogadores desistam, ambos somam um jogo jogado, sem vitória atribuída.

`Nome` é um nome de um jogador.

Entrada:

        D Nome[ Nome]

Saída com sucesso:

        Desistência com sucesso. Jogo terminado.

Saída com insucesso:

- Quando não existe um jogo em curso:

        Não existe jogo em curso.

- Quando um dos jogadores indicados não participa no jogo em curso:

        Jogador não participa no jogo em curso.

### Colocar Navios (CN)

Um jogador do jogo em curso, sem combate iniciado, coloca os navios no cenário, com base numa posição inicial, tamanho, e orientação.

O tamanho deve ser inferido com base no tipo de navio indicado, e não pode colocar mais que o limite de navios de cada tipo (ver tabela descritiva da [frota disponível](#frota-disponível)).

A orientação só é necessária se o navio ocupar mais que uma casa no cenário.

A posição do navio não pode ocupar casas fora do cenário, nem estar encostada a nenhum outro navio. Um navio está encostado se ocupa alguma casa com uma casa vizinha já ocupada (assume-se vizinhança a 8, i.e., a casa vizinha está à distância de uma casa na horizontal, vertical, ou diagonal).

`Nome` é um nome de um jogador, `Tipo` é o código do tipo de navio, `Linha` é o número da linha, `Coluna` é a letra maiúscula da coluna, e `Orientação` é a letra maiúscula correspondente ao ponto cardeal da orientação.

Entrada (parâmetros entre parêntesis retos são opcionais):

        CN Nome Tipo Linha Coluna[ Orientação]

Saída com sucesso:

        Navio colocado com sucesso.

Saída com insucesso:

- Quando não existe um jogo em curso:

        Não existe jogo em curso.

- Quando o jogador indicado não participa no jogo em curso:

        Jogador não participa no jogo em curso.

- Quando o jogo em curso já teve o combate iniciado:

        Combate iniciado.

- Quando a posição indicada não é válida:

        Posição irregular.

- Quando o jogador não tem navios da tipologia indicada para colocar:

        Não tem mais navios dessa tipologia disponíveis.

- Quando o jogador não tem mais navios para colocar:

        Não é possível colocar navios.

### Remover Navios (RN)

Um jogador do jogo em curso, sem combate iniciado, remove um dos seus navios do cenário. O navio a remover é identificado por uma das casas que ocupa.

`Nome` é um nome de um jogador, `Linha` é o número da linha, e `Coluna` é a letra maiúscula da coluna.

Entrada:

        RN Nome Linha Coluna

Saída com sucesso:

        Navio removido com sucesso.

Saída com insucesso:

- Quando não existe um jogo em curso:

        Não existe jogo em curso.

- Quando o jogo em curso já teve o combate iniciado:

        Combate iniciado.

- Quando o jogador indicado não participa no jogo em curso:

        Jogador não participa no jogo em curso.

- QUando não existe navio colocado na posição indicada.

        Não existe navio na posição.

### Disparar Tiro (T)

Um jogador do jogo em curso, com combate iniciado, dispara um tiro, se fizer parte do jogo em curso, e for a sua vez. Se nenhum jogador tiver disparado no jogo em curso, qualquer um pode ser o primeiro.

`Nome` é um nome de um jogador, e `Tipo` é o código do tipo de navio.

Entrada:

        T Nome Linha Coluna

Saída com sucesso (apenas uma saída das seguintes):

        Tiro na água.
        Tiro em navio Tipo.
        Navio Tipo afundado. Jogo terminado.
        Navio Tipo afundado.

Saída com insucesso:

- Quando não existe um jogo em curso:

        Não existe jogo em curso.

- Quando o jogo em curso ainda não tem o combate iniciado.

        Jogo em curso sem combate iniciado.

- Quando o jogador indicado não participa no jogo em curso:

        Jogador não participa no jogo em curso.

- Quando a posição indicada não é válida:

        Posição irregular.

### Visualizar Resultado (V)

Mostra o resultado atual do jogo em curso, com combate iniciado.

`Nome` é um nome de um jogador, `Tiros` número de tiros disparados, `TirosEmNavios` número de tiros que acertaram em navios, e `NaviosAfundados` número de navios do adversário afundados.

Entrada:

        V

Saída com sucesso (devem surgir duas mensagens, ordenadas por nome de jogador):

        Nome Tiros TirosEmNavios NaviosAfundados
        Nome Tiros TirosEmNavios NaviosAfundados

Saída com insucesso:

- Quando não existe um jogo em curso:

        Não existe jogo em curso.

- Quando o jogo em curso ainda não tem o combate iniciado.

        Jogo em curso sem combate iniciado.

### Gravar (G)

Grava a lista de jogadores, resultados, e estado do jogo em curso (se existir) em ficheiro.

Entrada:

        G

Saída com sucesso:

        Jogo gravado.

Saída com insucesso:

- Quando ocorre um erro na gravação:

        Ocorreu um erro na gravação.

### Ler (L)

Lê a lista de jogadores, resultados, e estado do jogo em curso (se existir) de ficheiro.

Entrada:

        L

Saída com sucesso:

        Jogo carregado.

Saída com insucesso:

- Quando ocorre um erro na leitura:

        Ocorreu um erro no carregamento.

## Estrutura do projeto

A estrutura mínima do projeto deve ser a seguinte:

      projeto
      |-- src: diretório com todo o código fonte
      |-- src/main.c : ficheiro com o ponto de entrada do programa
      |-- bin: diretório com o código compilado
      |-- Makefile: ficheiro de configuração
      |-- iotests : diretório com testes de output, a distribuir pela docência
      |-- README.md : este ficheiro
      |-- REPORT.md : relatório do projeto

O ficheiro `src/main.c` disponibilizado inclui código condicional que assegura que o caráter sinalizador de *nova linha* (`\n`) não é convertido para o padrão Windows (`\r\n`).

O repositório de referência está disponível em <https://github.com/IADE-PA/PA-2021-2022-Projeto>

Para efetuar a atualizações:

1. Registar o repositório como `upstream` (só deve acontecer uma vez)

        git remote add upstream https://github.com/IADE-PA/PA-2021-2022-Projeto

2. Atualizar o `upstream` (sempre que existirem atualizações)

        git fetch upstream

3. Obter as alterações (e.g., ficheiro `README.md`)

        git checkout upstream/main README.md

## Testes de *input*/*output*

O projeto é validado através de um conjunto de baterias de teste de *input*/*output*.

Cada bateria é constituída por um ficheiro de entrada e outro e saída. O ficheiro de entrada contém uma sequência de instruções a passar pelo programa que, por sua vez, deve produzir uma sequência de saída *exatamente* igual ao ficheiro de saída. A comparação será feita *byte* a *byte*, pelo que não podem existir quaisquer diferenças para o programa ser considerado válido.

As baterias serão distribuídas através do repositório git de referência, na diretoria `iotests` (será necessário registar o repositório de referência como `upstream`, de acordo com as instruções na secção sobre [estrutura do projeto](#estrutura-do-projeto)).

Os grupos de trabalho devem utilizar as baterias públicas para validar o desenvolvimento do projeto.

### Utilização de testes

Os testes disponibilizados devem ser utilizados por ordem, já que os cenários descritos num teste podem depender dos cenários dos testes anteriores. Na linha de comandos Windows (Command Prompt) e em GNU Linux/MacOs, cada teste deve ser utilizado da seguinte forma:

    main < 1.in > 1.mine.out

A instrução `<` redireciona o *standard input* para o ficheiro indicado, e a instrução `>` redireciona o *standard output* para o ficheiro indicado (cria se não existir, e escreve por cima se existir).

No exemplo, o ficheiro `1.in` contém várias instruções para testar o programa. O ficheiro `1.out` contém as saídas correspondentes às instruções no ficheiro `1.in`. O ficheiro `1.mine.out` será criado com as saídas que o programa gerar. Os ficheiros `1.out` e `1.mine.out` devem ser
idênticos.

A comparação entre ficheiros pode ser feita na linha de comandos, recorrendo ao programa `comp` em Windows, ou `diff` em Linux e MacOS.

A comparação também pode ser feita recorrendo a alguns IDEs ou editores de texto, tal como o [*Visual Studio Code*](https://code.visualstudio.com/). Para tal, abra o diretório do projeto em *File - Open Folder*. Selecione o diretório do projeto confirme em *Select Folder*. Caso não esteja visível, abra o explorador de ficheiros do *Visual Studio Code* em *View - Explorer*.

Selecione os dois ficheiros a comparar (selecione um, e selecione o outro enquanto pressiona na tecla `Ctrl`, ou `Cmd` em MacOS).

![](figures/vsc_two_file_selection.png)

Com os dois ficheiros selecionados, utilize o botão direito do rato em cima da seleção para obter um menu. Escolha *Compare Selected*.

![](figures/vsc_compare_selected.png)

O *Visual Studio Code* apresenta os dois ficheiros com as diferenças a vermelho e verde. Caso não existam diferenças, as linhas dos dois ficheiros surgem sem cores.

## Entrega

A entrega do projeto é feita no *GitHub Classroom* e na plataforma de *e-learning*.

Deve existir, na raiz do repositório, um ficheiro de relatório `REPORT.md` com a identificação dos elementos do grupo de trabalho, e eventuais comentários relativos a estratégias de implementação adotadas, e/ou à distribuição de tarefas.

A ausência de identificação individual no ficheiro de relatório implica a anulação da participação individual no projeto.

O código fonte entregue será sujeito a validação por um conjunto de testes reservado para esse efeito, e será compilado recorrendo a GNU Make, de acordo com a configuração presente no ficheiro `Makefile`, executando apenas

```bash
make
```

A compilação deve gerar o programa `main` no diretório `bin`, que será executado com as instruções dos testes.

A entrega no *e-learning* corresponde a um ficheiro `zip` do repositório *GitHub Classroom*, excluindo ficheiros compilados (i.e., executar `make clean` antes de construir o `zip`).

## Prova de Autoria

Todos os projetos entregues serão sujeitos a prova de autoria. Para esse efeito, cada grupo terá que efetuar uma discussão com a docência, de forma a demonstrar que o código entregue foi de facto feito pelo grupo, e que a distribuição de trabalho foi equilibrada.

O calendário das provas de autoria será disponibilizado no *e-learning*, após o prazo de entrega da implementação do projeto.

A não comparência na prova de autoria implica a anulação da participação individual no projeto.

## Tecnologias

O projeto deve ser implementado em C (C11, gcc versão 8.1, ou superior).

A avaliação vai ser feita em GNU Linux, 

Não podem ser utilizadas bibliotecas externas à distribuição padrão. No caso de dúvida, o corpo docente deve ser consultado.

## Grupo de trabalho

Os grupos de trabalho devem ter 4 pessoas, e são constituídos no início do semestre. Idealmente, todos os elementos do grupo devem participar em todos os aspetos do projeto. No entanto, pode existir divisão de tarefas, sendo que esta deve ser equilibrada.

Grupos com um número diferente de pessoas devem ser explicitamente autorizados pelo corpo docente.

## Avaliação

O projeto é avaliado com base em duas componentes: quantitativa (*A*), e qualitativa (*B*). A nota final do projeto é determinada por *(0.5 x A) + (0.5 x B)*.

| Instrução | Peso |
| --------- | :--: |
| RJ        |  1   |
| EJ        |  1   |
| LJ        |  1   |
| IJ        |  2   |
| IC        |  1   |
| D         |  1   |
| SN        |  2   |
| RN        |  2   |
| T         |  3   |
| V         |  2   |
| G         |  2   |
| L         |  2   |

A avaliação qualitativa irá considerar que existem várias formas de resolver o problema descrito, mas exige-se a utilização dos instrumentos e métodos apresentados na unidade curricular, nomeadamente:

- Separação entre interface, dados, e lógica da aplicação;
- Justificação clara para as variáveis e operações implementadas;
- Organização da solução coerente com a metodologia apresentada na unidade curricular;
- Adequação da escolha de estruturas de dados e algoritmos para a resolução do problema.

A implementação estrita de todas as instruções descritas neste enunciado assegura, sem prejuízo de reprovação por irregularidade académica, a nota mínima de 10 valores.

As notas finais do projeto serão disponibilizadas no Canvas.
