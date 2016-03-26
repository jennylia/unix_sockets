#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "util_functions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
//The steps for a server
//1. socket 
//2. bind
//3. listen
//4. accept
//5. write/ read, in this case we just read
//6. close the fd
#define PORT 8000
int main(){
  printf("hello world, I'm starting to make my own socket programming now\n");
  int socketfd;
  //1. socket
  socketfd = socket(PF_INET, SOCK_STREAM, 0); 
  if (socketfd < 0)
    fatal("The socket failed to be created =.=\n");

  //2. Let's bind
  //however, before making this, you need to have the server_addr information setup
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET; //host byte order
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = 0; //this one is of a type in_addr (/usr/include/netinet/in.h) which is a 4 byte int
  memset(&(server_addr.sin_zero), '\0', 8); //set the char array to all 0s
  //now we are ready to bind
  int bind_stat = bind (socketfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr));
  if (bind_stat < 0)
    fatal ("failed to bind @_@\n");

  //3. Time to listen to connections comming to this server
  int listen_stat = listen (socketfd, 10); // this will queue up to 10 connections at a time
  if (listen_stat < 0)
    fatal ("failed to listen\n");

  //4. Time to accept
  //This accept will populate a new addr structure
  struct sockaddr_in client_addr;
  socklen_t sin_size = sizeof(struct sockaddr_in); 
  // Accpt usually happens inside a while loop
  while(1){
    int client_fd = accept(socketfd, (struct sockaddr * ) &client_addr, &sin_size);
    if (client_fd < 0)
      fatal ("connection closed or accept stopped working");
    printf("got a client acceptioned from %s port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    //Let us to a echo server
    //5.
    int data_len = 1;
    char* recv_buf[1024];
    while (data_len){
      data_len = recv(client_fd, recv_buf, 1024, 0); 
      int send_bytes = send(client_fd, recv_buf, data_len, 0);
      if (send_bytes < 0)
        fatal("guess there was a problem sending msg\n");

      printf("%d bytes were sent!\n", send_bytes);
    
    }
    //
    //close
    close(socketfd);
    close(client_fd);

  }  

}
