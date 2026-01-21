
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
    

    void createSession(Session *session, std::string flags);
    void scannSession(Session *ptr_session, std::string flags, long sec, long usec);

};

