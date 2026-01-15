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
    
    void scan_any_TcpNodePorts(Session &session);
    void aux_any_TcpNodePorts(const std::string* ip, Node * node, long timeout_sec, long timeout_usec);

    void banner_grabbing_tcp(Session &session);
    void aux_get_banner( std::string ip, Port *port);

    

    //Referenciar na chamada 
    void setSession(Session* s){
        this->session = s;
    }


    //Vector tatical tcp ports 

std::vector<int> getTacticalTcpPorts() {
    return {
        
        21,   // FTP 
        22,   // SSH
        23,   // Telnet 
        25,   // SMTP 
        53,   // DNS
        
        80,   // HTTP
        443,  // HTTPS
        8080, // Web Proxy / Alt HTTP
        8180, // Apache Tomcat / Alt HTTP 
        8443, // Alt HTTPS
        
        135,  // MSRPC
        139,  // NetBIOS
        445,  // SMB 
        3389, // RDP         

        1433, // MSSQL
        3306, // MySQL
        5432, // PostgreSQL
        6379, // Redis
        27017,// MongoDB

        1524, // Ingreslock (Backdoor root shell)
        2049, // NFS (File Share - Mountable)
        2121, // CCProxy / Custom FTP
        3632, // Distcc (Remote Code Execution)
        5900, // VNC (Acesso visual remoto)
        6000, // X11 (Keylogging remoto se aberto)
        6667, // IRC (Backdoors / Botnets)
        
        512,  // exec (R-Service)
        513,  // login (R-Service)
        514,  // shell (R-Service)
        1099, // Java RMI (Java Deserialization exploits)
        8009  // Apache Jserv (AJP Ghostcat exploit)
    };
}
};

