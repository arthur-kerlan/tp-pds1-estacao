#define MIN_ID 0
#define MAX_ID 9999
#define MAX_STR 100
#define MAX_OPERADOR 40
#define MAX_NOME 40
#define MAX_SENSOR 20
#define MAX_DATA 11
#define MAX_NUM_LEITURAS 9999

struct DataLeitura {
  int dia;
  int mes;
  int ano;
};

struct Estacao {
  int id ;
  char nome [MAX_NOME];
  char operador [MAX_OPERADOR];
  char sensor [MAX_SENSOR]; // ex .: " temperatura ", " umidade ", "pressao "
  int n; // quantidade de leituras
  float * leituras ; // vetor alocado dinamicamente
  float media ;
  float variancia ;
  float desvioPadrao ;
  struct DataLeitura data ; // data da coleta
  };

