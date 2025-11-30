# Desafio WAR Estruturado (C)

Projeto pedagógico com três níveis do desafio WAR em linguagem C. Cada nível expande em complexidade e funcionalidades, demonstrando conceitos fundamentais de programação em C.

## Níveis

### 🟢 Nível Novato — Cadastro Inicial (`war_novato.c`)
- **Objetivo:** Cadastro e exibição de territórios.
- **Características:**
  - Struct `Territorio` com campos: `nome`, `cor`, `tropas`
  - Vetor estático com 5 territórios
  - Funções para cadastro via `fgets` e `sscanf` (entrada segura)
  - Exibição organizada do mapa
- **Entrada:** nome, cor e número de tropas para cada território
- **Saída:** impressão organizada dos 5 territórios

### 🔵 Nível Aventureiro — Batalhas Estratégicas (`war_aventureiro.c`)
- **Objetivo:** Sistema de batalhas interativas com alocação dinâmica.
- **Características:**
  - Alocação dinâmica com `calloc()` e liberação com `free()`
  - Função `simularAtaque()` com regras de dado (1–6)
  - Empates favorecem o atacante
  - Conquista: defensor com 0 tropas muda de cor
  - Loop interativo: escolher atacante/defensor, simular batalha, visualizar mapa atualizado
- **Entrada:** cadastro de 5 territórios, escolha de atacante/defensor
- **Saída:** resultado de cada batalha, mapa atualizado em tempo real

### 🟣 Nível Mestre — Modularização + Missões (`war_mestre.c`)
- **Objetivo:** Versão totalmente modularizada com sistema de missões aleatórias.
- **Características:**
  - Funções bem separadas:
    - `inicializarTerritoriosAutomatico()` — dados fixos pré-carregados
    - `mostrarMapa()` — exibe estado do mapa
    - `simularAtaque()` — simula batalha
    - `atribuirMissao()` — gera missão aleatória
    - `verificarMissao()` — verifica cumprimento
    - `menuPrincipal()` — loop interativo com menu
  - Missões aleatórias: "Destruir o exército [cor]" ou "Conquistar 3 territórios"
  - Verificação automática de vitória ao cumprir missão
  - Menu interativo:
    - `1` — Atacar
    - `2` — Verificar Missão
    - `0` — Sair
- **Entrada:** escolhas via menu (1, 2, 0)
- **Saída:** mapa, missão, resultado de batalhas e mensagem de vitória

## Compilação

Compile cada programa com:

```bash
gcc -Wall -Wextra -std=c11 -o war_novato war_novato.c
gcc -Wall -Wextra -std=c11 -o war_aventureiro war_aventureiro.c
gcc -Wall -Wextra -std=c11 -o war_mestre war_mestre.c
```

Ou compile todos de uma vez:

```bash
gcc -Wall -Wextra -std=c11 -o war_novato war_novato.c && \
gcc -Wall -Wextra -std=c11 -o war_aventureiro war_aventureiro.c && \
gcc -Wall -Wextra -std=c11 -o war_mestre war_mestre.c
```

## Execução

Execute cada programa interativamente:

```bash
./war_novato
./war_aventureiro
./war_mestre
```

### Exemplo de Uso (Nível Novato)
```
$ ./war_novato
╔════════════════════════════════════════╗
║  BEM-VINDO AO WAR - NÍVEL NOVATO      ║
╚════════════════════════════════════════╝

=== CADASTRO DE TERRITÓRIOS ===
Digite os dados de cada território:

Território 1:
  Nome: Brasil
  Cor: Azul
  Número de tropas: 5
  
... (mais 4 territórios) ...

╔════════════════════════════════════════╗
║        ESTADO DO MAPA - WAR            ║
╚════════════════════════════════════════╝

Território 1:
  ├─ Nome:   Brasil
  ├─ Cor:    Azul
  └─ Tropas: 5
```

## Conceitos Demonstrados

✅ **Struct e tipos de dados** — definição e uso de estruturas
✅ **Vetores estáticos e dinâmicos** — alocação em stack e heap
✅ **Ponteiros** — manipulação de endereços e alocação dinâmica
✅ **calloc/free** — gerenciamento de memória
✅ **Funções** — modularização e reutilização de código
✅ **rand()/srand()** — geração de números aleatórios
✅ **Entrada/Saída segura** — `fgets()`, `sscanf()`, `scanf()`
✅ **Controle de fluxo** — loops, condicionais, switches
✅ **Enums** — tipos enumerados para tipos de missão
✅ **Boas práticas** — comentários, nomes descritivos, uso de `const`

## Estrutura de Arquivos

```
/workspaces/war-DiogoMoreschi/
├── war_novato.c        # Versão Novato
├── war_aventureiro.c   # Versão Aventureiro
├── war_mestre.c        # Versão Mestre
├── README.md           # Este arquivo
└── war_novato          # Executável compilado
```

