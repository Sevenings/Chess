#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chess_net.h"


// Aloca a memória de uma Mensagem. Retorna seu ponteiro
Message* allocMessage() {
    // Aloca a mensagem
    Message *new_message = (Message*) malloc(sizeof(Message));
    return new_message;
}


// Inicializa uma Mensagem colocando seu Código e Conteudo
void initMessage(Message* message, Codigo codigo, const char *conteudo) {
    // Insere o código
    message->codigo = codigo;

    // Insere o conteúdo
    strcpy(message->conteudo, conteudo); }


// Aloca e Inicializa uma mensagem com seu Código e Conteudo
Message* newMessage(Codigo codigo, const char *conteudo) {
    Message* newMessage = allocMessage();
    initMessage(newMessage, codigo, conteudo);
    return newMessage;
}


// Converte Mensagem para String
void messageToString(Message *message_in, char* string_out) {
    // Escreve código e conteúdo na saída
    // Se código tiver 1 dígito, preencher com um zero
    if (message_in->codigo < 10) {
        sprintf(string_out, "0%d %s", message_in->codigo, message_in->conteudo);
    } else {
        sprintf(string_out, "%d %s", message_in->codigo, message_in->conteudo);
    }
}


// Converte String para Mensagem
void stringToMessage(char *string_in, Message* output) {
    // Define as informações da mensagem
    Codigo codigo;
    char conteudo[CONTENT_LEN];
    
    // Lê o código da mensagem
    sscanf(string_in, "%d", &codigo);

    // Lê o conteudo
    char c = 'a';
    int i=3;
    while (c != '\0') {
        c = string_in[i];
        conteudo[i-3] = c;
        i++;
    }

    // Junta código e conteudo na mensagem
    initMessage(output, codigo, conteudo);
}


// Verifica se o Código da mensagem é CÓDIGO
int isMessageCode(Message* message, Codigo codigo) {
    return message->codigo == codigo;
}


// Envia uma mensagem para um Socket
int sendMessage(int socket, Codigo codigo, const char *conteudo) {

    // Converte o código e conteudo para string
    Message *message = newMessage(codigo, conteudo);
    char message_string[MESSAGE_LEN];
    messageToString(message, message_string);

    // Envia a mensagem
    send(socket, message_string, sizeof(char)*MESSAGE_LEN, 0);

    // Espera o retorno de confirmação
    char retorno[MESSAGE_LEN];
    recv(socket, retorno, sizeof(char)*CONTENT_LEN, 0);

    // Retornar resultado da mensagem
    return strcmp(retorno, OK_MSG);
}


// Anotação: trocar essa alocação dinâmica por uma definição por referência.
void recvMessage(int socket, Message* output) {
    char* mensagem_string = (char*) malloc(sizeof(char) * MESSAGE_LEN);
    
    // Recebe a mensagem
    recv(socket, mensagem_string, MESSAGE_LEN*sizeof(char), 0);
    //printf("[chess_net.recvMessage] Mensagem recebida: %s\n", mensagem_string);

    // Envia confirmação de que recebeu a mensagem
    send(socket, OK_MSG, sizeof(OK_MSG), 0);

    stringToMessage(mensagem_string, output);
}


// Se conecta ao servidor e retorna o número do socket de conexão
void connectToServer(int* pnetwork_socket, const char* address, int port) {
    
    // Protocolo de conexão com o servidor
    // Create a socket
    *pnetwork_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Specify address to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, address, &server_address.sin_addr);
    //server_address.sin_addr.s_addr = address;


    // Conectar
    int connection_status = connect(*pnetwork_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    // Tratamento de erros
    if (connection_status == -1) {
        printf("Erro de conexão ao endereço remoto\n\n");
    }

    // Formalidades do nosso protocolo de conexão
    // Receber resposta do servidor
    char resposta[256];
    recv(*pnetwork_socket, &resposta, sizeof(resposta), 0);

    // Mostrar a resposta do servidor
    printf("Resposta do servidor: '%s'\n", resposta);
}


// Sobe um server em um determinado IP e PORTA. Aguarda player 1 e 2 se conectarem.
void hostServer(int* pserver_socket, int* pp1_socket, int* pp2_socket, const char* address, int port) {
    // Mensagens de respostas de conexão
    char p1_response_message[256] = "You are player 1!";
    char p2_response_message[256] = "You are player 2!";

    // Create the server socket
    *pserver_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, address, &server_address.sin_addr);
    //server_address.sin_addr.s_addr = address;


    // Bind the server to this address
    int bind_success = bind(*pserver_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    
    // Listen for connections
    listen(*pserver_socket, 2);


    printf("Waiting for player 1 connection...\n");
    
    // Manage client socket connection
    *pp1_socket = accept(*pserver_socket, NULL, NULL);
    
    printf("Player 1 connected!\n");

    // Send message to the client
    send(*pp1_socket, p1_response_message, MESSAGE_LEN, 0);


    printf("Waiting for player 2 connection...\n");

    *pp2_socket = accept(*pserver_socket, NULL, NULL);

    printf("Player 2 connected!\n");

    // Send message to the client
    send(*pp2_socket, p2_response_message, MESSAGE_LEN, 0);
}
