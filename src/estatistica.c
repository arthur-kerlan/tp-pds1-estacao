#include <math.h>
#include "estatistica.h"

//funcao recursiva de somatorio utilizada em media
float soma(float v[], int tam) {
  if (tam <= 0) return 0;

  return v[tam-1] + soma(v, tam-1);
}

//calcula media aritmetica a partir de um vetor de tipo float
//tam - tamanho do vetor
float media(float v[], int tam) {
  if (tam <= 0) return 0;
  
  return soma(v, tam) / tam;
}

//calcula variancia populacional a partir de um vetor de tipo float
//tam - tamanho do vetor
float variancia_populacional(float v[], int tam) {
  float media_v = media(v, tam);
  float soma = 0;

  //representa o somatorio de (xi - media(-1)) elevado ao quadrado
  for (int i = 0; i < tam; i++) {
    soma += (v[i] - media_v) * (v[i] - media_v);
  }

  return soma / (float) tam;
}

//calcula desvio padrao a partir de um vetor de tipo float
//tam - tamanho do vetor
float desvio_padrao(float v[], int tam) {
  return sqrtf(variancia_populacional(v, tam)); 
}
