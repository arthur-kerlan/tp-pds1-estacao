#include "datatype_estacao.h"

//todas as funcoes requisitam interativamente 
//pelo usuario informacoes a partir do stdin

// cadastra uma nova estação
//
// a funcao solicita ao usuario os seguintes campos:
// – Nome da estação;
// – Nome do operador responsável;
// – Tipo de sensor;
// – Data da coleta (dia, mes, ano);
// – Quantidade de leituras (n);
// – Valores numéricos das leituras medidas.
//
// retorna o novo tamanho do vetor v_est
int adicionarEstacao(int tam, struct Estacao *v_est[]);

//altera nome, operador, sensor ou data.
int editarEstacao(int tam, struct Estacao v_est[]);

//exclui uma estação a apartir de um dado id.
//
//caso nao haja o id especificado em v_est, retorna -1
int removerEstacao(int tam, struct Estacao *v_est[]); 

//exibe todas as estações de v_est com suas estatísticas.
int listarEstacoes(int tam, struct Estacao v_est[]);

//mostra as estações de determinado operador.
//
//funcao le do usuario o nome do operador e busca no vetor
//caso nao encontre nenhuma estacao com, imprime um erro na tela
void buscarPorOperador(int tam, struct Estacao v_est[], char *operador); 

//lista as leituras de uma estação que se afastam da média em mais de dois desvios-padrão (|x − x ̄| > 2σ).
int detectarAnomalias(int tam, struct Estacao v_est[]); 
