# tp-pds1-estacao
Trabalho Prático da matéria de PROGRAMAÇÃO E DESENVOLVIMENTO DE SOFTWARE I - 2026.1

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
│   │   └── *csv_parse_line()*
│   ├── estacao.h
│   │   ├── parse_leituras(float* leituras, int n);
│   │   ├── parser_data(struct DataLeitura *data, char* buff);
│   │   └── *parse_esta(char *buff, int tam);
│   └── functions.h
│       ├── editarEstacao(int tam, struct Estacao *v_est);
│       ├── removerEstacao(int tam, struct Estacao *v_est); 
│       ├── listarEstacoes(int tam, struct Estacao *v_est);
│       ├── buscarPorOperador(int tam, struct Estacao *v_est); 
│       └── detectarAnomalias(int tam, struct Estacao *v_est); 
├── src/                               # Implementações (.c)
│   ├── estacao.c
│   ├── functions.c
│   ├── csv.c
│   └── main.c
├── docs/                              # Documentação
├── bin/                               # Executáveis gerados
└── README.md
```


### Organização

* **include/**: declarações de funções, tipos e constantes.
* **src/**: implementação das funcionalidades.
* **docs/**: documentação adicional.

* **include/datatype_estacao.h**: Estruturas dos tipos dados definidos.
* **include/estacao.h**: define funções/helpers para os tipos de dados definidos.
* **include/cvs.h**: funções de persistência em arquivo CSV.
* **include/functions.h**: serviços diretamente requisitados pelo usuário (as funcionalidades principais do sistema).
