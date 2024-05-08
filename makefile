build:
	gcc -o Xadrez chess.c chess_engine/movimentos.c chess_engine/tabuleiro.c chess_engine/textinput.c

run:
	./Xadrez

client:
	gcc -o client chess_client.c chess_net/chess_net.c chess_net/turn_client.c chess_engine/tabuleiro.c chess_engine/movimentos.c chess_engine/textinput.c

server:
	gcc -o server chess_server.c chess_net/chess_net.c chess_net/turn_server.c chess_engine/textinput.c chess_engine/tabuleiro.c chess_engine/movimentos.c

Xadrez-dbg:
	gcc -o Xadrez-dbg -g chess.c

debug: Xadrez-dbg
	gdb Xadrez-dbg

all: build run

clear:
	rm Xadrez-dbg Xadrez server client
