#include "h/SessionBuild.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <memory>
#include <array>
#include <algorithm>

auto cleanString = [](std::string &s) {
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());    
};


Session SessionBuild::buildSession(){

    Session localSession;
    
   

    std::string rawNetIdentfier = fingerprintSession.makeIdentifierCombination_module1();
    std::string rawGatewayIp = fingerprintSession.gatewayIp_module1();
    std::string rawSubnetMask = fingerprintSession.getSubmask_module1();
    std::string rawCidr = fingerprintSession.getCidr_module1();

    cleanString(rawNetIdentfier);
    cleanString(rawGatewayIp);
    cleanString(rawSubnetMask);
    cleanString(rawCidr);

    // Retirar
    std::cout << "\n";
    std::cout << "=============================================" << std::endl;
    std::cout << "   NETWORK CONFIGURATION DEBUG             " << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << " [>] Interface Identifier : " << rawNetIdentfier << std::endl;
    std::cout << " [>] Gateway IP           : " << rawGatewayIp << std::endl;
    std::cout << " [>] Subnet Mask          : " << rawSubnetMask << std::endl;
    std::cout << " [>] CIDR                 : /" << rawCidr << std::endl;
    std::cout << "=============================================" << std::endl;
    std::cout << "\n";

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

void SessionBuild::buildNodes(std::string gateway, int cidr, Session & session){


    std::vector<std::string> ipList = fingerprintSession.discoverNodes(gateway, cidr);


    for(int i = 0; i < ipList.size(); i++){        
        
        Node actualNode;         
        actualNode.setSession(&session);
        std::string nodeIp = ipList[i];
        std::string nodeMac = fingerprintSession.getMacAddress_module1(ipList[i]);
       
        cleanString(nodeIp);
        cleanString(nodeMac);
        // Retirar
        std::cout << "[+] Node Found: " << nodeIp << " \t MAC: " << nodeMac << std::endl;
        actualNode.setIpAddress(nodeIp);
        actualNode.setMacAddress(nodeMac);

        
        session.addNode(actualNode);
    }


}