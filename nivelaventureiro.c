#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------- STRUCT --------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// -------- CADASTRO --------
void cadastrar(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpa buffer
    }
}

// -------- EXIBIR --------
void exibir(Territorio *mapa, int n) {
    printf("\n=== MAPA ===\n");

    for (int i = 0; i < n; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// -------- ATAQUE --------
void atacar(Territorio *atacante, Territorio *defensor) {
    printf("\n⚔️ ATAQUE INICIADO!\n");

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtaque);
    printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf("✅ Atacante venceu!\n");

        // Transferência de controle
        strcpy(defensor->cor, atacante->cor);

        // Metade das tropas vai para o território conquistado
        int tropasTransferidas = atacante->tropas / 2;
        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {
        printf("❌ Defensor venceu!\n");

        // Atacante perde 1 tropa
        if (atacante->tropas > 0)
            atacante->tropas--;
    }
}

// -------- LIBERAR MEMÓRIA --------
void liberarMemoria(Territorio *mapa) {
    free(mapa);
    printf("\nMemória liberada com sucesso!\n");
}

// -------- MAIN --------
int main() {
    int n;

    printf("Quantidade de territórios: ");
    scanf("%d", &n);
    getchar();

    // Alocação dinâmica
    Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro de alocação!\n");
        return 1;
    }

    // Inicializa aleatoriedade
    srand(time(NULL));

    cadastrar(mapa, n);

    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Exibir territórios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            exibir(mapa, n);
        }

        else if (opcao == 2) {
            int a, d;

            exibir(mapa, n);

            printf("\nEscolha o índice do ATACANTE: ");
            scanf("%d", &a);

            printf("Escolha o índice do DEFENSOR: ");
            scanf("%d", &d);
            getchar();

            // -------- VALIDAÇÕES --------
            if (a < 0 || a >= n || d < 0 || d >= n) {
                printf("Índice inválido!\n");
                continue;
            }

            if (a == d) {
                printf("Não pode atacar a si mesmo!\n");
                continue;
            }

            if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
                printf("Não pode atacar território da mesma cor!\n");
                continue;
            }

            if (mapa[a].tropas <= 1) {
                printf("Tropas insuficientes para atacar!\n");
                continue;
            }

            atacar(&mapa[a], &mapa[d]);

            // Exibir após ataque
            exibir(mapa, n);
        }

    } while (opcao != 0);

    // Liberação de memória
    liberarMemoria(mapa);

    return 0;
}