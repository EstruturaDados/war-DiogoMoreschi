#include <stdio.h>
#include <string.h>

/* 
 * ============================================
 * NÍVEL NOVATO - WAR ESTRUTURADO
 * Cadastro Inicial e Exibição de Territórios
 * ============================================
 */

// Definir número máximo de territórios
#define NUM_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 20

/*
 * Struct Territorio: representa um território do mapa
 * - nome: identificação do território
 * - cor: cor associada ao proprietário
 * - tropas: quantidade de tropas disponíveis
 */
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

/*
 * Função: cadastrarTerritorios
 * Objetivo: permitir ao usuário cadastrar os dados de cada território
 * Parâmetros: vetor de territórios e quantidade
 * Retorno: nenhum
 */
void cadastrarTerritorios(Territorio territorios[], int quantidade) {
    printf("\n=== CADASTRO DE TERRITÓRIOS ===\n");
    printf("Digite os dados de cada território:\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        // Usar fgets para todas as entradas para evitar problemas
        // ao mesclar fgets e scanf (especialmente ao usar pipes).
        char buffer[128];

        // Cadastrar nome
        printf("  Nome: ");
        if (fgets(territorios[i].nome, TAM_NOME, stdin) == NULL) {
            strcpy(territorios[i].nome, "Desconhecido");
        } else {
            territorios[i].nome[strcspn(territorios[i].nome, "\n")] = 0;
        }

        // Cadastrar cor
        printf("  Cor: ");
        if (fgets(territorios[i].cor, TAM_COR, stdin) == NULL) {
            strcpy(territorios[i].cor, "Neutra");
        } else {
            territorios[i].cor[strcspn(territorios[i].cor, "\n")] = 0;
        }

        // Cadastrar tropas usando fgets + sscanf para entrada segura
        printf("  Número de tropas: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            territorios[i].tropas = 5;
        } else {
            if (sscanf(buffer, "%d", &territorios[i].tropas) != 1) {
                territorios[i].tropas = 5; // valor padrão em caso de falha
            }
        }
        
        printf("\n");
    }
}

/*
 * Função: exibirMapa
 * Objetivo: mostrar o estado atual de todos os territórios
 * Parâmetros: vetor de territórios e quantidade
 * Retorno: nenhum
 */
void exibirMapa(Territorio territorios[], int quantidade) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║        ESTADO DO MAPA - WAR            ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    for (int i = 0; i < quantidade; i++) {
        printf("Território %d:\n", i + 1);
        printf("  ├─ Nome:   %s\n", territorios[i].nome);
        printf("  ├─ Cor:    %s\n", territorios[i].cor);
        printf("  └─ Tropas: %d\n\n", territorios[i].tropas);
    }
}

/*
 * Função: main
 * Objetivo: fluxo principal do programa
 * Parâmetros: nenhum
 * Retorno: 0 se sucesso
 */
int main(void) {
    // Vetor estático com 5 territórios
    Territorio territorios[NUM_TERRITORIOS];
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║  BEM-VINDO AO WAR - NÍVEL NOVATO      ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    // Executar cadastro
    cadastrarTerritorios(territorios, NUM_TERRITORIOS);
    
    // Exibir mapa após cadastro
    exibirMapa(territorios, NUM_TERRITORIOS);
    
    printf("Cadastro concluído com sucesso!\n");
    
    return 0;
}
