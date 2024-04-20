#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


// define the server address
struct sockaddr_in socket_address(sa_family_t family, int port, in_addr_t address) {
    struct sockaddr_in server_address;
    server_address.sin_family = family;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = address;
    return server_address;
}



int main() {

    int PORT = 65432;

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address = socket_address(AF_INET, PORT, INADDR_ANY);

    int bind_success = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    


    // Waiting for players 1 and 2.
    
    int p1_client, p2_client;
    printf("Waiting for player 1...");

    listen(server_socket, 2);

}
