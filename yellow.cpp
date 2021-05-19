#include "yellow.h"

using namespace std;

struct sockaddr_in address; 
int sock = 0, valread; 
struct sockaddr_in serv_addr; 
char buffer[1024] = {0};

void yellow_send(int x){
    char* c = new char[1];
    c[0] = (char)x;
    send(sock,c,1,0);
}

int yellow_recv(){
    char* c = new char[1];
    valread = read(sock,c,1);
    return (int)c[0];
}


bool yellow_init(){
    char *hello = "Hello from Yellow";  
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        cout<<"Socket creation error"<<endl; 
        return false; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        cout<<"Invalid address/ Address not supported"<<endl; 
        return false; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        cout<<"Connection Failed"<<endl; 
        return false; 
    } 
    //send(sock , hello , strlen(hello) , 0 ); 
    //cout<<"Hello message sent"<<endl; 
    //valread = read( sock , buffer, 1024); 
    //cout<<buffer<<endl;
    return true;
}

bool** maze_receive(){
    char* cc = new char[1600];
    valread = read(sock,cc,1600);
    bool** mz = new bool*[40];
    for(int i=0;i<40;i++){
    	mz[i] = new bool[40];
    }
    int k = 0;
    for(int i=0;i<40;i++){
    	for(int j=0;j<40;j++){
    	    if(cc[k]=='1'){
    	    	mz[i][j] = true;
    	    }else{
    	    	mz[i][j] = false;
    	    }
    	    k++;
    	}
    }
    return mz;
}
