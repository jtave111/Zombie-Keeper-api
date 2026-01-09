#include "h/Scanner.h"
#include "localNetwork/model/h/Session.h"

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


std::mutex mutex;
void Scanner::aux_allNode_TcpPorts(const std::string* ip, Node* node_ptr){

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


void Scanner::banner_grabbing(Session &session ){

    std::vector<Node> * ptr_session_nodes = &session.getMutableNodes();

    int sizeNodes = ptr_session_nodes->size();



    for(int i = 0; i < sizeNodes; i ++){

        Node * node_ptr = &ptr_session_nodes->at(i);

        std::vector<Port> * ports_ptr = &node_ptr->getmMutablesPorts();


        int size_ports = ports_ptr->size();


        for(int k = 0; k < size_ports; i ++){


        }

        
           
    }
    

}

