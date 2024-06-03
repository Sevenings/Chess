#include <stdio.h>

#include "chess_net/chess_net.h"
#include "chess_net/turn_server.h"
#include "chess_engine/chess.h"
#include "chess_engine/textinput.h"



// O server possui uma instancia global de tabuleiro
Tabuleiro tabuleiro;


// Recebe um movimento válido enviado por um player e o aplica no tabuleiro do server.
void fazerJogada(int player_socket, const char* jogada) {
    // Captura as cordenadas da jogada.
    int linhaInicial, colunaInicial, linhaFinal, colunaFinal;
    traduzirNotacao(jogada, &linhaInicial, &colunaInicial, &linhaFinal, &colunaFinal);

    // Faz a jogada no tabuleiro do server.
    TabuleiroMoverPeca(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal);

    // Debug:
    print_tabuleiro(tabuleiro);
}


// Verifica se a jogada é válida
int isValid(int turn, const char* jogada) {

    // Se a jogada estiver com o formato errado, inválida.
    if (!notacaoValida(jogada)) return 0;

    // Caso formato válido, traduz a notação
    int linhaInicial, colunaInicial, linhaFinal, colunaFinal;
    traduzirNotacao(jogada, &linhaInicial, &colunaInicial, &linhaFinal, &colunaFinal);

    // Se for a vez das Brancas e o movimento não for de Brancas, inválida.
    if (turn == 0 && TabuleiroGetCor(tabuleiro, linhaInicial, colunaInicial) != BRANCO) return 0;
    
    // Se for a vez das Pretas e o movimento não for de Pretas, inválida
    if (turn == 1 && TabuleiroGetCor(tabuleiro, linhaInicial, colunaInicial) != PRETO) return 0;

    // Sendo assim, se puder mover, então pode.
    return podeMover(tabuleiro, linhaInicial, colunaInicial, linhaFinal, colunaFinal);
}




void launchChessServer(const char* address, int port) {
    // Hostea o server no endereço de IP e porta fornecidos e 
    // aguarda pelos jogadores se conectarem
    int server_socket, p1_socket, p2_socket;
    hostServer(&server_socket, &p1_socket, &p2_socket, address, port);

    // Após os jogadores se conectarem, o tabuleiro é carregado
    tabuleiro = novoTabuleiro();

    // No caso deste server, o jogo real acontecerá nele e os
    // clientes terão acesso apenas a um espelho do jogo.
    loopTurnServer(p1_socket, p2_socket, isValid, fazerJogada);
    //
    // isValid: função que valida uma jogada.
    // fazerJogada: aplica a jogada que o player realizou.

}



int main() {

    char address[16];
    int port;

    // Digitar o Endereço e Porta onde Hospedar o Server
    printf("Chess Server\n");
    printf("Host on Ip: ");
    scanf(" %s", address);
    printf("on Port: ");
    scanf(" %d", &port);

    launchChessServer(address, port);

    return 0;
}
