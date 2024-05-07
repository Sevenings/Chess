#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include "chess_net.h"



void loopClient(int network_socket) {
    // Aloca a memória inicial de respostas do servidor
    Message* server_response = allocMessage();
    char message[MESSAGE_LEN];
    
    do {
        // Aguarda sempre por uma mensagem do server.
        recvMessage(network_socket, server_response);
        //printf("Recebido do Server: '%s'\n", server_response->conteudo);

        if (isMessageCode(server_response, OTHER_PLAY)) {
            printf("O outro jogador jogou: %s\n", server_response->conteudo);
        } else if (isMessageCode(server_response, YOUR_TURN)) {
            printf("Minha vez. Escrevo minha jogada:\n");
            scanf(" %s", message);
            sendMessage(network_socket, MY_PLAY, message);
        }

    // Se END_GAME o jogo fecha
    } while (!isMessageCode(server_response, END_GAME));

    free(server_response);
}


int main() {
    // Parâmetros de conexão
    in_addr_t address = INADDR_ANY;
    int port = 65432;

    // Se conecta ao servidor
    int network_socket;
    connectToServer(&network_socket, address, port);

    // Começa o loop principal do cliente
    loopClient(network_socket);

    // Fechar o socket
    close(network_socket);
    return 0;
}

