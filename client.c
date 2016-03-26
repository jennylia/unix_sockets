#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "util_functions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

// The client should act similar to a server
// 1. a fd should be created to get server information
// 2. connect () should be used to get the connection established
// 3. You can write something to the server

int main(){
  printf ("hello world I'm client\n");

}
