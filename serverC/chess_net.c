#include <stdlib.h>
#include <string.h>
#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>

#include "chess_net.h"


// Funções "privadas". Auxiliares para as funções "publicas" do Header



Message* newMessage(Codigo codigo, const char conteudo[MESSAGE_LEN-3]) {
    Message *new_message = (Message*) malloc(sizeof(Message));
    new_message->codigo = codigo;
    strcpy(new_message->conteudo, conteudo);
    return new_message;
}


void messageToString(Message *message_in, char *string_out) {
    char auxiliar[MESSAGE_LEN];

    int head = message_in->codigo;


    char body[MESSAGE_LEN-3];
    strcpy(body, message_in->conteudo);

    sprintf(auxiliar, "%d %s", head, body);

    strcpy(string_out, auxiliar);
    printf("%s", string_out);
}

void stringToMessage(char *string_in, Message *message_out);

int isMessageCode(Message* message, Codigo codigo) {
    return message->codigo == codigo;
}


int sendMessage(int socket, Codigo codigo, const char *conteudo) {

    // Converte o código e conteudo para string
    Message *message = newMessage(codigo, conteudo);
    char message_string[MESSAGE_LEN];
    messageToString(message, message_string);

    // Envia a mensagem
    send(socket, message_string, sizeof(message_string), 0);

    // Espera o retorno de confirmação
    char retorno[MESSAGE_LEN];
    recv(socket, retorno, sizeof(retorno), 0);

    // Retornar resultado da mensagem
    Message *mensagem_retorno;
    stringToMessage(retorno, mensagem_retorno);

    return isMessageCode(mensagem_retorno, OK);
}


void recvMessage(int socket, Message *message_out) {
    // Implementar
}





// Testes
