//
//  socket.hpp
//


#ifndef socket_hpp
#define socket_hpp

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

struct values {
    float degrees;
    float distance;
};


struct ClientSocket {
    int sockfd;
    struct sockaddr_in serv_addr;
};


ClientSocket createConnection(char* ip, char* port);
int sendValues(ClientSocket* sock, struct values a);
void closeConnection(ClientSocket sock);


#endif /* socket_hpp */






