#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include "chess_net.h"


Message* newMessage(Codigo codigo, const char *conteudo) {
    // Aloca a mensagem
    Message *new_message = (Message*) malloc(sizeof(Message));

    // Insere o código
    new_message->codigo = codigo;

    // Insere o conteúdo
    strcpy(new_message->conteudo, conteudo);

    return new_message;
}


char* messageToString(Message *message_in) {
    // Aloca a string de saida
    char* string_out = (char*) malloc(sizeof(char)*MESSAGE_LEN);

    // Escreve código e conteúdo na saída
    // Se código tiver 1 dígito, preencher com um zero
    if (message_in->codigo < 10) {
        sprintf(string_out, "0%d %s", message_in->codigo, message_in->conteudo);
    } else {
        sprintf(string_out, "%d %s", message_in->codigo, message_in->conteudo);
    }

    return string_out;
}


Message* stringToMessage(char *string_in) {
    // Define as informações da mensagem
    Codigo codigo;
    char conteudo[CONTENT_LEN];
    
    // Lê o código
    sscanf(string_in, "%d", &codigo);

    // Lê o conteúdo
    char c;
    int i=3;
    while (c != '\0') {
        c = string_in[i];
        conteudo[i-3] = c;
        i++;
    }

    // Junta código e conteudo na mensagem
    Message* mensagem = newMessage(codigo, conteudo);

    return mensagem;

}


int isMessageCode(Message* message, Codigo codigo) {
    return message->codigo == codigo;
}


int sendMessage(int socket, Codigo codigo, const char *conteudo) {

    // Converte o código e conteudo para string
    Message *message = newMessage(codigo, conteudo);
    char *message_string = messageToString(message);

    // Envia a mensagem
    send(socket, message_string, sizeof(char)*MESSAGE_LEN, 0);

    // Espera o retorno de confirmação
    char retorno[MESSAGE_LEN];
    recv(socket, retorno, sizeof(char)*CONTENT_LEN, 0);

    // Retornar resultado da mensagem
    return strcmp(retorno, OK_MSG);
}


Message* recvMessage(int socket) {
    char* mensagem_string = (char*) malloc(sizeof(char) * MESSAGE_LEN);
    
    // Recebe a mensagem
    recv(socket, mensagem_string, MESSAGE_LEN*sizeof(char), 0);
    printf("[chess_net] Mensagem recebida: %s", mensagem_string);

    // Envia confirmação de que recebeu a mensagem
    send(socket, OK_MSG, sizeof(OK_MSG), 0);

    return stringToMessage(mensagem_string);
}

