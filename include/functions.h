#include "datatype_estacao.h"

//altera nome, operador, sensor ou data.
int editarEstacao(int tam, struct Estacao *v_est);

//exclui uma estação.
int removerEstacao(int tam, struct Estacao *v_est); 

//exibe todas as estações com suas estatísticas.
int listarEstacoes(int tam, struct Estacao *v_est);

//mostra as estações de determinado operador.
//
//tam - tamanho do vetor 
//
//funcao le do usuario o nome do operador e busca no vetor
//caso nao encontre, imprime um erro na tela
void buscarPorOperador(int tam, struct Estacao *v_est); 

//lista as leituras de uma estação que se afastam da média em mais de dois desvios-padrão (|x − x ̄| > 2σ).
int detectarAnomalias(int tam, struct Estacao *v_est); 
