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

bool yellow_init();
bool** maze_receive();
int yellow_recv();
void yellow_send(int x);
