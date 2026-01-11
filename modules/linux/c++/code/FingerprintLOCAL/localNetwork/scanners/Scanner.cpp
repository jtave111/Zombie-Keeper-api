#include "h/Scanner.h"
#include "localNetwork/model/h/Session.h"



//---- Aux functions 

void Scanner::aux_allNode_TcpPorts(const std::string* ip, Node* node_ptr){
   static std::mutex mutex;
    for(int i = 1; i < 65536; i ++){

        if(Scanner::openPort_tcp(*ip, i)){
            mutex.lock();

            Port actualPort;
            actualPort.setNumber(i);
            node_ptr->addPort(actualPort);

            mutex.unlock();

        }
    }
}

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




//--- Core functions 
bool Scanner::openPort_tcp(std::string ip, int port){


    if(!ping.ping(ip.c_str())) return false;


    int sock = socket(AF_INET, SOCK_STREAM, 0);

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

void Scanner::scan_all_TcpNodePorts(Session &session){

    std::vector<std::thread> threads;

    std::vector<Node> * ptr_session_nodes = &session.getMutableNodes();
    int sizeNodes = ptr_session_nodes->size();

    for( int i = 0; i < sizeNodes; i ++ ){

        Node * node_ptr = &ptr_session_nodes->at(i);

        const std::string* actual_ip_ptr = &ptr_session_nodes->at(i).getIpAddress();
      
        threads.emplace_back(&Scanner::aux_allNode_TcpPorts, this, actual_ip_ptr,  node_ptr);

    }

    for(auto& t: threads){
        if(t.joinable()) t.join();
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
