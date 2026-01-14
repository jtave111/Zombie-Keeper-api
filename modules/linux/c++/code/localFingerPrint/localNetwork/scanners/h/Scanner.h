#pragma once
#include <thread>
#include <mutex>
#include "Ping.h"
#include "localNetwork/model/h/Port.h"
#include <vector>
#include "localNetwork/model/h/Node.h"

class Session; 

class Scanner
{

private:

    Ping ping;
    
    Session* session = nullptr;


public:

    

    //TCP
    bool openPort_tcp(std::string ip, int port, long timeout_sec, long timeout_usec);
    
    
    void scan_all_TcpNodePorts(Session &session);
    void aux_allNode_TcpPorts(const std::string* ip, Node* node, long timeout_sec, long timeout_usec);
    

    void banner_grabbing_tcp(Session &session);
    void aux_get_banner( std::string ip, Port *port);

    

    //Referenciar na chamada 
    void setSession(Session* s){
        this->session = s;
    }

};

