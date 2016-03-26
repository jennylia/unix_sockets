#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "util_functions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

// ip and port
// The client should act similar to a server
// 1. a fd should be created to get server information
// 2. connect () should be used to get the connection established
// 3. You can write something to the server

int main(int argc,char* argv[]){
  printf ("hello world I'm client\n");

  struct sockaddr_in server;
  int server_fd;
  
  //1. need to create the socket and get the server info
  server_fd = socket(AF_INET,SOCK_STREAM, 0);
  if (server_fd < 0)
    fatal ("didn't create the socket for server");
  if (argc < 2)
    fatal("please provide a server address and port next time");
  char input[1024];
  char output[1024];
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  server.sin_addr.s_addr = inet_addr(argv[1]);
  memset(&(server.sin_zero), '\0', 8);

  //2. time to connect
  int connect_stat = connect(server_fd, (struct sockaddr *)&server, sizeof(struct sockaddr_in));
  if (connect_stat < 0)
    fatal("connect stat failed");

  //3. time to send data
  while(1){
    char* data = "Jenny has a lil pika\n";
    fgets(input, 1024, stdin);
    int send_stat = send(server_fd, input, strlen(input), 0);
    if (send_stat < 0)
      fatal("couldn't send anything");

    int len = recv(server_fd, output, 1024, 0);
    output[len] = '\0';
    printf("%s\n", output);
  }

  close(server_fd);

}
