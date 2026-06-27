#include "helper.h"
#include <stdio.h>
#include <string.h>

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

//troca duas Estacoes de lugar em um vetor de struct Estacao
//i e j devem ser indices em v_est
void swapEstacao(struct Estacao v_est[], int i, int j) {

  struct Estacao temp = v_est[i];
  v_est[i] = v_est[j];
  v_est[j] = temp;
}
