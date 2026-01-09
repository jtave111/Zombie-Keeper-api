#pragma once
#include <thread>
#include <mutex>
#include "ping/h/Ping.h"
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
    bool openPort_tcp(std::string ip, int port);
    
    void aux_allNode_TcpPorts(const std::string* ip, Node* node);
    
    void scan_all_TcpNodePorts(Session &session);
    void banner_grabbing(Session &session);



    

    //Referenciar na chamada 
    void setSession(Session* s){
        this->session = s;
    }

};

