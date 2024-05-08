


void loopTurnClient(
        int network_socket,
        void (*recvJogadaOutro)(const char* jogada),
        void (*fazerJogada)(char *jogada_out)
    );
