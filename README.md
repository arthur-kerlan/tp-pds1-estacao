# tp-pds1-estacao

Trabalho Prático da matéria de PROGRAMAÇÃO E DESENVOLVIMENTO DE SOFTWARE I - 2026.1

## Sistema de Monitoramento de Estaçoes Meteorológicas

Sistema que pode armazenar, editar e remover informaçoes de
Estaçoes Meteorológicas de acordo com as leituras salvas.

## Compilação

```bash
gcc -Iinclude src/main.c src/csv.c src/estacao.c src/functions.c src/estatistica.c src/helper.c -o programa -lm
```

## Funcionamento geral

Ao iniciar, o programa exibe um menu em loop. O usuário escolhe uma
opção digitando uma letra (o program aceita maíusculas e minusculas).
O programa solicita os valores necessários (nome, id, leituras, etc).
O loop se repete até o usuário escolher a opção `x` ou `X` (Sair).

## Estrutura do Projeto

```text
tp-pds1-estacao/
├── include/                           # Arquivos de cabeçalho (.h)
│   ├── datatype_estacao.h
│   │   ├── struct DataLeitura 
│   │   └── struct Estacao 
│   ├── csv.h
│   │   ├── salvarCSV(int tam, stuct Estacao *v_est);
│   │   ├── struct Estacao* carregarCSV();
│   │   └── int num_entries()
│   ├── estacao.h
│   │   ├── parse_leituras(float* leituras, int n);
│   │   ├── parser_data(struct DataLeitura *data, char* buff);
│   │   ├── int is_valid_date(struct DataLeitura data);
│   │   ├── int is_valid_est(struct Estacao *est);
│   │   ├── void free_est(int tam, struct Estacao *v_est[]);
│   │   └── void parse_esta(struct Estacao *est, char *buff);
│   └── functions.h
│   │    ├── int editarEstacao(int tam, struct Estacao *v_est);
│   │    ├── int removerEstacao(int tam, struct Estacao *v_est); 
│   │    ├── int editarEstacao(int tam, struct Estacao v_est[]
│   │    ├── int listarEstacoes(int tam, struct Estacao *v_est);
│   │    ├── void buscarPorOperador(int tam, struct Estacao v_est[], char operador[])
│   │    └── int detectarAnomalias(int tam, struct Estacao *v_est); 
│   └── estatistica.h
│   │    ├── float media(float v[], int tam);
│   │    ├── float variancia_populacional(float v[], int tam);
│   │    └── float desvio_padrao(float v[], int tam);
│   └── helper.h
│   │    ├── void retira_new_line(char *str);
│   │    ├── void swapEstacao(struct Estacao v_est[], int i, int j);
│   │    ├── void limpa_stdin();
│   │    └── int num_lines(const char* path);
├── src/                               # Implementaçoes (.c)
│   ├── estacao.c
│   ├── functions.c
│   ├── estatistica.c
│   ├── csv.c
│   ├── helper.c
│   └── main.c
├── docs/                              # Documentação
├── bin/                               # Executáveis gerados
└── README.md
```

## Organização

