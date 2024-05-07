

/* Este é o loop principal de um server de turnos.
 *
 * Neste server, os jogadores enviam suas jogadas em turnos.
 *
 * 1. O P1 sempre começa. 
 * 2. Envia sua jogada. 
 * 3. Caso não seja válida, a jogada é descartada e 
 *    ele é requisitado a enviar novamente.
 * 4. Caso válida, a jogada é processada e o outro 
 *    jogador é notificado
 * 5. A vez passa para o P2.
 *
 * Entradas:
 *  p1_socket <- Socket de conexão com o P1.
 *  p2_socket <- Socket de conexão com o P2.
 *  isValid <- Função que verifica validade da jogada.
 *  applyPlay <- Função que aplica a jogada recebida
 */

void loopTurnServer(
        int p1_socket, 
        int p2_socket,
        int (*isValid)(char* jogada),
        void (*applyPlay)(int p_socket, char* jogada)
    );
