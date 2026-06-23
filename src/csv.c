#include <stdio.h>
#include <stdlib.h>
#include "csv.h"

int salvarCSV(int tam, struct Estacao *v_est) {
  FILE* pers = openf("test.csv" "w");

  //TODO
  //if (is_valid_data) para todo vetor
  //if (is_valid_est) para todo vetor

  if (pers == NULL)
    return -1;

  for (int i = 0; i < tam; i++) {
    fprintf(pers, "%d,%s,%s,%s,", v_est[i].nome, v_est[i].operador, v_est[i].sensor);

    fprintf(pers, "%d/%d/%d,", v_est[i].data.dia, v_est[i].data.mes, v_est[i].data.ano);

    fprintf(pers, "%d,%f,%f,%f", v_est[i].n, v_est[i].media, v_est[i].variancia, v_est[i].desvioPadrao );
  }

  return 1;
}


