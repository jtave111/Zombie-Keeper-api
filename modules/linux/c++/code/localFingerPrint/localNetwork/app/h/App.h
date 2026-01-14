
#pragma once

#include "localNetwork/scanners/h/Scanner.h"
#include "localNetwork/model/h/Session.h"  
#include "localNetwork/h/SessionBuild.h"    

class App
{
private:
    
    Session session;
    Scanner scanner;
    SessionBuild builder;
public:
    

    void createSession(Session &session);
    void scannSession(Session *ptr_session);

};

