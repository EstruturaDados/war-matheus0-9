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

// -------- MISSÃO --------

// Sorteia uma missão e copia para o destino
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// Exibe a missão apenas uma vez
void exibirMissao(char *missao) {
    printf("\n=================================\n");
    printf("MISSAO DO JOGADOR\n");
    printf("=================================\n");
    printf("%s\n", missao);
    printf("=================================\n");
}

// Verifica se a missão foi cumprida
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {
    int i;

    // Conta territórios azuis
    if (strcmp(missao, "Conquistar 3 territorios") == 0) {
        int contador = 0;

        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                contador++;
        }

        return contador >= 3;
    }

    // Soma tropas azuis
    if (strcmp(missao, "Possuir 20 tropas") == 0) {
        int total = 0;

        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                total += mapa[i].tropas;
        }

        return total >= 20;
    }

    // Todos os territórios azuis
    if (strcmp(missao, "Controlar todos os territorios azuis") == 0) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") != 0)
                return 0;
        }
        return 1;
    }

    // Todos os territórios vermelhos
    if (strcmp(missao, "Controlar todos os territorios vermelhos") == 0) {
        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") != 0)
                return 0;
        }
        return 1;
    }

    // Metade do mapa azul
    if (strcmp(missao, "Conquistar pelo menos metade do mapa") == 0) {
        int contador = 0;

        for (i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Azul") == 0)
                contador++;
        }

        return contador >= (tamanho / 2);
    }

    return 0;
}

// -------- CADASTRO --------
void cadastrar(Territorio *mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nTerritorio %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
}

// -------- EXIBIR MAPA --------
void exibirMapa(Territorio *mapa, int n) {
    printf("\n=========== MAPA ===========\n");

    for (int i = 0; i < n; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas);
    }
}

// -------- ATAQUE --------
void atacar(Territorio *atacante, Territorio *defensor) {

    printf("\nATAQUE INICIADO!\n");

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("Atacante (%s) rolou: %d\n",
           atacante->nome,
           dadoAtaque);

    printf("Defensor (%s) rolou: %d\n",
           defensor->nome,
           dadoDefesa);

    if (dadoAtaque > dadoDefesa) {

        printf("Atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;

        if (tropasTransferidas < 1)
            tropasTransferidas = 1;

        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    }
    else {

        printf("Defensor venceu!\n");

        if (atacante->tropas > 1)
            atacante->tropas--;
    }
}

// -------- LIBERAR MEMÓRIA --------
void liberarMemoria(Territorio *mapa, char *missao) {
    free(mapa);
    free(missao);

    printf("\nMemoria liberada com sucesso!\n");
}

// -------- MAIN --------
int main() {

    int n;

    printf("Quantidade de territorios: ");
    scanf("%d", &n);
    getchar();

    // Alocação dinâmica do mapa
    Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro de alocacao!\n");
        return 1;
    }

    // Vetor de missões
    char *missoes[] = {
        "Conquistar 3 territorios",
        "Possuir 20 tropas",
        "Controlar todos os territorios azuis",
        "Controlar todos os territorios vermelhos",
        "Conquistar pelo menos metade do mapa"
    };

    int totalMissoes = 5;

    // Alocação dinâmica da missão
    char *missaoJogador = (char *)malloc(100 * sizeof(char));

    if (missaoJogador == NULL) {
        printf("Erro ao alocar memoria para a missao!\n");
        free(mapa);
        return 1;
    }

    srand(time(NULL));

    // Sorteia missão
    atribuirMissao(missaoJogador, missoes, totalMissoes);

    cadastrar(mapa, n);

    // Exibe apenas uma vez
    exibirMissao(missaoJogador);

    int opcao;

    do {

        printf("\n=========== MENU ===========\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {

            exibirMapa(mapa, n);
        }

        else if (opcao == 2) {

            int a, d;

            exibirMapa(mapa, n);

            printf("\nIndice do ATACANTE: ");
            scanf("%d", &a);

            printf("Indice do DEFENSOR: ");
            scanf("%d", &d);
            getchar();

            // Validações
            if (a < 0 || a >= n || d < 0 || d >= n) {
                printf("Indice invalido!\n");
                continue;
            }

            if (a == d) {
                printf("Nao pode atacar a si mesmo!\n");
                continue;
            }

            if (strcmp(mapa[a].cor, mapa[d].cor) == 0) {
                printf("Nao pode atacar territorio da mesma cor!\n");
                continue;
            }

            if (mapa[a].tropas <= 1) {
                printf("Tropas insuficientes para atacar!\n");
                continue;
            }

            atacar(&mapa[a], &mapa[d]);

            exibirMapa(mapa, n);

            // Verifica missão automaticamente
            if (verificarMissao(missaoJogador, mapa, n)) {

                printf("\n=================================\n");
                printf("MISSAO CUMPRIDA!\n");
                printf("VOCE VENCEU O JOGO!\n");
                printf("Missao: %s\n", missaoJogador);
                printf("=================================\n");

                break;
            }
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador);

    return 0;
}
