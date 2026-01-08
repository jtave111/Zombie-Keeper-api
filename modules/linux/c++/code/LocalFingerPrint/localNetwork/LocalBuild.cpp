#include "h/LocalBuild.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <memory>
#include <array>


Session LocalBuild::buildSession(){

    Session localSession;
    
    std::string rawNetIdentfier = fingerprintSession.makeIdentifierCombination_module1();
    std::string rawGatewayIp = fingerprintSession.gatewayIp_module1();
    std::string rawSubnetMask = fingerprintSession.getSubmask_module1();
    std::string rawCidr = fingerprintSession.getCidr_module1();
    

    localSession.setNetworkIdentifier(rawNetIdentfier);
    localSession.setGatewayIp(rawGatewayIp);
    localSession.setSubnetMask(rawSubnetMask);
    localSession.setCidr(rawCidr);

    
    //------ Build nodes 

    std::string gateway = rawGatewayIp;
    int cidr = std::stoi(rawCidr);
    std::vector<Node> nodes;

    buildNodes(gateway, cidr, localSession);



    return localSession;

}

void LocalBuild::buildNodes(std::string gateway, int cidr, Session & session){


    std::vector<std::string> ipList = fingerprintNodes.makeIpList(gateway, cidr);


    for(int i = 0; i < ipList.size(); i++){        
        
        Node actualNode; 
        actualNode.setIpAddress(ipList[i]);
        actualNode.setSession(&session);

        
        session.addNode(actualNode);
    }


}