#include "h/Scanner.h"
#include "localNetwork/model/h/Session.h"


/**
 * @brief Attempts to establish a TCP connection to a specific host and port using non-blocking I/O.
 * * This function initiates a TCP 3-Way Handshake without blocking the execution thread.
 * It uses 'select()' to multiplex the I/O and wait for the connection result within a specific timeout.
 */
bool Scanner::portScan_tcp(std::string ip, int port,long timeout_sec, long timeout_usec){

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0) return false;

    //Set Non-Blocking Mod
    // O_NONBLOCK: Operations like connect() will return immediately with EINPROGRESS
    // instead of blocking the process while waiting for the handshake.
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);


    struct sockaddr_in target {};
    target.sin_family = AF_INET;
    target.sin_port = htons(port);

    if(inet_pton(AF_INET, ip.c_str(), &target.sin_addr) <= 0 ) {
        close(sock);
        return false;
    }

    
    //Send syn packet 
    int res = connect(sock, (sockaddr*)&target, sizeof(target));

    if(res < 0){
        
        
        //Connection in progress, It means the TCP Handshake SYN has been sent, but we are waiting for SYN-ACK.
        if(errno == EINPROGRESS){
            
            fd_set myset;
            FD_ZERO(&myset);
            FD_SET(sock, &myset);

            struct timeval tv;
            tv.tv_sec = timeout_sec;
            tv.tv_usec = timeout_usec;
             // We monitor the socket for WRITABILITY.
            res = select(sock + 1, NULL, &myset, NULL, &tv);
    
            if(res > 0){

                int so_error;
                socklen_t len = sizeof(so_error);
                
                // select() returning > 0 only means the process finished.
                if(getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len) < 0 ){
                    close(sock);
                    return false;
                } 

                //accept
                if(so_error == 0){



                    close(sock);
                    return true;
                }

            }

        }

    }else{
        
        close(sock);
        return true ;
    } 


    close(sock);
    return false;

}

//Overload 
bool Scanner::portScan_tcp(Port *port_ptr, std::string ip, int port, long timeout_sec, long timeout_usec){

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0) {
        close(sock);
        return false;
    }

    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in target {};
    target.sin_family = AF_INET;
    target.sin_port = htons(port);

    if(inet_pton(AF_INET, ip.c_str(), &target.sin_addr) <= 0){
        close(sock);
        return false;
    }

    int res = connect(sock, (sockaddr*)&target, sizeof(target));

    if(res < 0){

        if(errno == EINPROGRESS){

            fd_set myset;
            FD_ZERO(&myset);
            FD_SET(sock, &myset);

            struct timeval tv {};
            tv.tv_sec = timeout_sec;
            tv.tv_usec = timeout_usec;

            res = select (sock + 1, NULL, &myset, NULL, &tv);

            if(res > 0){

                int so_error; 
                socklen_t len = sizeof(so_error);

                if(getsockopt(sock,SOL_SOCKET, SO_ERROR, &so_error, &len)  < 0){
                    close(sock);
                    return false;
                }

                if(so_error == 0){

                    char buffer[1024];
                    memset(buffer, 0, sizeof(buffer));

                    if(port == 80 || port == 443 || port == 8080){
                        const char *req = "HEAD / HTTP/1.0\r\n\r\n";
                        send(sock, req, strlen(req), 0);
                    }

                    int bytes = recv(sock, buffer, sizeof(buffer), 0);

                    const std::string banner (buffer);

                    port_ptr->setBanner(banner);

                    close(sock);
                    return true;
                }

            }

        }
    }
    else{

        close(sock);
        return false;
    }
    
    close(sock);
    return false;

}



//Make scan ALL ports --All ports all nodes
void Scanner::scan_all_TcpNodePorts(Session &session){
    long sec = 0;
    long usec = 200000;
    
    std::vector<std::thread> threads;

    std::vector<Node> &nodes = session.getMutableNodes();
   

    for( int i = 0; i < nodes.size(); i ++ ){

        Node* node_ptr = &nodes[i];

        const std::string* ip_ptr = &node_ptr->getIpAddress();
      
        threads.emplace_back(&Scanner::aux_allNode_TcpPorts, this, ip_ptr, node_ptr, sec, usec);

    }

    for(auto& t: threads){
        if(t.joinable()) t.join();
    }

}
void Scanner::aux_allNode_TcpPorts(const std::string* ip, Node* node_ptr, long timeout_sec, long timeout_usec){
    long sec = 0;
    long usec = 200000;
    

    static std::mutex print_mutex; 

    for(int i = 1; i < 65536; i ++){

        
        if(Scanner::portScan_tcp(*ip, i,timeout_sec, timeout_usec)){
         
            Port actualPort;
            actualPort.setNumber(i);
            node_ptr->addPort(actualPort);
        }
    }
}




