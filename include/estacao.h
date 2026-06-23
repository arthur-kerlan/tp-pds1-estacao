#include "datatype_estacao.h"

//helper (parse_esta) de atribuicao das leituras feitas em struct Estacao
//
//Necessaria haver um buffer atribuido a funcao strtok
//
//buffer deve ser do tipo [int]*[;int]
void parse_leituras(float* leituras, int n);

// buffer deve ser do tipo ss/mm/aa
// s - segundo; m - mes; a - ano
//
// caso buffer nao esteja adequado,
// retorna sem atribuir nenhum valor a data
void parser_data(struct DataLeitura *data, char* buff);

//parser de uma string para um pointeiro de Estacao
//a string idealmente eh uma linha do arquivo de persistencia
struct Estacao* parse_esta(char *buff, int tam);

//mostra todos os campos de Estacao (stdout)
void print_esta(struct Estacao *est);

//TODO
// adicionar: isvalid_est
// adicionar: isvalid_data

