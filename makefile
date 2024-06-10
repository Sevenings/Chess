CC_LIN=gcc
CC_WIN=x86_64-w64-mingw32-gcc

OUTPUT_LIN=build/linux
OUTPUT_WIN=build/windows


client-linux:
	mkdir -p build/linux
	$(CC_LIN) -o $(OUTPUT_LIN)/client chess_client.c chess_net/chess_net.c chess_net/turn_client.c chess_engine/tabuleiro.c chess_engine/movimentos.c chess_engine/textinput.c

server-linux:
	mkdir -p build/linux
	$(CC_LIN) -o $(OUTPUT_LIN)/server chess_server.c chess_net/chess_net.c chess_net/turn_server.c chess_engine/textinput.c chess_engine/tabuleiro.c chess_engine/movimentos.c

client-win:
	mkdir -p build/windows
	$(CC_WIN) -o $(OUTPUT_WIN)/client chess_client.c chess_net/chess_net.c chess_net/turn_client.c chess_engine/tabuleiro.c chess_engine/movimentos.c chess_engine/textinput.c -lws2_32

server-win:
	mkdir -p build/windows
	$(CC_WIN) -o $(OUTPUT_WIN)/server chess_server.c chess_net/chess_net.c chess_net/turn_server.c chess_engine/textinput.c chess_engine/tabuleiro.c chess_engine/movimentos.c -lws2_32

Xadrez-dbg:
	$(CC) -o Xadrez-dbg -g chess.c

debug: Xadrez-dbg
	gdb Xadrez-dbg

all: build run

clear:
	rm build/linux/* build/windows*
