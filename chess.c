#include <stdio.h>
#include "chess_engine/chess.h"
#include "chess_engine/textinput.h"

void alternaVez(Cor*);

int main() {
    // Cria um novo tabuleiro
    Tabuleiro tabuleiro = novoTabuleiro();
    
    // Aloca a memória da entrada do usuário
    char entrada[6+1];  // 6 caracteres da jogada + 1 nulo
    int linhaInicial, colunaInicial, linhaFinal, colunaFinal;

    // Brancas começam
    Cor corDaVez = BRANCO;

    int loop = 1;
    while (loop) {
        // Mostra o tabuleiro
        print_tabuleiro(tabuleiro);

        // Inicia o turno de um dos players
        int movValido = 0;
        while (!movValido) {

            // Mostra de quem é a vez
            if (corDaVez == BRANCO) {
                printf("Vez das Brancas:\n");
            } else if (corDaVez == PRETO) {
                printf("Vez das Pretas:\n");
            }
            
            // Mostra as instruções de jogar
            printf("Digite um movimento [ex: e2->e4]:\n");

            // Recebe a entrada
            scanf("%s", entrada);

            
            // Verifica a validade da entrada
            if (!notacaoValida(entrada)) {
                printf("Notação Inválida.\n");
                continue;
            }
            
            // Caso valida, capture os dados da entrada
            traduzirNotacao(entrada, &linhaInicial, &colunaInicial, &linhaFinal, &colunaFinal);

            // Verifica validade do Movimento
            // Verifica se está movendo a cor correta
            if (corDaVez != TabuleiroGetCor(tabuleiro, linhaInicial, colunaInicial)) {
                printf("Movendo peça da cor errada!\n");
                continue;
            }
            // Verifica se está movendo de acordo com as regras
            if (!podeMover(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal)) {
                printf("Movimento Inválido!\n");
                continue;
            }

            // Caso passe em todos os testes o movimento é válido
            movValido = 1;
        }

        // Realiza o movimento
        TabuleiroMoverPeca(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal);

        // Passa a vez para o próximo jogador
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
