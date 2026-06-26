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
  
  //variavel placeholder para facilitar manipulacao de vetor 
  struct Estacao* v_temp = *v_est;

  //id torna-se a posicao da estacao no vetor
  v_temp[last].id = last+1;

  printf("Digite o nome da estacao (MAX %d caracteres)\n", MAX_NOME);
  fgets(v_temp[last].nome, MAX_NOME, stdin);
  
  printf("Digite o nome do operador da estacao (MAX %d caracteres)\n", MAX_OPERADOR);
  fgets(v_temp[last].operador, MAX_OPERADOR, stdin);

  printf("Digite o tipo de sensor da estacao (MAX %d caracteres)\n", MAX_SENSOR);
  fgets(v_temp[last].sensor, MAX_SENSOR, stdin);

  retira_new_line(v_temp[last].nome);
  retira_new_line(v_temp[last].operador);
  retira_new_line(v_temp[last].sensor);

  while (1) {
    printf("Digite a data das leituras (data deve ser escrita na forma dd/mm/aa)\n");
    fgets(date_str, MAX_DATA, stdin);
    parser_data(&v_temp[last].data, date_str);

    //placeholder
    //if(is_valid_data)
    break;
  } 

  while (1) {
    printf("Digite o numero de leituras (numero maior que 0 e menor que %d)\n", MAX_NUM_LEITURAS);
    scanf(" %d", &v_temp[last].n);
    limpa_stdin();

    if (0 >= v_temp[last].n || v_temp[last].n >= MAX_NUM_LEITURAS)
      printf("Numero de leituras Invalido!\n");
    else
      break;
  }

  v_temp[last].leituras = (float *) malloc(sizeof(float) * v_temp[last].n);

  printf("Digite as leituras feitas pelo sensor:\n");

  char buff[50];//buffer temporario para fgets
  char* end;
  for (int i = 0; i < v_temp[last].n; i++) {
    printf("Digite o valor %d (com casa decimais separadas por um ponto)\n", i+1); 
      while(1) {

        fgets(buff, sizeof(buff), stdin);
        v_temp[last].leituras[i] = strtof(buff, &end);

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

  v_temp[last].media = media(v_temp[last].leituras, v_temp[last].n);
  v_temp[last].variancia = variancia_populacional(v_temp[last].leituras, v_temp[last].n);
  v_temp[last].desvioPadrao = desvio_padrao(v_temp[last].leituras, v_temp[last].n);

  return tam+1;
}

//altera nome, operador, sensor ou data.
int editarEstacao(int tam, struct Estacao v_est[]);

//exclui uma estação a apartir de um dado id.
//
//caso nao haja o id especificado em v_est, retorna -1
//
//OBS: cada estacao deve possuir id unico
int removerEstacao(int tam, struct Estacao *v_est[], int id) {
 int r_id = -1;
 int new_tam = tam-1; //novo tamanho do vetor

 for (int i = 0; i < tam; i++) 
   if (id == (*v_est)[i].id) {
     r_id = i;
     break;
   }
 
 if (r_id == -1) {
   printf("Estacao vinculada ao ID %d nao encontrada \n", id);
   return tam;
 }

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