//Make scan any ports --Any ports all nodes 
void Scanner::scan_any_TcpNodePorts(Session &session){
    long sec = 0;
    long usec = 200000;
    
    
    std::vector<std::thread> threads;

    std::vector<Node> &nodes = session.getMutableNodes();

    for(int i = 0; i < nodes.size(); i ++){

        Node * node_ptr = &nodes[i];

        const std::string * ipPtr = &(node_ptr->getIpAddress());

        threads.emplace_back(&Scanner::aux_any_TcpNodePorts, this, ipPtr, node_ptr, sec, usec);
    }

    for(auto& t: threads){
        if(t.joinable() ) t.join();
    }

}
void Scanner::aux_any_TcpNodePorts(const std::string* ip, Node * node, long timeout_sec, long timeout_usec){

    std::vector <int> taticalPorts = Scanner::getTacticalTcpPorts();
    
    for(int i = 0; i < taticalPorts.size(); i ++){

        if(Scanner::portScan_tcp(*ip, taticalPorts[i], timeout_sec, timeout_usec )){

            Port actualPort;

            actualPort.setNumber(taticalPorts[i]);

            node->addPort(actualPort);

        }

    }
}




//Make scan all or any --One node all ports or any ports - use flag ALL for all ports or use ANY for tatical tcp ports  
void Scanner::scan_OneNode_Tcp(Session &session, std::string ip_node, std::string flag){

    Node* node_ptr = session.getOneMutableNode(ip_node);

    if(node_ptr == nullptr) {
        std::cerr << "Node not found" << std::endl;

        return;
    }

    if(!ping.ping(ip_node.c_str())){
        std::cerr << "Host closed " <<  std::endl;
    }

}

void Scanner::banner_grabbing_tcp(Session &session ){
    std::vector<std::thread> threads;

    std::vector<Node> * ptr_session_nodes = &session.getMutableNodes();

    int sizeNodes = ptr_session_nodes->size();

    for(int i = 0; i < sizeNodes; i ++){

        Node * node_ptr = &ptr_session_nodes->at(i);

        std::vector<Port> * ports_ptr = &node_ptr->getmMutablesPorts();


        int size_ports = ports_ptr->size();


        for(int k = 0; k < size_ports; k ++){

            

            Port * port_ptr = &ports_ptr->at(k);
            std::string ip_str = node_ptr->getIpAddress();

            threads.emplace_back(&Scanner::aux_get_banner, this, ip_str, port_ptr);

        }
        
        for(auto& t : threads){
            if(t.joinable()){
                t.join();
            }
        }
    }
    
}
//Call threads
void Scanner::aux_get_banner( std::string ip, Port *port){
   
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0){
         
        return;
    } 

    struct timeval timeout;
    timeout.tv_sec = 2; 
    timeout.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof timeout);
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof timeout);

    int port_int = port->getNumber();

    struct sockaddr_in target {};
    target.sin_family = AF_INET;
    target.sin_port = htons(port_int);
    inet_pton(AF_INET, ip.c_str(), &target.sin_addr);


    int connection = connect(sock, (struct sockaddr*)&target, sizeof(target));

    if(connection == 0){

        if(port_int == 80 || port_int == 443 || port_int == 8080){
        
            const char* req = "HEAD / HTTP/1.0\r\n\r\n";
            send(sock, req, strlen(req), 0);
        
        }

        int bytes = recv(sock, buffer, 1023, 0);

        static std::mutex banner_mtx;
        std::lock_guard<std::mutex> lock(banner_mtx);
        
        if(bytes > 0){

           port->setBanner(std::string(buffer));
        
        }else{

            port->setBanner("Open(unknown)");
        }
    }

    close(sock);



}