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
    int degrees;
    int distance;
    int quality;
};


void createConnection();
int sendValues(struct values a);
void closeConnection();


#endif /* socket_hpp */






