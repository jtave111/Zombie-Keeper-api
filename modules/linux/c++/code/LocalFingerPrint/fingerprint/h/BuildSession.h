#pragma once
#include "model/h/Session.h"
#include "model/h/Node.h"
#include "FingerprintSession.h"


class BuildSession
{
private:
    FingerprintSession fingerPrint;
public:

    Session build();
    BuildSession() = default;
    ~BuildSession() = default;

};

