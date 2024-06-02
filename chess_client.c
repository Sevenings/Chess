#include <netinet/in.h>
#include <stdio.h>

#include "chess_net/chess_net.h"
#include "chess_net/turn_client.h"
#include "chess_engine/chess.h"
#include "chess_engine/textinput.h"



// O server possui uma instancia global de tabuleiro
Tabuleiro tabuleiro;


void aplicarJogada(const char* jogada) {
    // Captura as cordenadas da jogada.
    int linhaInicial, colunaInicial, linhaFinal, colunaFinal;
    traduzirNotacao(jogada, &linhaInicial, &colunaInicial, &linhaFinal, &colunaFinal);

    // Aplica a jogada no tabuleiro local.
    TabuleiroMoverPeca(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
}



// Recebe um movimento válido enviado por um player e o aplica no tabuleiro do server.
void recvJogadaOutro(const char* jogada) {
    // Aplica a jogada no próprio tabuleiro
    aplicarJogada(jogada);


    printf("\ec\e[3J");
    printf("Tabuleiro:\n");
    print_tabuleiro(tabuleiro);
    printf("Outro jogador moveu %s.\n", jogada);
}


void fazerJogada(char* jogada_realizada) {
    int linhaInicial, colunaInicial, linhaFinal, colunaFinal;
    Cor cor;
    int ehValida;

    do {
        // Lê a jogada
        printf("Sua jogada:\n");
        scanf(" %s", jogada_realizada);

        // Verifica se a notação é válida
        if (!notacaoValida(jogada_realizada)) {
            printf("Notação Invalida. ex: [e2->e4]\n");
            continue;
        }

        // Obtém os dados da jogada
        traduzirNotacao(jogada_realizada, &linhaInicial, &colunaInicial, &linhaFinal, &colunaFinal);
        cor = TabuleiroGetCor(tabuleiro, linhaInicial, linhaFinal);
        
        // Valida a jogada
        ehValida = jogadaValida(tabuleiro, cor, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
        if (!ehValida) {
            printf("Movimento Invalido!\n");
        }
    } while (!ehValida);

    // Aplica a jogada no próprio tabuleiro
    aplicarJogada(jogada_realizada);
    printf("\ec\e[3J");
    printf("Tabuleiro:\n");
    print_tabuleiro(tabuleiro);
    printf("Aguardando outro jogador...");
}


void launchChessClient(in_addr_t address, int port) {
    // Se conecta ao server especificado
    int network_socket, p1_socket, p2_socket;
    connectToServer(&network_socket, address, port);

    // Após se conectar, o tabuleiro local é carregado
    tabuleiro = novoTabuleiro();
    printf("\ec\e[3J");
    printf("Tabuleiro:\n");
    print_tabuleiro(tabuleiro);

    loopTurnClient(network_socket, recvJogadaOutro, fazerJogada);
    //
    // isValid: função que valida uma jogada.
    // fazerJogada: aplica a jogada que o player realizou.

}



int main() {
    // Parâmetros de conexão
    in_addr_t address = INADDR_ANY;
    int port = 65432;

    // Inicia o Client de Xadrez
    launchChessClient(address, port);

    return 0;
}
