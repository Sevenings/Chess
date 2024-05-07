build:
	gcc -o Xadrez chess.c chess_engine/movimentos.c chess_engine/tabuleiro.c chess_engine/textinput.c

run:
	./Xadrez

Xadrez-dbg:
	gcc -o Xadrez-dbg -g chess.c

debug: Xadrez-dbg
	gdb Xadrez-dbg

all: build run

clear:
	rm Xadrez-dbg Xadrez
