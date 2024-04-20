#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>

#define MESSAGE_LEN 256
#define CONTENT_LEN 253

typedef enum Codigo {
    END_GAME,
    YOUR_TURN,
    OK,
    NOT_OK,
} Codigo;

typedef struct Message {
    Codigo codigo;
    char conteudo[MESSAGE_LEN-3];
} Message;


// Verifica se o código da mensagem é o desejado
int isMessageCode(Message* message, Codigo codigo);

// Envia uma mensagem a um socket e retorna o sucesso da operação.
int sendMessage(int socket, Codigo codigo, const char conteudo[CONTENT_LEN]);

// Espera para receber uma mensagem de um socket. Retorna a mensagem.
void recvMessage(int socket, Message *message_out);
