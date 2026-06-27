#include "datatype_estacao.h"

//todas essas funcoes provalvelmente serao transportadas 
//para csv.h uma vez que nao majoritariamente helpers
//do modulo de persistencia

//helper de atribuicao das leituras feitas em struct Estacao (parse_esta)
//
//Necessaria haver um buffer atribuido a funcao strtok
//
//buffer deve ser do tipo [int]*[;int]
void parse_leituras(float* leituras, int n);

//parser de string para tipo DataLeitura
//
// buffer deve ser do tipo ss/mm/aa
// s - segundo; m - mes; a - ano
//
// caso buffer nao esteja adequado,
// retorna sem atribuir nenhum valor a data
void parser_data(struct DataLeitura *data, char* buff);

//parser de uma string para um pointeiro de Estacao
//
//a string idealmente eh uma linha do arquivo de persistencia
void parse_esta(struct Estacao *est, char *buff);

//mostra todos os campos de Estacao (stdout)
void print_esta(struct Estacao *est);

//retorna 1 se a data definida for uma data
//valida no calendario gregoriano.
//Caso contrario, retorna 0
int is_valid_date(struct DataLeitura data);

//retorna 1 se a 'est' for valida,
//caso contrario, retorna 0
//
//para est ser considerada valida, necessita-se:
//  data valida
//  ponteiro de leituras nao nulo
//  nome, operador e sensor strings nao vazias
int is_valid_est(struct Estacao *est);

//destructor para um vetor de struct Estacao 
void free_est(int tam, struct Estacao *v_est[]);
