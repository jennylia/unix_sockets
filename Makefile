CFLAGS = -g
server:
	gcc $(CFLAGS) -o server.out server.c

clean:
	rm *.out
