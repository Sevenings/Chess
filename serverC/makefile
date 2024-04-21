OUTPUT=test_chess_net
INPUT=chess_net.c

build:
	gcc -o $(OUTPUT) $(INPUT)

run:
	./$(OUTPUT)


server:
	gcc -o server csocket_server.c chess_net.c

client:
	gcc -o client csocket_client.c chess_net.c

clear:
	rm server client

reset: 
	make clear
	make server
	make client
