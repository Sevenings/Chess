#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include "chess_net.h"
#include "turn_client.h"


void loopTurnClient(
        int network_socket,
        void (*recvJogadaOutro)(const char* jogada),
        void (*fazerJogada)(char *jogada_out)
    ) {
    // Aloca a memória inicial de respostas do servidor
    Message* server_response = allocMessage();
    char message_to_server[MESSAGE_LEN];
    
    do {
        // Aguarda sempre por uma mensagem do server.
        recvMessage(network_socket, server_response);

        if (isMessageCode(server_response, OTHER_PLAY)) {
            recvJogadaOutro(server_response->conteudo);
        } else if (isMessageCode(server_response, YOUR_TURN)) {
            fazerJogada(message_to_server);
            sendMessage(network_socket, MY_PLAY, message_to_server);
        }

    // Se END_GAME o jogo fecha
    } while (!isMessageCode(server_response, END_GAME));

    free(server_response);
}


