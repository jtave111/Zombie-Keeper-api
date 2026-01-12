#pragma once

#include <vector>
#include "localNetwork/model/h/Session.h"
#include "localNetwork/model/h/Node.h"

#include "FingerprintSession.h"



class SessionBuild
{
private:
    FingerprintSession fingerprintSession;
    Ping ping;
public:

    void buildSession(Session& targetSession);
    void buildNodes(std::string gateway, int cidr, Session & session);

    SessionBuild() = default;
    ~SessionBuild() = default;

};

