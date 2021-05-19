#include "blue.h"

using namespace std;

int server_fd, new_socket, valreadb; 
struct sockaddr_in addressb; 
int opt = 1; 
int addrlen = sizeof(addressb); 
char bufferb[1024] = {0}; 

void blue_send(int x){
    char* c = new char[1];
    c[0] = '0' + x;
    send(new_socket,c,1,0);
}

int blue_recv(){
    char* c = new char[1];
    valreadb = read(new_socket,c,1);
    return c[0]-'0';
}

bool blue_init(){
    char *hello = "Hello from Blue"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        return false;
        //exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 2021
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        return false;
        //exit(EXIT_FAILURE); 
    } 
    addressb.sin_family = AF_INET; 
    addressb.sin_addr.s_addr = INADDR_ANY; 
    addressb.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 2021
    if (bind(server_fd, (struct sockaddr *)&addressb,  
                                 sizeof(addressb))<0) 
    { 
        perror("bind failed"); 
        return false;
        //exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        return false;
        //exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&addressb,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        return false;
        //exit(EXIT_FAILURE); 
    } 
    return true;
}

void maze_send(bool** maze){
    char* mz = new char[1600];
    int k = 0;
    for(int i=0;i<40;i++){
    	for(int j=0;j<40;j++){
    	    if(maze[i][j]){
    	    	mz[k] = '1';
    	    }else{
    	    	mz[k] = '0';
    	    }
    	    k++;
    	}
    }
    send(new_socket, mz, 1600, 0);
}
