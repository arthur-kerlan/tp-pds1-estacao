#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "estacao.h"
#include "functions.h"
#include "estatistica.h"

//colocar em um helper separado
void retira_new_line(char *str) {
  char *chr = strchr(str, '\n');
  if (chr != NULL)
    *strchr(str, '\n') = '\0';
}

//colocar em um helper separado
void limpa_stdin() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void swapEstacao(struct Estacao v_est[], int i, int j) {

  struct Estacao temp = v_est[i];
  v_est[i] = v_est[j];
  v_est[j] = temp;
}

// retorna o novo tamanho do vetor v_est
int adicionarEstacao(int tam, struct Estacao **v_est) {
  char date_str[MAX_DATA];

  //realocação dinamica do array v_v_est[last]
  //adiciona mais um campo - desconsiderando possiveis erros de alocacao de memoria
  *v_est = (struct Estacao*) realloc(*v_est, sizeof(struct Estacao)*(tam+1));  
  int last = tam;
  
  //variavel placeholder para facilitar manipulacao no vetor 
  struct Estacao *v_temp= &(*v_est)[last];

  //leitura e tratamento de ID
  while (1) {
    printf("Digite o numero do id da Estacao (entre %d e %d)\n", MIN_ID, MAX_ID);

    if (scanf(" %d", &v_temp->id) != 1 ||
        v_temp->id < MIN_ID || 
        v_temp->id > MAX_ID) {
      printf("ID Invalido!\n");
      limpa_stdin();
    }
    else
      break;
  }

  limpa_stdin();

  printf("Digite o nome da estacao (MAX %d caracteres)\n", MAX_NOME);
  fgets(v_temp->nome, MAX_NOME, stdin);
  
  printf("Digite o nome do operador da estacao (MAX %d caracteres)\n", MAX_OPERADOR);
  fgets(v_temp->operador, MAX_OPERADOR, stdin);

  printf("Digite o tipo de sensor da estacao (MAX %d caracteres)\n", MAX_SENSOR);
  fgets(v_temp->sensor, MAX_SENSOR, stdin);

  retira_new_line(v_temp->nome);
  retira_new_line(v_temp->operador);
  retira_new_line(v_temp->sensor);

  //leitura e tratamento de data
  while (1) {
    printf("Digite a data das leituras (data deve ser escrita na forma dd/mm/aa)\n");
    fgets(date_str, MAX_DATA, stdin);
    parser_data(&v_temp->data, date_str);

    if(!is_valid_date(v_temp->data)) {
      printf("Data Invalida!\n");
      limpa_stdin();
    }
    else
      break;
  } 

  //leitura e tratamento do numero de leituras que serao armazenadas
  while (1) {
    printf("Digite o numero de leituras (numero maior que 0 e menor que %d)\n", MAX_NUM_LEITURAS);
    scanf(" %d", &v_temp->n);
    limpa_stdin();

    if (0 >= v_temp->n || v_temp->n >= MAX_NUM_LEITURAS)
      printf("Numero de leituras Invalido!\n");
    else
      break;
  }

  v_temp->leituras = (float *) malloc(sizeof(float) * v_temp->n);

  printf("Digite as leituras feitas pelo sensor:\n");

  char buff[50];//buffer temporario para fgets
  char* end;
  //leitura e tratamento das leituras 
  for (int i = 0; i < v_temp->n; i++) {
    printf("Digite o valor %d (com casa decimais separadas por um ponto)\n", i+1); 
      while(1) {

        fgets(buff, sizeof(buff), stdin);
        v_temp->leituras[i] = strtof(buff, &end);

        //caso o endereco de end for igual ao de buff, nenhum valor foi lido
        if (end == buff)
          printf("Valor invalido! Digite um valor numero (com casa decimais separadas por um ponto)\n");
        //checagem de erro para overflow
        else if(errno == ERANGE)
          printf("Valor absoluto muito grande! \n");
        else
          break;
      }
  }

  v_temp->media = media(v_temp->leituras, v_temp->n);
  v_temp->variancia = variancia_populacional(v_temp->leituras, v_temp->n);
  v_temp->desvioPadrao = desvio_padrao(v_temp->leituras, v_temp->n);

  return tam+1;
}

