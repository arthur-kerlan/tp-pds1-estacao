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

//TODO
// adicionar: isvalid_est
// adicionar: isvalid_data

