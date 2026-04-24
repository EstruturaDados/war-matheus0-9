#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função para remover o '\n' do fgets
void removerQuebraLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

// Função para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct Territorio territorios[5];
    char buffer[100]; // buffer auxiliar para leitura segura

    printf("=== Cadastro de Territórios ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);

        // -------- NOME --------
        while (1) {
            printf("Digite o nome do território: ");
            fgets(buffer, sizeof(buffer), stdin);

            // Verifica se houve erro na leitura
            if (buffer[0] == '\n') {
                printf("Erro: o nome não pode estar vazio!\n");
                continue;
            }

            removerQuebraLinha(buffer);
            strncpy(territorios[i].nome, buffer, sizeof(territorios[i].nome));
            territorios[i].nome[sizeof(territorios[i].nome) - 1] = '\0';
            break;
        }

        // -------- COR --------
        while (1) {
            printf("Digite a cor do exército: ");
            fgets(buffer, sizeof(buffer), stdin);

            if (buffer[0] == '\n') {
                printf("Erro: a cor não pode estar vazia!\n");
                continue;
            }

            removerQuebraLinha(buffer);
            strncpy(territorios[i].cor, buffer, sizeof(territorios[i].cor));
            territorios[i].cor[sizeof(territorios[i].cor) - 1] = '\0';
            break;
        }
        // -------- TROPAS --------
        while (1) {
            printf("Digite a quantidade de tropas: ");
            fgets(buffer, sizeof(buffer), stdin);

            char *endptr;
            int valor = strtol(buffer, &endptr, 10);

            // Validação: verifica se é número válido
            if (endptr == buffer || *endptr != '\n') {
                printf("Erro: digite um número válido!\n");
                continue;
            }

            if (valor < 0) {
                printf("Erro: o número de tropas não pode ser negativo!\n");
                continue;
            }

            territorios[i].tropas = valor;
            break;
        }

        printf("\n");
    }

    // -------- EXIBIÇÃO --------
    printf("\n=== Territórios Cadastrados ===\n\n");

    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}