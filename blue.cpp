#include "blue.h"

using namespace std;

int server_fd, new_socket, valread; 
struct sockaddr_in address; 
int opt = 1; 
int addrlen = sizeof(address); 
char buffer[1024] = {0}; 

void blue_send(int x){
    char* c = new char[1];
    c[0] = (char)x;
    send(new_socket,c,1,0);
}

int blue_recv(){
    char* c = new char[1];
    valread = read(new_socket,c,1);
    return (int)c[0];
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
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 2021
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
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
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        return false;
        //exit(EXIT_FAILURE); 
    } 
    //valread = read( new_socket , buffer, 1024); 
    //cout<<buffer<<endl; 
    //send(new_socket , hello , strlen(hello) , 0 ); 
    //cout<<"Hello message sent"<<endl; 
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

