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

struct values
{
    float degrees;
    float distance;
    int quality;
};

struct ClientSocket
{
    int sockfd;
    struct sockaddr_in serv_addr;
};

ClientSocket createConnection(char *ip, char *port);
void sendValues(ClientSocket *sock, void *a, int size);
int sendValuesPY(ClientSocket* sock, struct values a);
void closeConnection(ClientSocket sock);

#endif /* socket_hpp */
