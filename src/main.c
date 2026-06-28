#include <stdio.h>
#include <stdlib.h>
#include "csv.h"
#include "functions.h"
#include "estacao.h"
#include "helper.h"

static void print_separador(int num) {
  for (int i = 0; i < num; i++) 
    printf("=");

  printf("\n");
}

//imprime o menu de opcoes de entrada
static void printMenu() {
  print_separador(60);
  printf("Digite M para mostrar este menu\n");
  printf("Digite N para adicionar nova estacao\n");
  printf("Digite R para remover estacao pelo ID\n");
  printf("Digite E para editar estacao pelo ID\n");
  printf("Digite L para listar todas as estacoes\n");
  printf("Digite O para buscar estacoes pelo nome do operador\n");
  printf("Digite C para detectar anomalias nas leituras das estacoes\n");
  printf("Digite S para salvar alteracoes\n");
  printf("Digite X para sair.\n");
  print_separador(60);
}

int main(int argc, char *argv[])
{
  //carrega todas as estacoes do arquivo de persistencia
  int tam; //tamanho hipotetico  do arr estacoes
  int old_tam, r;//variavel de tam auxiliar
  int exit_flag = 1;//flag de saida do usuario
  struct Estacao* estacoes = carregarCSV();
  tam = num_entries();
  char buff[MAX_OPERADOR];//buffer auxiliar 
  
  printf("%*sBem Vindo!\n", 15, "");
  printMenu();

  while (exit_flag) {
    switch (getchar()) {
      case 'n': 
      case 'N':
        tam = adicionarEstacao(tam, &estacoes);
        printf("Estacao criada com sucesso!\n");
        print_separador(60);
        break;
      case 'r':
      case 'R':
        old_tam = tam;
        tam = removerEstacao(tam, &estacoes);
        if (old_tam != tam) printf("Estacao excluida com sucesso!\n");
        print_separador(60);
        break;
      case 'e':
      case 'E':
        r = editarEstacao(tam, estacoes);
        if (r == 0) printf("Estacao editada com sucesso!\n");
        print_separador(60);
        break;
      case 'l':
      case 'L':
        listarEstacoes(tam, estacoes);
        print_separador(60);
        break;
      case 'o':
      case 'O':
        printf("Digite o nome do operador da estacao (MAX %d caracteres)\n", MAX_OPERADOR);
        limpa_stdin();
        fgets(buff, MAX_OPERADOR, stdin);
        retira_new_line(buff);
        buscarPorOperador(tam, estacoes, buff);
        print_separador(60);
        break;
      case 'c':
      case 'C':
        detectarAnomalias(tam, estacoes);
        print_separador(60);
        break;
      case 's':
      case 'S':
        r = salvarCSV(tam, estacoes);
        if (r == 0) printf("Estacoes salvas!\n");
        print_separador(60);
        break;
      case 'm':
      case 'M':
        printMenu();
        break;
      case 'x':
      case 'X':
        exit_flag = 0;
        r = salvarCSV(tam, estacoes);
        if (r == 0) printf("Estacoes salvas automaticamente!\n");
        else printf("Não foi possivel salvar alteracoes\n");
        free_est(tam, &estacoes);
        break;
      default:
        printf("Entrada invalida!\n");
      }
    limpa_stdin();
  }

  return 0;
}
