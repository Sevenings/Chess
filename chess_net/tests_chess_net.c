#include <stdio.h>
#include <sys/socket.h>
#include "chess_net.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


void alloc_test() {
    // Titulo
    printf("[ALLOC TEST]\n");

    // Teste
    Message* m = allocMessage();
    
    // Resultado
    printf("Size Message Object: %lu\n", sizeof(*m));
    printf("\n");
}


void init_message_test() {
    // Titulo
    printf("[INIT MESSAGE TEST]\n");

    // Preparação
    Message* m = allocMessage();
    
    // Teste
    initMessage(m, YOUR_TURN, "Sua vez amigão");

    // Resultado
    printf("Codigo: %d.\nConteudo: %s\n", m->codigo, m->conteudo);
    printf("\n");
}


void new_message_test() {
    // Titulo
    printf("[NEW MESSAGE TEST]\n");

    // Teste
    Message* m = newMessage(END_GAME, "Undertale");

    // Resultado
    printf("Codigo: %d.\nConteudo: %s\n", m->codigo, m->conteudo);
    printf("\n");
}


void message_to_string_test() {
    // Titulo
    printf("[MESSAGE TO STRING TEST]\n");

    // Preparação
    Message* m = newMessage(END_GAME, "Naruto");
    char s[MESSAGE_LEN];
    
    // Teste
    messageToString(m, s);

    // Resultado
    printf("String output: %s\n", s);
    printf("\n");
}


void string_to_message_test() {
    // Titulo
    printf("[STRING TO MESSAGE TEST]\n");

    // Preparação
    char input[MESSAGE_LEN] = "03 Acabou meu amigo.";
    Message* output = allocMessage();

    // Teste
    stringToMessage(input, output);

    // Resultado
    printf("Code: %d\nContent: %s\n", output->codigo, output->conteudo);
    printf("\n");
}


void is_message_code_test() {
    // Titulo
    printf("[IS MESSAGE CODE TEST]\n");

    // Preparação
    Message* m = newMessage(YOUR_TURN, "Vai, é sua");

    // Teste
    int r1 = isMessageCode(m, YOUR_TURN);
    int r2 = isMessageCode(m, END_GAME);

    // Resultado
    printf("YOUR_TURN = YOUR_TURN: %d\n", r1);
    printf("YOUR_TURN = END_GAME: %d\n", r2);
    printf("\n");
}


int main() {
    alloc_test();
    init_message_test();
    new_message_test();
    message_to_string_test();
    string_to_message_test();
    is_message_code_test();
}
