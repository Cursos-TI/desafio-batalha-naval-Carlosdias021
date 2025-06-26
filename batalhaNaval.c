#include <stdio.h>
#include <stdbool.h> // Necessario para o tipo de dado 'bool'

// Define as constantes para o tamanho do tabuleiro e do navio
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

/*
 * @brief Inicializa um tabuleiro de Batalha Naval 10x10 com agua (valor 0).
 *
 * @param tabuleiro A matriz que representa o tabuleiro.
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Percorre cada linha e coluna do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; // Define o valor 0 para representar agua
        }
    }
}

/*
 * @brief Exibe o tabuleiro no console, mostrando agua e navios.
 *
 * @param tabuleiro A matriz que representa o tabuleiro.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Imprime o cabecalho das colunas
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d  ", j);
    }
    printf("\n");
    printf("  --------------------------------\n");

    // Percorre e imprime cada elemento do tabuleiro
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d |", i); // Imprime o numero da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d  ", tabuleiro[i][j]); // Imprime o valor da celula com espacos
        }
        printf("\n"); // Quebra de linha para a proxima linha do tabuleiro
    }
}

/*
 * @brief Tenta posicionar um navio no tabuleiro, validando os limites e sobreposicao.
 *
 * @para tabuleiro A matriz do tabuleiro.
 * @para linha_inicial A linha de inicio do navio.
 * @para coluna_inicial A coluna de inicio do navio.
 * @para tamanho O tamanho do navio.
 * @para horizontal Verdadeiro se o navio for horizontal, Falso se for vertical.
 * @return Retorna true se o navio foi posicionado com sucesso, false caso contrario.
 */
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int tamanho, bool horizontal) {
    // 1. Validar se o navio cabe no tabuleiro
    if (horizontal) {
        // Verifica se o navio horizontal excede os limites da coluna
        if (coluna_inicial + tamanho > TAMANHO_TABULEIRO) {
            printf("Erro: O navio horizontal nao cabe no tabuleiro a partir dessa posicao.\n");
            return false;
        }
    } else {
        // Verifica se o navio vertical excede os limites da linha
        if (linha_inicial + tamanho > TAMANHO_TABULEIRO) {
            printf("Erro: O navio vertical nao cabe no tabuleiro a partir dessa posicao.\n");
            return false;
        }
    }

    // 2. Validar se o navio se sobrepoe a outro
    // Percorre as posicoes que o navio ira ocupar e verifica se ja estao ocupadas
    if (horizontal) {
        for (int j = 0; j < tamanho; j++) {
            if (tabuleiro[linha_inicial][coluna_inicial + j] == NAVIO) {
                printf("Erro: Sobreposicao de navios na posicao (%d, %d).\n", linha_inicial, coluna_inicial + j);
                return false;
            }
        }
    } else { // Vertical
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha_inicial + i][coluna_inicial] == NAVIO) {
                printf("Erro: Sobreposicao de navios na posicao (%d, %d).\n", linha_inicial + i, coluna_inicial);
                return false;
            }
        }
    }

    // 3. Se a validacao passar, posiciona o navio
    if (horizontal) {
        for (int j = 0; j < tamanho; j++) {
            tabuleiro[linha_inicial][coluna_inicial + j] = NAVIO;
        }
    } else { // Vertical
        for (int i = 0; i < tamanho; i++) {
            tabuleiro[linha_inicial + i][coluna_inicial] = NAVIO;
        }
    }

    return true; // Navio posicionado com sucesso
}

int main() {
    // Declara e inicializa o tabuleiro 10x10 com agua (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // --- Posicionamento dos Navios (coordenadas fixas no codigo) ---
    // Navio Horizontal
    int linha_navio_h = 2;
    int coluna_navio_h = 1;
    // O navio horizontal ira ocupar as posicoes (2, 1), (2, 2) e (2, 3)

    // Navio Vertical
    int linha_navio_v = 4;
    int coluna_navio_v = 5;
    // O navio vertical ira ocupar as posicoes (4, 5), (5, 5) e (6, 5)

    // Tenta posicionar o primeiro navio (horizontal)
    printf("Tentando posicionar Navio Horizontal de tamanho %d em (%d, %d)...\n", TAMANHO_NAVIO, linha_navio_h, coluna_navio_h);
    if (posicionarNavio(tabuleiro, linha_navio_h, coluna_navio_h, TAMANHO_NAVIO, true)) {
        printf("Navio horizontal posicionado com sucesso!\n\n");
    } else {
        printf("Nao foi possivel posicionar o navio horizontal.\n\n");
    }

    // Tenta posicionar o segundo navio (vertical)
    printf("Tentando posicionar Navio Vertical de tamanho %d em (%d, %d)...\n", TAMANHO_NAVIO, linha_navio_v, coluna_navio_v);
    if (posicionarNavio(tabuleiro, linha_navio_v, coluna_navio_v, TAMANHO_NAVIO, false)) {
        printf("Navio vertical posicionado com sucesso!\n\n");
    } else {
        printf("Nao foi possivel posicionar o navio vertical.\n\n");
    }

    // --- Exibir o Tabuleiro Final ---
    printf("--- Tabuleiro Final ---\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
