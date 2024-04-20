#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include "messages_constants.h"



void loop(int network_socket) {
    Message server_response;
    char message[MESSAGE_LEN];
    
    while (isMessageCode(server_response, END_GAME)) {
        recv(network_socket, server_response, MESSAGE_LEN, 0);
        printf("Recebido do Server: '%s'\n", server_response);


        switch (server_response) {
            case YOUR_TURN:
        }

        if (strcmp(server_response, YOUR_TURN) != 0) {
            printf("Não é minha vez\n");
            system("clear");
            continue;
        }

        printf("Minha vez. Escrevo minha jogada:\n");
        scanf(" %s", message);
        send(network_socket, message, MESSAGE_LEN, 0);
    }
}



int main() {

    // Create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Specify address to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(65432);
    server_address.sin_addr.s_addr = INADDR_ANY;


    // Conectar
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    // Tratamento de erros
    if (connection_status == -1) {
        printf("Erro de conexão ao endereço remoto\n\n");
    }

    // Receber resposta do servidor
    char resposta[256];
    recv(network_socket, &resposta, sizeof(resposta), 0);

    // Mostrar a resposta do servidor
    printf("Resposta do servidor: '%s'\n", resposta);

    // Enters the client main loop
    loop(network_socket);

    // Fechar o socket
    close(network_socket);
    return 0;
}