* **include/**: declaraçoes de funçoes, tipos e constantes.
* **src/**: implementação das funcionalidades.
* **docs/**: documentação adicional.

* **include/datatype_estacao.h**: Estruturas dos tipos dados definidos.
* **include/estacao.h**: define funçoes/helpers para os tipos de dados definidos.
* **include/cvs.h**: funçoes de persistência em arquivo CSV.
* **include/functions.h**: serviços diretamente requisitados pelo usuário
(as funcionalidades principais do sistema).
* **include/estatistica.h**: funçoes gerais de estatística
* **include/helper.h**: funçoes auxiliares gerais do sistema

## Descrição das funções

### `salvarCSV(int tam, stuct Estacao *v_est)`

Grava todas as estações em arquivo CSV.

* **Entrada**: tamanho do vetor e vetor de `struct Estacao`
* **Saída**: retorna 0 para carregamento completo e -1 caso contrario

### ``struct Estacao`* carregarCSV()`

lê o arquivo CSV e restaura os dados para a memória.

* **Entrada**: Sem entrada
* **Saída**: retorna um vetor de `struct Estacao` com todas
entradas do arquivo de persistência CSV

### `int num_entries()`

Retorna numero de entradas do arquivo CSV.

* **Entrada**: Sem entrada
* **Saída**: Retorna a quantidade de entradas do arquivo
de persistência CSV (util para tamanho do vetor de carregarCSV)

### `parse_leituras(float* leituras, int n)`

Função helper de atribuição das leituras feitas em struct estacao (parse_esta).
É Necessário haver um buffer atribuido a funcao `strtok`.

* **Entrada**: vetor de tipo float (leituras) e tamanho do vetor (n)
* **Saída**: Sem saída

### `parser_data(struct DataLeitura *data, char* buff);`

Parser de string para tipo DataLeitura.
Buffer deve ser do tipo ´ss/mm/aaaa´:

* s - segundo
* m - mes
* a - ano

* **Entrada**: struct de data (não inicializado) e string (buffer) de leitura
para parsing
* **Saída**: Sem saída

### `is_valid_date(struct DataLeitura data)`

Valida data de Struct DataLeitura

* **Entrada**: DataLeitura `data` a ser validada
* **Saída**: retorna 1 se a data definida for uma data válida no calendário gregoriano.
Caso contrario, retorna 0

### `int is_valid_est(struct Estacao *est)`

Valida estação de `struct Estacao`.
Para estação ser considerada valida, necessita-se:
  Data válida
  Ponteiro de leituras nao nulo
  Nome, operador e sensor strings não vazias

* **Entrada**: Estacao `est` a ser validada
* **Saída**: retorna 1 se for válida - segundo os críterios anteriores.
Caso contrário, retorna 0

### `void free_est(int tam, struct Estacao *v_est[])`

Destructor para um vetor de `struct Estacao`

* **Entrada**: tamanho do vetor (`int`) e vetor  de `struct Estacao`  
* **Saída**: Sem saída

### `void parse_esta(struct Estacao *est, char *buff)`

Parser de uma string para um pointeiro de Estacao.
A string idealmente eh uma linha do arquivo de persistência.

* **Entrada**: buffer de string e o ponteiro para um uma Estacao
`struct Estacao` que será inicializada
* **Saída**: Sem saída

### `int adicionarEstacao(int tam, struct Estacao *v_est[])`

Recebe interativamente informaçoes do usuário para adicinar uma
nova estação.
A funcao solicita ao usuario os seguintes campos:

* Nome da estacao;
* Nome do operador responsável;
* Tipo de sensor;
* Data da coleta (dia, mes, ano);
* Quantidade de leituras (n);
* Valores numéricos das leituras medidas.

* **Entrada**: tamanho do vetor (`int`) e ponteiro de vetor  de
`struct Estacao`  (`**struct Estacao`)
* **Saída**: retorna o novo tamanho do vetor v_est (`int`)

### `int removerEstacao(int tam, struct Estacao *v_est)`

Exclui uma estacao a partir de um id requsitado ao usuário.
Caso nao haja o id especificado em v_est, monstra um mensagem
de erro.

* **Entrada**: tamanho do vetor (`int`) e ponteiro de vetor  de
`struct Estacao`  (`**struct Estacao`)
* **Saída**: retorna o novo tamanho do vetor
v_est (`int`)

### `int editarEstacao(int tam, struct Estacao v_est[]`

altera nome, operador, sensor ou data (requsitando ao usuário).

* **Entrada**: tamanho do vetor (`int`) e vetor  de
`struct Estacao`  
* **Saída**: retorna 0 para sucesso e -1 caso contrário (`int`)

### `int listarEstacoes(int tam, struct Estacao *v_est)`

exibe todas as estacoes de  `v_est` com suas estatísticas.

* **Entrada**: tamanho do vetor (`int`) e vetor  de
`struct Estacao`

* **Saída**: retorna 0

### `void buscarPorOperador(int tam, struct Estacao v_est[], char operador[])`

Mostra as estacoes de determinado operador.
Função le do usuario o nome do operador e busca no vetor,
Caso não encontre nenhuma estacao com o operador, imprime um erro na tela.

* **Entrada**: tamanho do vetor (`int`) e vetor de
`struct Estacao`
* **Saída**: Sem saída

### `int detectarAnomalias(int tam, struct Estacao *v_est)`

Lista as leituras de uma estacao que se afastam da média em mais de dois
desvios-padrao (|x<sub>i</sub> − x<sub>m</sub>| > 2σ).

* **Entrada**: tamanho do vetor (`int`) e vetor de
`struct estacao`
* **Saída**: retorna o total de anomalias de leitura encontradas(`int`)

### `float media(float v[], int tam)`

Calcula média aritmética a partir de um vetor de tipo float.
Utiliza **Soma Recursiva**.

* **Entrada**: vetor de tipo `float` e
tamanho do vetor (`int`)
* **Saída**: retorna o valor em `float`

### `float variancia_populacional(float v[], int tam)`

Calcula variância populacional a partir de um vetor de tipo float.

* **Entrada**: vetor de tipo `float` e
tamanho do vetor (`int`)
* **Saída**: retorna o valor em `float`

### `float desvio_padrao(float v[], int tam)`

Calcula desvio padrão a partir de um vetor de tipo float

* **Entrada**: vetor de tipo `float` e
tamanho do vetor (`int`)
* **Saída**: retorna o valor em `float` (utilizando `sqrtf`)

### `void retira_new_line(char *str)`

Troca ,caso houver, o primeiro '\n' encontrado por '\0'

* **Entrada**: Recebe uma string (`char *`)
* **Saída**: Sem saída

### `void swapEstacao(struct Estacao v_est[], int i, int j)`

Troca duas Estacoes de lugar em um vetor de `struct estacao`

* **Entrada**: vetor de `struct estacao` e dois indices de v_est
 `i` e `j` de tipo `int`
* **Saída**: Sem saída.

### `void limpa_stdin()`

Limpa todos os caracteres sobressalentes em `stdin`

* **Entrada**: Sem Entrada.
* **Saída**: Sem saída.

### `int num_lines(const char* path)`

Lê o numero de linhas em um arquivo.

* **Entrada**: Recebe uma string (`char *`) de
caminho relativo para o arquivo.
* **Saída**: Retorna o numero de linhas como `int`.
Caso não consiga abrir o arquivo, retorna -1;

### `int main()`
Função principal. Controla o loop do menu, lê as opções,
solicita os valores de entrada (especificamente para buscarPorOperador), 
chama as funções correspondentes (serviços para usuário em functions)
e exibe os resultados.
* **Entrada:** interação do usuário via teclado.
* **Saída:** retorna `0` ao encerrar o programa.
