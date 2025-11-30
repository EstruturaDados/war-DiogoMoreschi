/*
 * WAR - NÍVEL AVENTUREIRO
 * Implementação com alocação dinâmica (calloc) e batalhas estratégicas
 * Regras de batalha: atacante e defensor lançam dados (1-6), empates favorecem o atacante.
 * Se defensor chega a 0 tropas -> conquista (troca de cor do território).
 * Programa interativo: escolher atacante/defensor, simular ataque e atualizar mapa.
 * Compilar: gcc -Wall -Wextra -std=c11 -o war_aventureiro war_aventureiro.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5
#define TAM_NOME 50
#define TAM_COR 20

typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// Inicializa vetor dinâmico de territórios pedindo entrada do usuário
Territorio *inicializarTerritoriosDinamicos(size_t n) {
    Territorio *t = calloc(n, sizeof(Territorio));
    if (!t) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    char buffer[128];
    printf("=== CADASTRO DINÂMICO DE TERRITÓRIOS ===\n");
    for (size_t i = 0; i < n; ++i) {
        printf("Território %zu:\n", i + 1);

        printf("  Nome: ");
        if (fgets(t[i].nome, TAM_NOME, stdin) == NULL) strncpy(t[i].nome, "Desconhecido", TAM_NOME);
        t[i].nome[strcspn(t[i].nome, "\n")] = '\0';

        printf("  Cor: ");
        if (fgets(t[i].cor, TAM_COR, stdin) == NULL) strncpy(t[i].cor, "Neutra", TAM_COR);
        t[i].cor[strcspn(t[i].cor, "\n")] = '\0';

        printf("  Número de tropas: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            t[i].tropas = 5;
        } else {
            if (sscanf(buffer, "%d", &t[i].tropas) != 1) t[i].tropas = 5;
        }
        printf("\n");
    }
    return t;
}

// Exibe o mapa
void mostrarMapa(const Territorio *t, size_t n) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║        ESTADO DO MAPA - AVENTUREIRO    ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    for (size_t i = 0; i < n; ++i) {
        printf("Território %zu:\n", i + 1);
        printf("  ├─ Nome:   %s\n", t[i].nome);
        printf("  ├─ Cor:    %s\n", t[i].cor);
        printf("  └─ Tropas: %d\n\n", t[i].tropas);
    }
}

// Simula um ataque entre dois territórios. Retorna 1 se houve conquista, 0 caso contrário.
int simularAtaque(Territorio *atacante, Territorio *defensor) {
    int atk_roll = rand() % 6 + 1;
    int def_roll = rand() % 6 + 1;
    printf("Resultado do dado -> Atacante (%s): %d | Defensor (%s): %d\n",
           atacante->nome, atk_roll, defensor->nome, def_roll);

    if (atk_roll >= def_roll) { // empates favorecem atacante
        defensor->tropas -= 1;
        printf("Atacante vence a rodada: %s perde 1 tropa (agora %d)\n",
               defensor->nome, defensor->tropas);
        if (defensor->tropas <= 0) {
            // Conquista: troca de cor e coloca 1 tropa para o novo dono
            strncpy(defensor->cor, atacante->cor, TAM_COR - 1);
            defensor->cor[TAM_COR - 1] = '\0';
            defensor->tropas = 1;
            printf("Território %s conquistado por %s! Cor agora: %s | Tropas: %d\n",
                   defensor->nome, atacante->nome, defensor->cor, defensor->tropas);
            return 1;
        }
    } else {
        printf("Defensor vence a rodada: atacante não causa dano.\n");
    }
    return 0;
}

// Loop interativo: escolher atacante/defensor e fazer ataques
void loopBatalhas(Territorio *t, size_t n) {
    char buffer[32];
    while (1) {
        mostrarMapa(t, n);
        printf("Escolha o número do território atacante (0 para sair): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
        int a = atoi(buffer);
        if (a == 0) break;
        if (a < 1 || a > (int)n) { printf("Índice inválido. Tente novamente.\n"); continue; }

        printf("Escolha o número do território defensor (0 para cancelar): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
        int d = atoi(buffer);
        if (d == 0) continue;
        if (d < 1 || d > (int)n) { printf("Índice inválido. Tente novamente.\n"); continue; }
        if (a == d) { printf("Um território não pode atacar a si mesmo.\n"); continue; }
        if (strcmp(t[a-1].cor, t[d-1].cor) == 0) { printf("Não é possível atacar território da mesma cor.\n"); continue; }

        printf("Simulando ataque: %s (%s) -> %s (%s)\n",
               t[a-1].nome, t[a-1].cor, t[d-1].nome, t[d-1].cor);
        simularAtaque(&t[a-1], &t[d-1]);
        printf("Pressione ENTER para continuar...\n");
        fgets(buffer, sizeof(buffer), stdin);
    }
}

int main(void) {
    srand((unsigned)time(NULL));
    Territorio *territorios = inicializarTerritoriosDinamicos(NUM_TERRITORIOS);
    loopBatalhas(territorios, NUM_TERRITORIOS);
    free(territorios);
    printf("Saindo do programa Aventureiro. Obrigado por jogar!\n");
    return 0;
}

