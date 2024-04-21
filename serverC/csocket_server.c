#include <bits/sockaddr.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "chess_net.h"


char* getJogada(int player_socket);


// define the server address
struct sockaddr_in socket_address(sa_family_t family, int port, in_addr_t address) {
    struct sockaddr_in server_address;
    server_address.sin_family = family;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = address;
    return server_address;
}





void loop(int p1_socket, int p2_socket) {
    char *jogada;

    int turn = 0;   // 0 -> p1; 1 -> p2;
    do {
        // Receber jogada do jogador
        if (turn == 0) {
            jogada = getJogada(p1_socket);
            printf("Jogada player 1: %s\n", jogada);
        } else {
            jogada = getJogada(p2_socket);
            printf("Jogada player 2: %s\n", jogada);
        }

        // Trocar turno
        if (turn == 0) {
            turn = 1;
        } else {
            turn = 0;
        }
    } while (1);
}



char* getJogada(int player_socket) {
    sendMessage(player_socket, YOUR_TURN, "Sua vez de jogar\n");

    Message *resposta;
    resposta = recvMessage(player_socket);
    if (!isMessageCode(resposta, MY_PLAY)) {
        // retorna erro? 
        // pede novamente?
        printf("Resposta não é jogada\n");
    }
    printf("Jogada recebida: %s\n", resposta->conteudo);

    // Recebe a jogada
    return resposta->conteudo;
}



int main() {
    
    char p1_response_message[256] = "You are player 1!";
    char p2_response_message[256] = "You are player 2!";


    // Create the server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address = socket_address(AF_INET, 65432, INADDR_ANY);


    // Bind the server to this address
    int bind_success = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    
    // Listen for connections
    listen(server_socket, 2);


    printf("Waiting for player 1 connection...\n");
    
    // Manage client socket connection
    int p1_socket;
    p1_socket = accept(server_socket, NULL, NULL);
    
    printf("Player 1 connected!\n");

    // Send message to the client
    send(p1_socket, p1_response_message, MESSAGE_LEN, 0);


    printf("Waiting for player 2 connection...\n");

    int p2_socket;
    p2_socket = accept(server_socket, NULL, NULL);

    printf("Player 2 connected!\n");

    // Send message to the client
    send(p2_socket, p2_response_message, MESSAGE_LEN, 0);


    // Enters the game main loop
    loop(p1_socket, p2_socket);

    // Close connection
    close(server_socket);

    return 0;
}

