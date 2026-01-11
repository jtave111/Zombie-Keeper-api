#include "localNetwork/app/h/App.h"
#include <iostream>


Session App::creatSession(){
    
    Session session = sessionBuild.buildSession();
    
    Session * ptr_session = &session;

    scannSession(ptr_session);

    std::cout << "Chegou antes de  retornar a session" << std::endl;
    return session;
}


void App::scannSession(Session *ptr_session){

    scanner.setSession(ptr_session);


    scanner.scan_all_TcpNodePorts( *ptr_session);
    scanner.banner_grabbing_tcp(*ptr_session);

}