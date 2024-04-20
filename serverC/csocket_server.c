#include <bits/sockaddr.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "messages_constants.h"


void getJogada(int, char*);


// define the server address
struct sockaddr_in socket_address(sa_family_t family, int port, in_addr_t address) {
    struct sockaddr_in server_address;
    server_address.sin_family = family;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = address;
    return server_address;
}





void loop(int p1_socket, int p2_socket) {
    char response[256];

    int turn = 0;   // 0 -> p1; 1 -> p2;
    while (strncmp(response, END_RESPONSE, strlen(END_RESPONSE)) != 0) {
        if (turn == 0) {
            getJogada(p1_socket, response);
            printf("Jogada player 1: %s\n", response);
        } else {
            getJogada(p2_socket, response);
            printf("Jogada player 2: %s\n", response);
        }



        if (turn == 0) 
            turn = 1;
        else 
            turn = 0;
    }
}



void getJogada(int player_socket, char *resultado) {
    send(player_socket, YOUR_TURN, MESSAGE_LEN, 0);

    char resposta[MESSAGE_LEN];
    recv(player_socket, &resposta, MESSAGE_LEN, 0);

    strcpy(resultado, resposta);
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

