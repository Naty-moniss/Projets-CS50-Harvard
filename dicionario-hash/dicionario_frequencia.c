#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAMANHO_TABELA 1009
#define TAMANHO_LINHA 1024

// ==========================================
// 1. ESTRUTURAS E DEFINIÇÕES (Antigo hash_table.h)
// ==========================================

typedef struct Node {
    char *palavra;
    int frequencia;
    struct Node *next;
} Node;

typedef struct {
    Node *buckets[TAMANHO_TABELA];
    int total_palavras_unicas;
} HashTable;

// ==========================================
// 2. MÓDULO DE TRATAMENTO DE TEXTO (Parser)
// ==========================================

void normalizar_palavra(char *str) {
    if (!str) return;

    int i = 0;
    int j = 0;

    while (str[i]) {
        if (isalnum((unsigned char)str[i])) {
            str[j] = tolower((unsigned char)str[i]);
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

// ==========================================
// 3. MÓDULO DA TABELA HASH
// ==========================================

unsigned long funcao_hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TAMANHO_TABELA;
}

HashTable* criar_tabela() {
    HashTable *ht = (HashTable*) malloc(sizeof(HashTable));
    if (!ht) return NULL;

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        ht->buckets[i] = NULL;
    }
    ht->total_palavras_unicas = 0;
    return ht;
}

void inserir_ou_incrementar(HashTable *ht, const char *palavra) {
    if (!ht || !palavra) return;

    unsigned long index = funcao_hash(palavra);
    Node *atual = ht->buckets[index];

    // Verifica se a palavra já existe na lista encadeada (Colisão tratada)
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            atual->frequencia++;
            return;
        }
        atual = atual->next;
    }

    // Se não existe, cria um novo nó no início da lista
    Node *novo = (Node*) malloc(sizeof(Node));
    if (!novo) return;

    novo->palavra = strdup(palavra);
    novo->frequencia = 1;
    novo->next = ht->buckets[index];
    ht->buckets[index] = novo;

    ht->total_palavras_unicas++;
}

Node* buscar_palavra(HashTable *ht, const char *palavra) {
    if (!ht || !palavra) return NULL;

    unsigned long index = funcao_hash(palavra);
    Node *atual = ht->buckets[index];

    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0) {
            return atual;
        }
        atual = atual->next;
    }

    return NULL;
}

void liberar_tabela(HashTable *ht) {
    if (!ht) return;

    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Node *atual = ht->buckets[i];
        while (atual != NULL) {
            Node *tmp = atual;
            atual = atual->next;
            free(tmp->palavra);
            free(tmp);
        }
    }
    free(ht);
}

// ==========================================
// 4. ORDENAÇÃO (QSORT) E EXPORTAÇÃO CSV
// ==========================================

int comparar_frequencia(const void *a, const void *b) {
    Node *nodeA = *(Node**)a;
    Node *nodeB = *(Node**)b;
    
    if (nodeB->frequencia == nodeA->frequencia) {
        return strcmp(nodeA->palavra, nodeB->palavra);
    }
    return nodeB->frequencia - nodeA->frequencia;
}

void exportar_e_ordenar_csv(HashTable *ht, const char *nome_arquivo_csv) {
    if (!ht || ht->total_palavras_unicas == 0) {
        printf("Tabela vazia. Nada a exportar.\n");
        return;
    }

    Node **array_palavras = (Node**) malloc(ht->total_palavras_unicas * sizeof(Node*));
    if (!array_palavras) return;

    int index = 0;
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        Node *atual = ht->buckets[i];
        while (atual != NULL) {
            array_palavras[index++] = atual;
            atual = atual->next;
        }
    }

    // Ordenação O(N log N) via QuickSort
    qsort(array_palavras, ht->total_palavras_unicas, sizeof(Node*), comparar_frequencia);

    // Exibe o Top 5 no terminal
    printf("\n=== Top 5 Palavras Mais Frequentes ===\n");
    int limite = ht->total_palavras_unicas < 5 ? ht->total_palavras_unicas : 5;
    for (int i = 0; i < limite; i++) {
        printf("%d. %s (%d vezes)\n", i + 1, array_palavras[i]->palavra, array_palavras[i]->frequencia);
    }

    // Salva o relatório em CSV
    FILE *f_csv = fopen(nome_arquivo_csv, "w");
    if (f_csv) {
        fprintf(f_csv, "Palavra,Frequencia\n");
        for (int i = 0; i < ht->total_palavras_unicas; i++) {
            fprintf(f_csv, "%s,%d\n", array_palavras[i]->palavra, array_palavras[i]->frequencia);
        }
        fclose(f_csv);
        printf("\nRelatorio salvo com sucesso em '%s'!\n", nome_arquivo_csv);
    } else {
        printf("Erro ao criar o arquivo CSV.\n");
    }

    free(array_palavras);
}

// ==========================================
// 5. FLUXO PRINCIPAL (MAIN) E LEITURA DE ARQUIVO
// ==========================================

void processar_texto(HashTable *ht, char *texto) {
    char *token = strtok(texto, " \t\n\r");
    
    while (token != NULL) {
        normalizar_palavra(token);
        
        if (strlen(token) > 0) {
            inserir_ou_incrementar(ht, token);
        }
        
        token = strtok(NULL, " \t\n\r");
    }
}

int ler_arquivo(HashTable *ht, const char *caminho_arquivo) {
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo: %s\n", caminho_arquivo);
        return 0;
    }

    char linha[TAMANHO_LINHA];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        processar_texto(ht, linha);
    }

    fclose(arquivo);
    return 1;
}

int main(int argc, char *argv[]) {
    HashTable *ht = criar_tabela();
    char caminho_arquivo[256];

    if (argc > 1) {
        strcpy(caminho_arquivo, argv[1]);
    } else {
        printf("Digite o nome do arquivo de texto (ex: exemplo.txt): ");
        scanf("%255s", caminho_arquivo);
    }

    printf("\nLendo e processando o arquivo '%s'...\n", caminho_arquivo);

    if (ler_arquivo(ht, caminho_arquivo)) {
        printf("\n=== Processamento Concluido ===\n");
        printf("Total de palavras unicas encontradas: %d\n", ht->total_palavras_unicas);
        
        // Ordena, mostra o top 5 e exporta o CSV
        exportar_e_ordenar_csv(ht, "resultado_frequencia.csv");
    }

    liberar_tabela(ht);
    return 0;
}