build:
	gcc -o Xadrez chess.c

run:
	./Xadrez

Xadrez-dbg:
	gcc -o Xadrez-dbg -g chess.c

debug: Xadrez-dbg
	gdb Xadrez-dbg

all: build run

clear:
	rm Xadrez-dbg Xadrez
