#include "h/App.h"
#include <iostream>
#include "Scanner.h"
#include <iomanip>
#include <cctype>
#include <algorithm>


void printSessionJson(Session * session){

    std::cout << "["; 

    auto& nodes = session->getMutableNodes();
    bool firstNode = true;

    for (auto& node : nodes) {
        
        if (!firstNode) {
            std::cout << ",";
        }
        firstNode = false;
        
        std::cout << "{";
        std::cout << "\"ip\": \"" << node.getIpAddress() << "\",";
        
        std::string mac = node.getMacAddress();
        if(mac.empty()) mac = "unknown";
        std::cout << "\"mac\": \"" << mac << "\",";
        
        std::cout << "\"ports\": [";
        
        auto ports = node.getOpenPorts();
        bool firstPort = true;

        for (auto& p : ports) {
            if (!firstPort) {
                std::cout << ",";
            }
            firstPort = false;
    
            std::string banner = p.getBanner();
            
            std::replace(banner.begin(), banner.end(), '\n', ' ');
            std::replace(banner.begin(), banner.end(), '\r', ' ');
            std::replace(banner.begin(), banner.end(), '"', '\'');
            std::replace(banner.begin(), banner.end(), '\\', '/');
            
            banner.erase(std::remove_if(banner.begin(), banner.end(), 
                         [](unsigned char c){ return !std::isprint(c); }), banner.end());

            if(banner.empty()) banner = "unknown";

            
            std::string serviceName = p.getService();
            if(serviceName.empty()) serviceName = "unknown";

            std::string protocolName = p.getProtocol();
            if(protocolName.empty()) protocolName = "tcp"; 

            std::cout << "{";
            std::cout << "\"number\": " << p.getNumber() << ",";
            std::cout << "\"proto\": \"" << protocolName << "\",";  
            std::cout << "\"service\": \"" << serviceName << "\","; 
            std::cout << "\"banner\": \"" << banner << "\""; 
            std::cout << "}";
        }

        std::cout << "]"; 
        std::cout << "}"; 
    }

    std::cout << "]" << std::endl; 
}


int main(int argc, char* argv[]){

    App appInit;

   // "./Binary --create_session '-all-ports' or 'any-ports' "
    std::string command = argv[1];

    if(command == "--create_session"){

        std::string scan_opt_flags = argv[2];
        Session session;

        Session *ptr_session = &session;

        appInit.createSession(ptr_session, scan_opt_flags);

        appInit.scannSession(ptr_session, scan_opt_flags);

        printSessionJson(ptr_session);

    }

    return 0;
   
}

