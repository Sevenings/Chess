OUTPUT=test_chess_net
INPUT=chess_net.c

build:
	make reset

run:
	./test


server:
	gcc -o server csocket_server.c chess_net.c

client:
	gcc -o client csocket_client.c chess_net.c

clear:
	rm server client test

test:
	gcc -o test tests_chess_net.c  chess_net.c

reset: 
	make clear
	make server
	make client
	make test
