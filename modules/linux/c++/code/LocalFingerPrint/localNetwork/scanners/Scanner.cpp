#include "h/Scanner.h"


bool Scanner::openPort(std::string ip, int port){


    if(!ping.ping(ip.c_str())) return false;


    int sock = socket(AF_INET, sock, 0);

    if(sock < 0) return false;

    struct sockaddr_in target {};
    target.sin_family = AF_INET;
    target.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &target.sin_addr);


    int connection = connect(sock, (sockaddr*)&target, sizeof(target));

    if(connection < 0) return false;


    close(sock);


    return true;

}

/// ler all ports, return vector ? 
