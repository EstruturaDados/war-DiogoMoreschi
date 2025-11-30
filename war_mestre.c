/*
 * WAR - NÍVEL MESTRE
 * Versão modularizada com missões aleatórias, menu principal e verificação de vitória
 * Estrutura de funções: inicializarTerritorios(), mostrarMapa(), simularAtaque(),
 * atribuirMissao(), verificarMissao(), menuPrincipal().
 * Compilar: gcc -Wall -Wextra -std=c11 -o war_mestre war_mestre.c
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

typedef enum { MISS_DESTROI_COR, MISS_CONQUISTAR_N } MissaoTipo;

typedef struct {
    MissaoTipo tipo;
    char alvo_cor[TAM_COR]; // usado se tipo == MISS_DESTROI_COR
    int alvo_n;            // usado se tipo == MISS_CONQUISTAR_N
    char jogador_cor[TAM_COR]; // cor do jogador (para missao de conquista)
} Missao;

// Inicializa territórios com dados fixos (versão mestre exige inicialização automática)
Territorio *inicializarTerritoriosAutomatico(size_t n) {
    Territorio *t = calloc(n, sizeof(Territorio));
    if (!t) { perror("calloc"); exit(EXIT_FAILURE); }

    // Dados pré-definidos (didáticos)
    strncpy(t[0].nome, "Fortaleza", TAM_NOME); strncpy(t[0].cor, "Vermelho", TAM_COR); t[0].tropas = 3;
    strncpy(t[1].nome, "Planície", TAM_NOME);   strncpy(t[1].cor, "Azul", TAM_COR);     t[1].tropas = 2;
    strncpy(t[2].nome, "Pântano", TAM_NOME);   strncpy(t[2].cor, "Verde", TAM_COR);    t[2].tropas = 4;
    strncpy(t[3].nome, "Montanha", TAM_NOME);  strncpy(t[3].cor, "Amarelo", TAM_COR);  t[3].tropas = 1;
    strncpy(t[4].nome, "Ilha", TAM_NOME);      strncpy(t[4].cor, "Roxo", TAM_COR);     t[4].tropas = 5;

    return t;
}

void mostrarMapa(const Territorio *t, size_t n) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║        ESTADO DO MAPA - MESTRE         ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    for (size_t i = 0; i < n; ++i) {
        printf("Território %zu:\n", i + 1);
        printf("  ├─ Nome:   %s\n", t[i].nome);
        printf("  ├─ Cor:    %s\n", t[i].cor);
        printf("  └─ Tropas: %d\n\n", t[i].tropas);
    }
}

int simularAtaque(Territorio *atacante, Territorio *defensor) {
    int atk_roll = rand() % 6 + 1;
    int def_roll = rand() % 6 + 1;
    printf("Dado -> %s: %d | %s: %d\n", atacante->nome, atk_roll, defensor->nome, def_roll);
    if (atk_roll >= def_roll) {
        defensor->tropas -= 1;
        printf("Atacante vence: %s perde 1 tropa (agora %d)\n", defensor->nome, defensor->tropas);
        if (defensor->tropas <= 0) {
            strncpy(defensor->cor, atacante->cor, TAM_COR - 1);
            defensor->cor[TAM_COR - 1] = '\0';
            defensor->tropas = 1;
            printf("Conquistado: %s agora pertence a %s (cor %s)\n", defensor->nome, atacante->nome, defensor->cor);
            return 1;
        }
    } else {
        printf("Defensor resiste à rodada.\n");
    }
    return 0;
}

// Atribui missão aleatória
Missao atribuirMissao(const Territorio *t, size_t n) {
    Missao m;
    // Jogador tem cor fixa para esta demo
    strncpy(m.jogador_cor, "Azul", TAM_COR);

    int tipo = rand() % 2; // 0 ou 1
    if (tipo == 0) {
        m.tipo = MISS_DESTROI_COR;
        // escolhe uma cor aleatória existente
        int idx = rand() % n;
        strncpy(m.alvo_cor, t[idx].cor, TAM_COR - 1);
        m.alvo_cor[TAM_COR - 1] = '\0';
        m.alvo_n = 0;
    } else {
        m.tipo = MISS_CONQUISTAR_N;
        m.alvo_n = 3; // conquistar 3 territórios
        m.alvo_cor[0] = '\0';
    }
    return m;
}

// Verifica se missão foi cumprida
int verificarMissao(const Missao *m, const Territorio *t, size_t n) {
    if (m->tipo == MISS_DESTROI_COR) {
        // A missão é destruir todas as tropas da cor alvo
        for (size_t i = 0; i < n; ++i) {
            if (strcmp(t[i].cor, m->alvo_cor) == 0 && t[i].tropas > 0) return 0; // ainda existe tropa
        }
        return 1; // todas as tropas da cor alvo foram zeradas
    } else if (m->tipo == MISS_CONQUISTAR_N) {
        // Contar quantos territórios pertencem ao jogador
        int cont = 0;
        for (size_t i = 0; i < n; ++i) {
            if (strcmp(t[i].cor, m->jogador_cor) == 0) cont++;
        }
        return cont >= m->alvo_n;
    }
    return 0;
}

void mostrarMissao(const Missao *m) {
    printf("--- MISSÃO ATUAL ---\n");
    if (m->tipo == MISS_DESTROI_COR) {
        printf("Destruir o exército %s\n", m->alvo_cor);
    } else if (m->tipo == MISS_CONQUISTAR_N) {
        printf("Conquistar %d territórios (cor do jogador: %s)\n", m->alvo_n, m->jogador_cor);
    }
}

// Menu principal: permite atacar, verificar missão e sair
void menuPrincipal(Territorio *t, size_t n) {
    Missao missao = atribuirMissao(t, n);
    char buffer[64];
    while (1) {
        mostrarMapa(t, n);
        mostrarMissao(&missao);
        printf("Menu:\n 1 - Atacar\n 2 - Verificar Missão\n 0 - Sair\nEscolha: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
        int opc = atoi(buffer);
        if (opc == 0) break;
        else if (opc == 1) {
            printf("Selecione número do atacante: ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
            int a = atoi(buffer);
            printf("Selecione número do defensor: ");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) break;
            int d = atoi(buffer);
            if (a < 1 || a > (int)n || d < 1 || d > (int)n || a == d) {
                printf("Índices inválidos.\n");
            } else if (strcmp(t[a-1].cor, t[d-1].cor) == 0) {
                printf("Não pode atacar mesmo dono.\n");
            } else {
                simularAtaque(&t[a-1], &t[d-1]);
            }
        } else if (opc == 2) {
            if (verificarMissao(&missao, t, n)) {
                printf("Parabéns! Missão cumprida!\n");
                break;
            } else {
                printf("Missão ainda não cumprida. Continue tentando.\n");
            }
        } else {
            printf("Opção inválida.\n");
        }
        printf("Pressione ENTER para continuar...\n");
        fgets(buffer, sizeof(buffer), stdin);
    }
}

int main(void) {
    srand((unsigned)time(NULL));
    Territorio *territorios = inicializarTerritoriosAutomatico(NUM_TERRITORIOS);
    menuPrincipal(territorios, NUM_TERRITORIOS);
    free(territorios);
    printf("Saindo do programa Mestre. Obrigado por jogar!\n");
    return 0;
}

