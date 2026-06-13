#include <stdio.h>
#include "estatisticas.h"

#define MAX_ELEMENTOS 100

int main() {
    float dados[MAX_ELEMENTOS];
    int quantidade;

    printf("--- Analisador de Estatisticas de Dados ---\n\n");
    printf("Quantos valores deseja inserir (maximo %d)? ", MAX_ELEMENTOS);
    
    // Validação da entrada do usuário
    if (scanf("%d", &quantidade) != 1 || quantidade <= 0 || quantidade > MAX_ELEMENTOS) {
        printf("Quantidade invalida!\n");
        return 1;
    }

    // Coleta dos dados
    for (int i = 0; i < quantidade; i++) {
        printf("Digite o valor %d: ", i + 1);
        scanf("%f", &dados[i]);
    }

    // Chamada das funções do nosso módulo customizado
    float media = calcular_media(dados, quantidade);
    float maximo = buscar_maximo(dados, quantidade);
    float minimo = buscar_minimo(dados, quantidade);

    // Exibição dos resultados com duas casas decimais
    printf("\n--- Resultados ---\n");
    printf("Media aritmetica: %.2f\n", media);
    printf("Valor maximo:     %.2f\n", maximo);
    printf("Valor minimo:     %.2f\n", minimo);

    return 0;
}