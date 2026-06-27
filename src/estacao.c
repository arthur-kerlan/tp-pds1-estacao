#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estacao.h"

void parse_leituras(float* leituras, int n) {
  leituras[0] = atof(strtok(NULL, ";"));

  for (int i = 1; i < n; i++) {
    leituras[i] = atof(strtok(NULL, ";"));
  }
}

// buffer deve ser do tipo ss/mm/aaaa
// s - segundo; m - mes; a - ano
//
// caso buffer nao esteja adequado,
// retorna sem atribuir nenhum valor a data
void parser_data(struct DataLeitura *data, char* buff) {
  int dia, mes, ano;
  if (sscanf(buff, "%d/%d/%d", &dia, &mes, &ano) != 3)
    return;

  data->dia = dia;
  data->mes = mes;
  data->ano = ano;
}

//parser de uma string para um pointeiro de Estacao
//
//a string idealmente eh uma linha do arquivo de persistencia
//
//o parametro est NAO deve nulo (NULL)
void parse_esta(struct Estacao *est, char *buff) {
  //Estacao possui ID,Nome,Operador,Sensor,Data,N,Media,Variancia,DesvioPadrao,Leituras
  
  if (est == NULL) 
    return;

  est->id = atoi(strtok(buff, ","));

  char* nome = strtok(NULL, ",");
  strncpy(est->nome, nome, MAX_NOME);
  char* operador = strtok(NULL, ",");
  strncpy(est->operador, operador, MAX_OPERADOR);
  char* sensor = strtok(NULL, ",");
  strncpy(est->sensor, sensor, MAX_SENSOR);

  parser_data(&est->data, strtok(NULL, ","));

  est->n = atoi(strtok(NULL, ",")); // quantidade de leituras
  
  est->media = atof(strtok(NULL, ","));
  est->variancia = atof(strtok(NULL, ","));
  est->desvioPadrao  = atof(strtok(NULL, ","));

  est->leituras = malloc(sizeof(float)*est->n); // vetor alocado dinamicamente

  parse_leituras(est->leituras, est->n);
}

void printDataLeitura(struct DataLeitura data) {
  printf("%d/%d/%d\n", data.dia,data.mes, data.ano);
}

//mostra todos os campos de Estacao
void print_esta(struct Estacao *est) {
  printf("Nome da Estacao: %s\n", est->nome);
  printf("ID: %d\n", est->id);
  printf("Operador: %s\n", est->operador);
  printf("Sensor: %s\n", est->sensor);

  printf("Data da Leitura:");
  printDataLeitura(est->data);
  printf("Media: %.2f\n", est->media);
  printf("Variancia: %.2f\n", est->variancia);
  printf("Desvio Padrao: %.2f\n", est->desvioPadrao);

  printf("Leituras:\n");
  for (int i = 0; i < est->n; i++) 
    printf("  %.1f\n", est->leituras[i]);
}

//retorna 1 se a data definida for uma data
//valida no calendario gregoriano.
//Caso contrario, retorna 0
int is_valid_date(struct DataLeitura data) {
  //ultimo dia de cada mes
  int max_dias_mes[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  //muda o valor maximo de dias de feveiro se o ano e bissexto
  if (((data.ano %4 == 0) && (data.ano % 100 != 0)) 
  || (data.ano % 400 == 0)) 
    max_dias_mes[1] = 29;
  else 
    max_dias_mes[1] = 28;

  if(data.ano >= 1900)
    if ((data.mes >= 1) && (data.mes <= 12)) 
      if(data.dia >= 1)
        if (data.dia <= max_dias_mes[data.mes-1])
          return 1;

  return 0;
}

int is_valid_est(struct Estacao *est) {

  if (strlen(est->nome)!= 0 && 
      strlen(est->operador) != 0 && 
      strlen(est->sensor) != 0)
    if (is_valid_date(est->data))
      if (est->leituras != NULL)
        return 1;

  return 0;
}

//destructor para um vetor de struct Estacao 
//libera memoria de leituras e depois do vetor 
//É preciso ser um ponteiro de ponteiro para acessar o end. de v_est[]
void free_est(int tam, struct Estacao *v_est[]) {
  for (int i = 0; i < tam; i++) {
    free((*v_est)[i].leituras);
  }

  free(*v_est);
}
