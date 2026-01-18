#include "h/SessionBuild.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <memory>
#include <array>
#include <algorithm>



void SessionBuild::buildSession(Session& targetSession){


    std::string rawNetIdentfier = fingerprintSession.makeIdentifierCombination_module1();
    std::string rawGatewayIp = fingerprintSession.gatewayIp_module1();
    std::string rawSubnetMask = fingerprintSession.getSubmask_module1();
    std::string rawCidr = fingerprintSession.getCidr_module1();


    targetSession.setNetworkIdentifier(rawNetIdentfier);
    targetSession.setGatewayIp(rawGatewayIp);
    targetSession.setSubnetMask(rawSubnetMask);
    targetSession.setCidr(rawCidr);

    
    //------ Build nodes 

    std::string gateway = rawGatewayIp;
    int cidr = std::stoi(rawCidr);
    std::vector<Node> nodes;

    buildNodes(gateway, cidr, targetSession);
   

}

void SessionBuild::buildNodes(std::string gateway, int cidr, Session & session){


    std::vector<std::string> ipList = fingerprintSession.discoverNodes(gateway, cidr);


    for(int i = 0; i < ipList.size(); i++){        
        
        Node actualNode;         
        actualNode.setSession(&session);
        std::string nodeIp = ipList[i];
        std::string nodeMac = fingerprintSession.getMacAddress_module1(ipList[i]);
       
        // Retirar
        actualNode.setIpAddress(nodeIp);
        actualNode.setMacAddress(nodeMac);

        
        session.addNode(actualNode);
    }

 
 
}