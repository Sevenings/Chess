CC=x86_64-w64-mingw32-gcc

build:
	$(CC) -o Xadrez chess.c chess_engine/movimentos.c chess_engine/tabuleiro.c chess_engine/textinput.c

run:
	./Xadrez

client:
	$(CC) -o client chess_client.c chess_net/chess_net.c chess_net/turn_client.c chess_engine/tabuleiro.c chess_engine/movimentos.c chess_engine/textinput.c

server:
	$(CC) -o server chess_server.c chess_net/chess_net.c chess_net/turn_server.c chess_engine/textinput.c chess_engine/tabuleiro.c chess_engine/movimentos.c

Xadrez-dbg:
	$(CC) -o Xadrez-dbg -g chess.c

debug: Xadrez-dbg
	gdb Xadrez-dbg

all: build run

clear:
	rm Xadrez-dbg Xadrez server client
