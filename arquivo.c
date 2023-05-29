#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

void inicializarDados(int vet[][4], int tam) {
  int i;
  for (i = 0; i < tam; i++) {
    vet[i][0] = -1;
    vet[i][1] = -1;
    vet[i][2] = -1;
    vet[i][3] = -1;
  }
}

void carregarDadosArquivo(char matpergs[][100], char matresp1[][100],
                          char matresp2[][100], char matresp3[][100],
                          char matresp4[][100], int matvalores[][4], int tam) {
  FILE *arq = fopen("dados.txt", "r");
  int linha = 0, parte;
  char frase[1000];

  while (fscanf(arq, "%[^\n] ", frase) != EOF) {
    char *token = strtok(frase, ";");
    parte = 0;
    while (token != NULL && linha <= tam) {
      switch (parte) {
      case 0: /*pergunta*/
        strcpy(matpergs[linha], token);
        break;
      case 1: /*resp1*/
        strcpy(matresp1[linha], token);
        break;
      case 2: /*resp2*/
        strcpy(matresp2[linha], token);
        break;
      case 3: /*resp3*/
        strcpy(matresp3[linha], token);
        break;
      case 4: /*resp4*/
        strcpy(matresp4[linha], token);
        break;
      case 5: /*val1*/
        matvalores[linha][0] = atoi(token);
        break;
      case 6: /*val2*/
        matvalores[linha][1] = atoi(token);
        break;
      case 7: /*val3*/
        matvalores[linha][2] = atoi(token);
        break;
      case 8: /*val4*/
        matvalores[linha][3] = atoi(token);
        break;
      }

      token = strtok(NULL, ";");
      parte++;
    }
    linha++;
  };
}

void imprimirTudo(char matpergs[][100], char matresp1[][100],
                  char matresp2[][100], char matresp3[][100],
                  char matresp4[][100], int matvalores[][4], int tam) {
  int i, j;
  for (i = 0; i < tam; i++) {
    if (matvalores[i][0] < 0)
      break;
    printf("\n\nPergunta %d: %s", i + 1, matpergs[i]);
    printf("\n\ta) %s - Valor: %d", matresp1[i], matvalores[i][0]);
    printf("\n\tb) %s - Valor: %d", matresp2[i], matvalores[i][1]);
    printf("\n\tc) %s - Valor: %d", matresp3[i], matvalores[i][2]);
    printf("\n\td) %s - Valor: %d", matresp4[i], matvalores[i][3]);
  }
}

int randomInteger(int low, int high) {
  int k;
  double d;
  srand(time(NULL));
  d = (double)rand() / ((double)RAND_MAX + 1);
  k = d * (high - low + 1);

  return low + k;
}

int repeated(int vet[], int num, int tam) {
  int i;
  for (i = 0; i < tam; i++) {
    if (vet[i] == num)
      return 1;
  }
  return 0;
}

void printvet(int vet[], int tam) {
  int i;
  printf("Valores gerados %d: ", tam);
  for (i = 0; i < tam; i++) {
    printf("[ %d ]", vet[i]);
  }
}

void generate(int vet[], int tam) {
  int i = 0, tmp;
  do {
    tmp = randomInteger(0, 19);
    if (!repeated(vet, tmp, tam)) {
      vet[i] = tmp;
      i++;
    }
  } while (i < tam);
}

