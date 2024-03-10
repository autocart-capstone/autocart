//
//  socket.cpp
//

#include "socket.hpp"

using namespace std;

ClientSocket createConnection(char *ip, char *port)
{
    ClientSocket sock;

    /* Create a socket point */
    sock.sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock.sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }
    else if (sock.sockfd > 0)
    {
        cout << "SOCKET OPENED" << endl;
    }

    sock.serv_addr.sin_family = AF_INET;
    sock.serv_addr.sin_port = htons(atoi(port));
    inet_pton(AF_INET, ip, &(sock.serv_addr.sin_addr.s_addr));

    cout << "attempting to connect to server" << endl;

    int conn_success = connect(sock.sockfd, (struct sockaddr *)&sock.serv_addr, sizeof(sock.serv_addr));

    if (conn_success < 0)
    {
        cout << "ERROR connecting to " << ip << ":" << port << endl;
        exit(1);
    }
    else
    {
        cout << "connection successful to " << ip << ":" << port << endl;
    }

    return sock;
}

int sendValuesPY(ClientSocket* sock, struct values a) {
    int n = send(sock->sockfd, &a, sizeof(a), 0);
    return 0;
}

void sendValues(ClientSocket *sock, void *a, int size)
{
    int n = send(sock->sockfd, a, size, 0);
    if (n < 0)
    {
        cout << "Error in `sendValues`: " << std::strerror(errno) << endl;
        exit(1);
    }
}

void closeConnection(ClientSocket sock)
{
    int n = close(sock.sockfd);
    if (n < 0)
    {
        cout << "Error shutting down socket" << endl;
    }
    else
    {
        cout << "Socket has been shutdown" << endl;
    }
}
