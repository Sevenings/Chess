#include <stdio.h>
#include "chess.h"
#include "textinput.h"

void alternaVez(Cor*);

int main() {
    Tabuleiro tabuleiro = novoTabuleiro();
    
    char entrada[6+1];
    int linhaInicial, colunaInicial, linhaFinal, colunaFinal;

    Cor corDaVez = BRANCO;

    int loop = 1;
    while (loop) {
        print_tabuleiro(tabuleiro);

        int movValido = 0;
        while (!movValido) {
            if (corDaVez == BRANCO) {
                printf("Vez das Brancas:\n");
            } else if (corDaVez == PRETO) {
                printf("Vez das Pretas:\n");
            }
            printf("Digite um movimento [ex: e2->e4]:\n");

            // Recebe a entrada
            scanf("%s", entrada);

            
            if (!notacaoValida(entrada)) {
                printf("Notação Inválida.\n");
                continue;
            }
            traduzirNotacao(entrada, &linhaInicial, &colunaInicial, &linhaFinal, &colunaFinal);

            if (corDaVez != TabuleiroGetCor(tabuleiro, linhaInicial, colunaInicial)) {
                printf("Movendo peça da cor errada!\n");
                continue;
            }
            if (!podeMover(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal)) {
                printf("Movimento Inválido!\n");
                continue;
            }
            movValido = 1;
        }
        TabuleiroMoverPeca(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
        alternaVez(&corDaVez);
    }
}

void alternaVez(Cor *corDaVez) {
    // Passa a vez para o outro jogador
    if (*corDaVez == BRANCO) {
        *corDaVez = PRETO;
    } else if (*corDaVez == PRETO) {
        *corDaVez = BRANCO;
    }
}
