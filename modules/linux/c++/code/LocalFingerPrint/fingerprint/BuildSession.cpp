#include "h/BuildSession.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <memory>
#include <array>


Session BuildSession::build(){

    Session localSession;

    std::string rawNetIdentfier = fingerPrint.makeIdentifierCombination_module1();
    std::string rawGatewayIp = fingerPrint.gatewayIp_module1();
    std::string rawSubnetMask = fingerPrint.getSubmask_module1();
    std::string rawCidr = fingerPrint.getCidr_module1();
    

    localSession.setNetworkIdentifier(rawNetIdentfier);
    localSession.setGatewayIp(rawGatewayIp);
    localSession.setSubnetMask(rawSubnetMask);
    localSession.setCidr(rawCidr);



    return localSession;

}