int main() {

  int tam = 17;
  setlocale(LC_ALL, "Portuguese");

  // Matrizes e vetores para armazenar os dados
  char matpergs[tam][100], matresp1[tam][100], matresp2[tam][100],
      matresp3[tam][100], matresp4[tam][100];
  int matvalores[tam][4];

  inicializarDados(matvalores, tam);

  /*Esta função carrega os dados gravados no arquivo dados.txt e coloca as
   * informações nos vetores.*/
  carregarDadosArquivo(matpergs, matresp1, matresp2, matresp3, matresp4,
                       matvalores, tam);

  float n;
  char nome[30];

  printf(GRN "----------------------------------------------------------");
  printf("\n------------ Quiz: Recomendação de Escritores ------------");
  printf("\nSeja bem-vind@! Esse Quiz tem o objetivo de recomendar escritores "
         "com base em seus interesses.");

  printf("\nPara começarmos, digite o seu nome: " RESET);
  scanf("%[^\n]", nome);

  do {
    setbuf(stdin, NULL);
    while (strlen(nome) < 2 || strlen(nome) > 30) {
      setbuf(stdin, NULL);
      if (strlen(nome) < 2) {
        printf(RED "\nSeu nome precisa conter mais do que DOIS caracteres. "
                   "Digite novamente seu nome: " RESET);
        scanf("%[^\n]", nome);
      }

      if (strlen(nome) > 30) {
        printf(RED "\nSeu nome precisa conter MENOS que TRINTA caracteres. "
                   "Digite novamente seu nome: " RESET);
        scanf("%[^\n]", nome);
      }
    }

    /* 1) Pede o nome do usuário e verifica se o nome contém menos que 2
     * caracteres ou mais do que 30 caracteres. */

    printf(GRN "\n\n%s, qual modo você quer jogar?\n1. Modo Rápido (3 "
               "perguntas) \n2. Modo Completo (10 perguntas)\n" RESET,
           nome);
    scanf("%f", &n);

    while (n != 1 && n != 2) {
      printf(GRN
             "%s, digite APENAS 1 ou 2 para selecionar o modo desejado: " RESET,
             nome);
      scanf("%f", &n);
    }

    /* 2) Pergunta qual modo o usuário deseja jogar (1 para rápido e 2 para
    completo). Caso o usuário digite um valor diferente de 1 e 2 vai aparecer
    uma mensagem na tela pedindo que ele informe apenas 1 ou 2. */

    /* 3) Caso o usuário queira jogar o modo rápido ele terá de responder 3
    perguntas, cada uma com 4 respostas. Caso ele digite um valor diferente de
    1,2,3 e 4 aparecerá uma mensagem na tela*/

    // O valor padrão definindo o limite de perguntas só precisa ser mudado se
    // o usuário escolher o modo de 10 perguntas
    int perglim = 3; // limite máximo de perguntas para o modo 1
    if (n == 2) {
      perglim = 10;
    }

    // Cria e preenche um vetor de números randômicos para seres usados
    // quando selecionando a pergunta e suas possíveis respostas.
    int pergiV[perglim];
    generate(pergiV, perglim);

    // PergInd é usado para armazer os índices que vão ser usados para acessar
    // os elementos do vetor pergiV, que armazena os índices randômicos
    // das linhas onde as perguntas e suas respostas se encontram nas matrizes
    // que as contém. pergLn armazena a linha da matriz em que a pergunta está
    // contida
    int pergLn, pergInd;
    int gen, respGen[4] = {0, 0, 0, 0}; // gêneros com os quais as respostas
                                        // estão associadas
    char pergResp[3];                   // resposta dada pelo usuário

    for (pergInd = 0; pergInd < perglim; pergInd++) {
      pergLn = pergiV[pergInd] % tam;

      // imprime a pergunta e suas possíveis respostas
      printf(GRN "\n\n%s \n a) %s \n b) %s \n c) %s \n d) %s\n" RESET,
             matpergs[pergLn], matresp1[pergLn], matresp2[pergLn],
             matresp3[pergLn], matresp4[pergLn]);

      printf(MAG "Insira a sua resposta(entre a e d): " RESET);
      scanf("%2s", pergResp);

      while (pergResp[0] != 'a' && pergResp[0] != 'b' && pergResp[0] != 'c' &&
                 pergResp[0] != 'd' ||
             strlen(pergResp) != 1) {

        // limpa o buffer the caracteres inseridos pelo usuário que não foram
        // consumidos posteriormente
        char c;
        while ((c = fgetc(stdin) != '\n') && c != '\0') {
        }

        printf(RED "\nSua resposta precisa ser a, b, c ou d. Por favor, "
                   "tente novamente: " RESET);
        scanf("%2s", pergResp);
      }

      // converte o caractere inserido pelo usuário em um número inteiro entre
      // 0 e 3
      int respInteiro = (int)pergResp[0] - (int)'a';

      // Aqui pegamos o gênero com o qual a resposta dada pelo usuário para a
      // pergunta na linha respInteiro está associada. Porque as perguntas
      // iniciam a contagem do gênero a partir do valor 1, precisamos subtrair
      // 1 para que este valor possa ser usado para acessar elementos de um
      // vetor.
      gen = matvalores[pergLn][respInteiro] - 1;

      // Temos 4 gêneros. Cada resposta provê um gênero entre esses 4. Cada
      // gênero possui uma varáável no vetor respGen. O usuário responde a
      // pergunta, nós encontramos com que gênero a resposta está associada e
      // adicionamos 1 à variável em respGen contendo este gênero. No final do
      // questionário, respGen vai conter a distribuição do(s) gênero(s) com
      // o(s) qual(is) o usuário melhor se encaixa. Temos que
      // respGen[0] refere ao gênero filosofia,
      // respGen[1] refere ao gênero ciência,
      // respGen[2] refere ao gênero literatura trágica e
      // respGen[3] refere ao gênero fantasia
      respGen[gen] += 1;
    }

    // Valor contendo o índice, em respGen, do gênero com o qual o
    // usuário melhor se encaixa
    int gostaMais = 0;

    // array contendo quantas vezes acontece empate para os respectivos
    // gêneros representados pela posição no vetor. Cada índice representa um
    // gênero. Caso o número de repostas dadas para um gênero seja igual ao
    // número de respostas dadas para outros gêneros, as variáveis em empate
    // respectivas ao gênero serão aumentadas em 1 para cada empate, para todos
    // os gêneros que empatam
    int empate[4] = {0, 0, 0, 0};

    int respI;
    int repeat = 0;
    //  Itera o vetor contendo a distribuição dos gêneros e identifica
    //  qual o gênero com o maior número de respostas, assim como os gêneros
    //  com um número repetido de respostas
    for (gen = 0; gen < 4; ++gen) {
      // no final do loop, gostaMais vai ser o índice em respGen do
      // Gênero com o maior número de respostas em seu favor
      if (respGen[gostaMais] < respGen[gen]) {
        gostaMais = gen;
      }

      if (respGen[gen] > 0) {
        // Descobre quantos outros gêneros contiveram o mesmo número de
        // respostas que o gênero no vetor respGen identificado pelo índice gen
        repeat = 0;
        for (respI = 0; respI < 4; respI++) {
          if (respGen[respI] == respGen[gen] && respI != gen) {
            repeat++;
          }
        }

        empate[gen] = repeat;
      }
    }

    // printvet(empate, 4);

    // Cada número se refere a um gênero. A variável gostaMais será usada para
    // decidir qual o gênero selecionado
    char genero[4][50];
    char autores[4][100];
    strcpy(genero[0], "filosofia");
    strcpy(autores[0], "Marx, Nietzsche, Aristóteles e Simone de Beauvoir");

    strcpy(genero[1], "ciência");
    strcpy(autores[1], "Newton, Stephen Hawking, Darwin e Galileu");

    strcpy(genero[2], "literatura trágica");
    strcpy(autores[2], "Shakespeare, Goethe, Lorde Byron e Machado de Assis");

    strcpy(genero[3], "fantasia");
    strcpy(autores[3], "J.K Rowling, Guimarães Rosa, Lovecraft e Tolkien");

    // Decide qual a mensagem final que deve ser impressa ao usuário

    // Se o primeiro caso passar, o usuário respondeu todas as perguntas
    // de acordo com o mesmo gênero
    if (respGen[gostaMais] == perglim) {
      printf(MAG "\n\n\nVocê é completamente aficcionado por %s, " RESET,
             genero[gostaMais]);

      printf(CYN "e aqui estão alguns autores que com certeza vão te \n"
                 "entusiasmar com o passar de cada palavra: %s.\n\n" RESET,
             autores[gostaMais]);

    } else if (empate[gostaMais] > 0) {
      // Imprime na tela os gêneros empatados que tiveram o mesmo número
      // de respostas que gostaMais
      printf(BLU "\n\n\nSeu gosto literário parece ser profundamente "
                 "intersciplinar, \n"
                 "e aqui estão algumas recomendações para saciar sua sede \n"
                 "literária por algum tempo: \n\n" RESET);

      for (gen = 0; gen < 4; gen++) {
        if (empate[gen] == empate[gostaMais]) {
          printf(MAG "%s:\n " RESET, genero[gen]);

          printf(RED "   *" RESET CYN " %s\n\n" RESET, autores[gen]);
        }
      }
    } else {
      printf(BLU
             "\n\n\nSeu gosto parece ser interdisciplinar, mas o gênero com "
             "o qual mais se identifica é %s\n" RESET,
             genero[gostaMais]);

      printf(RED "    *" MAG
                 " Alguns autores de %s para se deleitar com: %s\n" RESET,
             genero[gostaMais], autores[gostaMais]);
    }

    printf(GRN "\n%s, você gostaria de refazer o Quiz? \n1.Sim\n2.Não\n" RESET,
           nome);

    scanf("%f", &n);
    while (n != 1 && n != 2) {
      printf(RED "Digito inválido! Digite apenas 1 ou 2.\nVocê gostaria de "
                 "refazer o Quiz? \n1.Sim\nNão\n" RESET);
      scanf("%f", &n);
    }

    if (n == 2) {
      printf(GRN "%s, foi muito bom jogar com você! Até outra hora! :3\n",
             nome);
    }
  } while (n == 1);

  /* 5) É perguntado ao usuário se deseja responder o Quiz novamente (1 para Sim
  e 2 para Não). Caso o valor digitado seja diferente de 1 e 2 aparecerá uma
  mensagem na tela. */
  return 0;
}
