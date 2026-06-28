#include "datatype_estacao.h"

//troca ,caso houver, o primeiro '\n' encontrado por '\0' 
void retira_new_line(char *str);

void limpa_stdin();

//troca duas Estacoes de lugar em um vetor de struct Estacao
//i e j devem ser indices em v_est
void swapEstacao(struct Estacao v_est[], int i, int j);

//le o numero de linhas em um arquivo
//
//retorna -1 caso nao consiga ler o arquivo
int num_lines(const char* path);
