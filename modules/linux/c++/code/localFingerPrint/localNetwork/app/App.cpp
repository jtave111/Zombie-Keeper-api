#include "localNetwork/app/h/App.h"
#include <iostream>


void App::createSession(Session &session){
    
    builder.buildSession(session);
    
    Session * ptr_session = &session;

   
    
}


void App::scannSession(Session *ptr_session){

    scanner.setSession(ptr_session);


    scanner.scan_all_TcpNodePorts( *ptr_session);
    scanner.banner_grabbing_tcp(*ptr_session);

}