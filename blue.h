#include <iostream>
#include <sys/types.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
#include <unistd.h>
#include <cstring>
#define PORT 2021

bool blue_init();
void maze_send(bool** maze);
int blue_recv();
void blue_send(int x);
