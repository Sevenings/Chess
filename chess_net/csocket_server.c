#include <bits/sockaddr.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "chess_net.h"


void waitJogada(int player_socket, char* jogada);


void loopServer(
        int p1_socket, 
        int p2_socket, 
        int (*isValid)(char* jogada),
        void (*applyPlay)(int p_socket, char* jogada)
    ) {
    // Aloca algumas variaveis iniciais
    char jogada[MESSAGE_LEN];

    int turn = 0;   // 0 -> p1; 1 -> p2;
    int selected_socket = p1_socket;
    do {
        // Mostra o turno atual
        printf("Turno: %d\n", turn);

        // Recebe e verifica a jogada do jogador
        do {
            // Aguarda para receber jogada do jogador
            waitJogada(selected_socket, jogada);
            printf("[Loop Server] Jogada player %d: %s\n", turn+1, jogada);
            
            // Verificar validade Jogada
        } while (isValid(jogada) != 1);

        // Caso Valida Aplica a Jogada
        applyPlay(selected_socket, jogada);

        // Divulga ao outro player qual a jogada realizada
        if (selected_socket != p1_socket) {
            sendMessage(p1_socket, OTHER_PLAY, jogada);
        } else if (selected_socket != p2_socket) {
            sendMessage(p2_socket, OTHER_PLAY, jogada);
        }

        // Trocar turno e player selecionado
        if (turn == 0) {
            turn = 1;
            selected_socket = p2_socket;
        } else {
            turn = 0;
            selected_socket = p1_socket;
        }
    } while (1);
}



void waitJogada(int player_socket, char *jogada) {
    sendMessage(player_socket, YOUR_TURN, "Sua vez de jogar");

    Message *resposta = allocMessage();
    recvMessage(player_socket, resposta);
    if (!isMessageCode(resposta, MY_PLAY)) {
        // retorna erro? 
        // pede novamente?
        printf("Resposta não é jogada\n");
    }
    //printf("[getJogada] Jogada recebida: %s\n", resposta->conteudo);

    // Recebe a jogada
    strcpy(jogada, resposta->conteudo); // Substituir strcpy
    free(resposta);
}






int main() {
    // Parâmetros de conexão
    in_addr_t address = INADDR_ANY;
    int port = 65432;

    // Sobe o server
    int server_socket, p1_socket, p2_socket;
    hostServer(&server_socket, &p1_socket, &p2_socket, address, port);

    // Enters the game main loop
    loopServer(p1_socket, p2_socket);   // APLICAR ATUALIZAÇÃO

    // Close connection
    close(server_socket);

    return 0;
}