## Notas

- Código comentado e didático para fins de aprendizado
- Todos os programas usam `srand(time(NULL))` para aleatoriedade
- Compatível com compiladores GCC/Clang modernos
- Testado em Ubuntu 24.04 LTS
- Requisitos mínimos: C99 ou C11
# 🗺️ Desafio WAR Estruturado – Conquista de Territórios

Bem-vindo ao **Desafio WAR Estruturado!** Inspirado no famoso jogo de estratégia, este desafio convida você a programar diferentes versões do jogo WAR, evoluindo seus conhecimentos em **C** à medida que avança pelos níveis **Novato**, **Aventureiro** e **Mestre**.

A empresa **MateCheck** contratou você para criar uma versão estruturada do WAR. Cada nível propõe novas funcionalidades, conceitos e desafios de programação. **Você escolhe por onde começar!**

---

## 🧩 Nível Novato: Cadastro Inicial dos Territórios

### 🎯 Objetivo

- Criar uma `struct` chamada `Territorio`.
- Usar um **vetor estático de 5 elementos** para armazenar os territórios.
- Cadastrar os dados de cada território: **Nome**, **Cor do Exército**, e **Número de Tropas**.
- Exibir o estado atual do mapa.

### ⚙️ Funcionalidades

- Leitura de dados pelo terminal (`fgets` e `scanf`)
- Impressão organizada dos dados de todos os territórios

### 💡 Conceitos abordados

- `struct`
- Vetor estático
- Entrada/saída com `scanf`, `fgets`, e `printf`

### 📥 Entrada

O usuário digita o nome do território, a cor do exército dominante e o número de tropas para **cada um dos 5 territórios**.

### 📤 Saída



## 🧗‍♂️ Nível Aventureiro: Batalhas Estratégicas

### 🎯 Objetivo

- Substituir o vetor estático por **alocação dinâmica com `calloc`**
- Criar uma função para **simular ataques entre dois territórios**
- Utilizar números aleatórios para representar dados de batalha

### 🆕 Novidades em relação ao Nível Novato

- Alocação dinâmica de memória com `calloc`
- Uso de **ponteiros**
- Laço interativo para o jogador escolher **territórios para atacar e defender**
- Simulação de dados de ataque e defesa com `rand()`

### ⚙️ Funcionalidades

- Cadastro dos territórios (como no Nível Novato)
- Fase de ataque com:
  - Escolha de atacante e defensor
  - Dados de ataque/defesa
  - Lógica:
    - Se atacante vence → defensor perde 1 tropa
    - Se defensor perde todas → território é conquistado
    - Empates favorecem o atacante

### 💡 Conceitos abordados

- Ponteiros
- `calloc` / `free`
- Aleatoriedade com `rand()` / `srand()`
- Funções para modularização

### 📥 Entrada

- Território **atacante** (1 a 5)
- Território **defensor** (1 a 5)

### 📤 Saída

Exibição do resultado da batalha, dados sorteados e mudanças no mapa.



## 🧠 Nível Mestre: Missões e Modularização Total

### 🎯 Objetivo

- Dividir o código em funções bem definidas
- Implementar um **sistema de missões**
- Verificar cumprimento da missão
- Aplicar **boas práticas** (uso de `const`, modularização, etc.)

### 🆕 Diferenças em relação ao Nível Aventureiro

- Modularização total em funções
- Missões aleatórias atribuídas:
  1. Destruir o exército **Verde**
  2. Conquistar **3 territórios**
- Menu interativo com opções

### ⚙️ Funcionalidades

- Inicialização automática dos territórios
- Menu principal com 3 opções:
  1. Atacar
  2. Verificar Missão
  3. Sair
- Verificação de vitória da missão

### 💡 Conceitos abordados

- Modularização
- `const` correctness
- Estruturação em múltiplas funções
- Passagem por referência

### 📥 Entrada

- Ações do jogador via menu:
  - `1` - Atacar
  - `2` - Verificar Missão
  - `0` - Sair
- Escolha de territórios para ataque

### 📤 Saída

- Mapa atualizado
- Resultados das batalhas
- Verificação da missão
- Mensagem de vitória



## 🏁 Conclusão

Com este **Desafio WAR Estruturado**, você praticará fundamentos essenciais da linguagem **C** de forma **divertida e progressiva**.

Cada nível foca em um conjunto de habilidades:

- 🟢 **Novato**: `struct`, vetor, entrada/saída
- 🔵 **Aventureiro**: ponteiros, memória dinâmica, lógica de jogo
- 🟣 **Mestre**: modularização, design limpo, sistema de missões



🚀 **Boa sorte! Avance nos níveis e torne-se um mestre da programação estratégica!**

> Equipe de Ensino – MateCheck