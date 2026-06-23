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

// buffer deve ser do tipo ss/mm/aa
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
//tam - tamanho do buffer
struct Estacao* parse_esta(char *buff, int tam) {
  //Estacao possui ID,Nome,Operador,Sensor,Data,N,Media,Variancia,DesvioPadrao,Leituras
  struct Estacao *est = (struct Estacao*) malloc(sizeof(struct Estacao));

  est->id = 0;

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

  est->leituras = malloc(sizeof(int)*est->n); // vetor alocado dinamicamente

  parse_leituras(est->leituras, est->n);

  return est;
}

//mostra todos os campos de Estacao
void print_esta(struct Estacao *est) {
  printf("Nome da Estacao: %s\n", est->nome);
  printf("ID: %d\n", est->id);
  printf("Operador: %s\n", est->operador);
  printf("Sensor: %s\n", est->sensor);

  printf("Leituras:\n");
  for (int i = 0; i < est->n; i++) 
    printf("  %.3f\n", est->leituras[i]);
}

//TODO
// adicionar: isvalid_est
// adicionar: isvalid_data
