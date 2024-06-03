#include <stdlib.h>
#include <string.h>


#define MESSAGE_LEN 256
#define CONTENT_LEN 253


#define OK_MSG "OkayBroMsgReceived"


typedef enum Codigo {
    END_GAME,
    YOUR_TURN,
    MY_PLAY,
    OTHER_PLAY
} Codigo;


typedef struct Message {
    Codigo codigo;
    char conteudo[CONTENT_LEN];
} Message;


// Aloca memória de uma Mensagem.
Message* allocMessage();


// Inicia uma Mensagem
void initMessage(Message* message_in, Codigo codigo, const char *conteudo);


// Construtor de Mensagem.
Message* newMessage(Codigo codigo, const char *conteudo);


// Verifica se o código da mensagem é o desejado.
int isMessageCode(Message* message, Codigo codigo);


// Envia uma mensagem a um socket e retorna o sucesso da operação.
int sendMessage(int socket, Codigo codigo, const char conteudo[CONTENT_LEN]);


// Espera para receber uma mensagem de um socket. Retorna a mensagem.
void recvMessage(int socket, Message* output);


// Converte uma string para uma mensagem.
void stringToMessage(char *string_in, Message* output);


// Converte uma Message em String
void messageToString(Message* input, char* output);


// Se Conecta a um Server como um Cliente, retornando o socket de conexão
void connectToServer(int* pnetwork_socket, const char* address, int port);


// Sobe um server em um determinado IP e PORTA. Aguarda player 1 e 2 se conectarem.
void hostServer(int* pserver_socket, int* pp1_socket, int* pp2_socket, const char* address, int port);

