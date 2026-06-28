#include <stdio.h>
#include <stdlib.h>
#include "csv.h"
#include "estacao.h"
#include "helper.h"

#define MAX_BUFF 1150

//string do diretorio do arquivo CSV
const char *CSV_PATH = "pers/test.csv";


//retorna numero de entradas do arquivo CSV desconsiderando o cabecalho
int num_entries() {
  return num_lines(CSV_PATH)-1;
}

struct Estacao* carregarCSV() {
  char line[MAX_STR];
  char buff[MAX_BUFF];

  int n = num_entries();

  //o vetor nao eh inicializado tanto quando nao a entradas 
  //e quando nao eh possivel ler o arquivo
  if (n <= 0)
    return NULL;
  
  FILE* file = fopen(CSV_PATH, "r");

  //ignora primeira linha (cabecalho)
  fgets(buff, MAX_BUFF, file);

  struct Estacao *v_est = (struct Estacao*) malloc(sizeof(struct Estacao ) * n);

  for (int i = 0; i < n; i++) {
    fgets(buff, MAX_BUFF, file);
    parse_esta(&v_est[i], buff); 
  }

  fclose(file);

  return v_est;
}

int salvarCSV(int tam, struct Estacao v_est[]) {
  FILE* pers = fopen(CSV_PATH, "w");

  for (int i = 0; i < tam; i++) {
    if (!is_valid_est(&v_est[i]))
      return -1;
  }

  //escreve o cabecalho
  fprintf(pers,"ID,Nome,Operador,Sensor,Data,N,Media,Variancia,DesvioPadrao,Leituras\n");

  if (pers == NULL)
    return -1;

  for (int i = 0; i < tam; i++) {
    fprintf(pers, "%d,%s,%s,%s,", v_est[i].id, v_est[i].nome, v_est[i].operador, v_est[i].sensor);

    fprintf(pers, "%d/%d/%d,", v_est[i].data.dia, v_est[i].data.mes, v_est[i].data.ano);

    fprintf(pers, "%d,%.2f,%.2f,%.2f,", v_est[i].n, v_est[i].media, v_est[i].variancia, v_est[i].desvioPadrao );

    //escreve todas as leituras no final do arquivo
    for (int j= 0; j< v_est[i].n; j++) {
      fprintf(pers, "%.1f", v_est[i].leituras[j]);

      if (j != v_est[i].n-1)
        fprintf(pers, ";", v_est[i]);
    }

    fprintf(pers, "\n");
  }

  fclose(pers);

  return 0;
}

