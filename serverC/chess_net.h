#include <stdlib.h>
#include <string.h>

#define MESSAGE_LEN 256
#define CONTENT_LEN 253

#define OK_MSG "OkayBroMsgReceived"

typedef enum Codigo {
    END_GAME,
    YOUR_TURN,
    MY_PLAY
} Codigo;

typedef struct Message {
    Codigo codigo;
    char conteudo[CONTENT_LEN];
} Message;

// Construtor de Mensagem.
Message* newMessage(Codigo codigo, const char *conteudo);

// Verifica se o código da mensagem é o desejado.
int isMessageCode(Message* message, Codigo codigo);

// Envia uma mensagem a um socket e retorna o sucesso da operação.
int sendMessage(int socket, Codigo codigo, const char conteudo[CONTENT_LEN]);

// Espera para receber uma mensagem de um socket. Retorna a mensagem.
Message* recvMessage(int socket);

// Converte uma string para uma mensagem.
Message* stringToMessage(char *string_in);

