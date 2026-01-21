#include "localNetwork/app/h/App.h"
#include <iostream>


void App::createSession(Session *session, std::string flags){
    
    builder.buildSession(*session);
    
     
}


void App::scannSession(Session *ptr_session, std::string flags, long sec, long usec){


    scanner.setSession(ptr_session);


    if(flags == "-all-ports"){
        
        scanner.scan_all_TcpNodePorts( *ptr_session,  sec,  usec);
       
    }else if(flags == "-any-ports"){

        scanner.scan_any_TcpNodePorts( *ptr_session, sec, usec);
    
    }

}