//altera nome, operador, sensor ou data.
int editarEstacao(int tam, struct Estacao v_est[]) {
  //id dado pelo usuario e id dentro do vetor
  int id, v_id;
  int ff = 0;//found id flag
  char *swap_str;
  int max_swap;//tamanho max para buff swap_str

   while (1) {
    printf("Digite o numero do id da Estacao (entre %d e %d)\n", MIN_ID, MAX_ID);

    if (scanf(" %d", &id) != 1 ||
        id < MIN_ID || 
        id > MAX_ID) {
      printf("ID Invalido!\n");
      limpa_stdin();
    }
    else
      break;
  }

 for (int i = 0; i < tam; i++) 
   if (id == v_est[i].id) {
     v_id = i;
     ff = 1;
     break;
   }

if (!ff) {
   printf("Estacao vinculada ao ID %d nao encontrada!\n", id);
   return -1;
 }
  limpa_stdin();

  //tratamento de entrada de edicao do usuario
  int lf; //loop flag - quando lf == 0, saiu do loop
  while(lf){
    lf=0;
    printf("Digite N, O, ou S para alterar nome, operador ou sensor respectivamente\n");
    //define o ponteiro para str a ser editada
    switch (getchar()) {
      case 'n':
      case 'N':
        swap_str = v_est[v_id].nome;
        printf("Digite novo nome para Estacao\n");
        max_swap = MAX_NOME;
        break;
      case 'o':
      case 'O':
        swap_str = v_est[v_id].operador;
        printf("Digite novo nome para operador da Estacao\n");
        max_swap = MAX_OPERADOR;
        break;
      case 's':
      case 'S':
        swap_str = v_est[v_id].sensor;
        printf("Digite novo nome para sensor\n");
        max_swap = MAX_SENSOR;
        break;
      default:
        lf=1
        printf("Entrda invalida!\n");
    }
  }

  limpa_stdin();
  fgets(swap_str, max_swap, stdin);
  retira_new_line(swap_str);

  return 0;
}

//exclui uma estação a apartir de um dado id.
//
//caso nao haja o id especificado em v_est, retorna -1
//
//OBS: cada estacao deve possuir id unico
int removerEstacao(int tam, struct Estacao *v_est[], int id) {
 int r_id = -1;//id a ser removido
 int new_tam = tam-1; //novo tamanho do vetor

 for (int i = 0; i < tam; i++) 
   if (id == (*v_est)[i].id) {
     r_id = i;
     break;
   }
 
  //testa se o valor padrao se mante, (i.e. id nao encontrado em v_est)
 if (r_id == -1) {
   printf("Estacao vinculada ao ID %d nao encontrada \n", id);
   return tam;
 }

  //leva o Estacao a ser removida para o final e diminui o tamanho do vetor v_est
  //OBS: definitivamente nao eh a melhor maneira de essa realocacao
  for (int i = r_id; i < new_tam; i++) 
    swapEstacao(*v_est, i, i+1);

  *v_est = (struct Estacao*) realloc(*v_est, new_tam * sizeof(struct Estacao));

  return new_tam;
}

//exibe todas as estações de v_est com suas estatísticas.
int listarEstacoes(int tam, struct Estacao v_est[]);

//mostra as estações de determinado operador.
//
//funcao le do usuario o nome do operador e busca no vetor
//caso nao encontre nenhuma estacao com, imprime um erro na tela
void buscarPorOperador(int tam, struct Estacao v_est[], char *operador); 

//lista as leituras de uma estação que se afastam da média em mais de dois desvios-padrão (|x − x ̄| > 2σ).
int detectarAnomalias(int tam, struct Estacao v_est[]); 
