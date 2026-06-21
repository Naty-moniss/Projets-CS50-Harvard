#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do paciente com foco em métricas de diagnóstico
typedef struct {
    int id;
    int idade;
    int dias_espera_diagnostico; // Tempo decorrido desde os primeiros sintomas/exames
    int estadiamento_clinico;    // Grau do tumor (1 a 4) segundo o padrão médico
    float score_urgencia;        // Calculado pelo algoritmo
    char status_prioridade[20];   // "CRÍTICO", "ALERTA" ou "ESTÁVEL"
} Paciente;

// Função que calcula o score ponderado de urgência baseado em dados clínicos
void calcular_score_urgencia(Paciente *p) {
    float score = 0.0;

    // Fator 1: Idade Geriátrica Avançada (Maior vulnerabilidade clínica)
    if (p->idade >= 75) {
        score += 30.0;
    } else if (p->idade >= 60) {
        score += 15.0;
    }

    // Fator 2: Atraso no Diagnóstico (Foco na eficiência de tempo)
    if (p->dias_espera_diagnostico > 60) {
        score += 40.0; 
    } else if (p->dias_espera_diagnostico > 30) {
        score += 20.0;
    }

    // Fator 3: Gravidade do Estadiamento Clínico Atual
    if (p->estadiamento_clinico >= 3) {
        score += 30.0;
    } else if (p->estadiamento_clinico == 2) {
        score += 10.0;
    }

    p->score_urgencia = score;

    if (score >= 65.0) {
        strcpy(p->status_prioridade, "CRÍTICO");
    } else if (score >= 35.0) {
        strcpy(p->status_prioridade, "ALERTA");
    } else {
        strcpy(p->status_prioridade, "ESTÁVEL");
    }
}

int main() {
    int total_pacientes = 5;
    
    Paciente fila_pacientes[5] = {
        {1, 74, 85, 2, 0.0, ""}, 
        {2, 42, 15, 1, 0.0, ""}, 
        {3, 81, 40, 3, 0.0, ""}, 
        {4, 67, 20, 1, 0.0, ""}, 
        {5, 61, 95, 4, 0.0, ""}  
    };

    // Criando o arquivo de exportação de dados médicos
    FILE *arquivo = fopen("relatorio_triagem.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de relatório.\n");
        return 1;
    }

    // Print no Console
    printf("=== SISTEMA DE ANÁLISE DE TRIAGEM ONCO-GERIÁTRICA ===\n\n");
    printf("ID\tIdade\tEspera(Dias)\tEstágio\tScore\tStatus\n");
    printf("-------------------------------------------------------------\n");

    // Print no Arquivo (.txt) em Francês
    fprintf(arquivo, "=== RAPPORT DE TRIAGE ONCO-GÉRIATRIQUE (MOCK DATA) ===\n\n");
    fprintf(arquivo, "ID\tAGE\tATTENTE(JOURS)\tSTADE\tSCORE\tSTATUS\n");
    fprintf(arquivo, "-------------------------------------------------------------\n");

    for (int i = 0; i < total_pacientes; i++) {
        calcular_score_urgencia(&fila_pacientes[i]);
        
        // Exibe no terminal
        printf("%d\t%d\t%d\t\t%d\t%.1f\t%s\n", 
               fila_pacientes[i].id, fila_pacientes[i].idade, fila_pacientes[i].dias_espera_diagnostico, 
               fila_pacientes[i].estadiamento_clinico, fila_pacientes[i].score_urgencia, fila_pacientes[i].status_prioridade);

        // Grava no arquivo
        fprintf(arquivo, "%d\t%d\t%d\t\t%d\t%.1f\t%s\n", 
               fila_pacientes[i].id, fila_pacientes[i].idade, fila_pacientes[i].dias_espera_diagnostico, 
               fila_pacientes[i].estadiamento_clinico, fila_pacientes[i].score_urgencia, fila_pacientes[i].status_prioridade);
    }

    fclose(arquivo);

    printf("\n[SUCESSO] Relatório exportado para 'relatorio_triagem.txt'!\n");
    return 0;
}