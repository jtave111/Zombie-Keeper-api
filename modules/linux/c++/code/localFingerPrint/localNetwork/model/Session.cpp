#include "h/Session.h"
#include <sstream>

Session::Session(std::string netId, std::string gateway, std::string mask, std::string cidr)
    : networkIdentifier(netId), gatewayIp(gateway), subnetMask(mask), cidr(cidr)
{
}

Session::~Session()
{
}

void Session::addNode(const Node& node) {
    this->nodes.push_back(node);
}

/*
std::string Session::toJson() const {
    std::stringstream ss;
    ss << "{";
    
    
    ss << "\"networkIdentifier\": \"" << networkIdentifier << "\",";
    ss << "\"gatewayIp\": \"" << gatewayIp << "\",";
    ss << "\"subnetMask\": \"" << subnetMask << "\",";
    ss << "\"cidr\": \"" << cidr << "\",";

    
    ss << "\"nodes\": [";
    for (size_t i = 0; i < nodes.size(); ++i) {
        
        ss << nodes[i].toJson(); 
        if (i < nodes.size() - 1) ss << ",";
    }
    ss << "],";

    
    ss << "\"ports\": [";
    for (size_t i = 0; i < ports.size(); ++i) {
        ss << ports[i].toJson();
        if (i < ports.size() - 1) ss << ",";
    }
    ss << "]";

    ss << "}";
    return ss.str();
}
*/