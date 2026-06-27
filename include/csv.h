#include "datatype_estacao.h"

//retorna numero de entradas do arquivo CSV
int num_entries();

//grava todas as estações em arquivo CSV 
int salvarCSV(int tam, struct Estacao v_est[]);

//lê o arquivo CSV e restaura os dados para a memória.
//
//retorna no formato de array de struct Estacao
struct Estacao* carregarCSV();

