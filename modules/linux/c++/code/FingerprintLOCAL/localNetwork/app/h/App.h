
#pragma once

#include "localNetwork/scanners/h/Scanner.h"
#include "localNetwork/model/h/Session.h"  
#include "localNetwork/h/SessionBuild.h"    

class App
{
private:
    
    Session session;
    Scanner scanner;
    SessionBuild sessionBuild;
public:
    

    Session creatSession();
    void scannSession(Session *ptr_session);

};

