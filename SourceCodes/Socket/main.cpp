//
//  main.cpp
//


#include <iostream>
#include "socket.hpp"

using namespace std;




struct values mess[6];

int main(int argc, char *argv[]) {
    struct values v1;
    v1.degrees = 50;
    v1.distance = 1000;
    v1.quality = 47;
    struct values v2;
    v2.degrees = 51;
    v2.distance = 1001;
    v2.quality = 47;
    struct values v3;
    v3.degrees = 52;
    v3.distance = 1002;
    v3.quality = 47;
    struct values v4;
    v4.degrees = 53;
    v4.distance = 1003;
    v4.quality = 47;
    struct values v5;
    v5.degrees = 54;
    v5.distance = 1004;
    v5.quality = 47;
    struct values v6;
    v6.degrees = 55;
    v6.distance = 1005;
    v6.quality = 47;
    mess[0] = v1;
    mess[1] = v2;
    mess[2] = v3;
    mess[3] = v4;
    mess[4] = v5;
    mess[5] = v6;
    createConnection();
    for(int i = 0; i < 6; i++) {
        sendValues(mess[i]);
    }
    closeConnection();
    
    return 0;
}
