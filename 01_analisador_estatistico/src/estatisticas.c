#include "estatisticas.h"

float calcular_media(float valores[], int tamanho) {
    if (tamanho == 0) return 0.0;
    float soma = 0.0;
    for (int i = 0; i < tamanho; i++) {
        soma += valores[i];
    }
    return soma / tamanho;
}

float buscar_maximo(float valores[], int tamanho) {
    if (tamanho == 0) return 0.0;
    float max = valores[0];
    for (int i = 1; i < tamanho; i++) {
        if (valores[i] > max) {
            max = valores[i];
        }
    }
    return max;
}

float buscar_minimo(float valores[], int tamanho) {
    if (tamanho == 0) return 0.0;
    float min = valores[0];
    for (int i = 1; i < tamanho; i++) {
        if (valores[i] < min) {
            min = valores[i];
        }
    }
    return min;
}