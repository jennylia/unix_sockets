CFLAGS = -g
server:
	gcc $(CFLAGS) -o server.out server.c
client:
	gcc $(CFLAGS) -o client.out client.c
clean:
	rm *.out
