#pragma once

#include <vector>
#include "localNetwork/model/h/Session.h"
#include "localNetwork/model/h/Node.h"

#include "FingerprintSession.h"
#include "FingerprintNodes.h"


class LocalBuild
{
private:
    FingerprintNodes fingerprintNodes;
    FingerprintSession fingerprintSession;
public:

    Session buildSession();
    void buildNodes(std::string gateway, int cidr, Session & session);

    LocalBuild() = default;
    ~LocalBuild() = default;

};

