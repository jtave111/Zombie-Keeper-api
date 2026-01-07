#include "h/Node.h"
#include "h/Session.h" 


Node::Node(std::string ip, std::string mac, std::string host, std::string vend, int score)
    : ipAddress(ip), macAddress(mac), hostname(host), vendor(vend), vulnerabilityScore(score)
{
}

Node::~Node()
{
}

void Node::addPort(const Port& port) {
    this->openPorts.push_back(port);
}

void Node::addVulnerability(const Vulnerability& vuln) {
    this->vulnerabilities.push_back(vuln);
}
/*
std::string Node::toJson() const {
    std::stringstream ss;
    ss << "{";
    
    ss << "\"ipAddress\": \"" << ipAddress << "\",";
    ss << "\"macAddress\": \"" << macAddress << "\",";
    ss << "\"hostname\": \"" << hostname << "\",";
    ss << "\"vendor\": \"" << vendor << "\",";
    ss << "\"vulnerabilityScore\": " << vulnerabilityScore << ",";

    // Só imprimimos o ID da sessão para evitar loop infinito no JSON
    if (session != nullptr) {
        ss << "\"sessionId\": \"" << session->getNetworkIdentifier() << "\",";
    } else {
        ss << "\"sessionId\": null,";
    }

    ss << "\"openPorts\": [";
    for (size_t i = 0; i < openPorts.size(); ++i) {
        ss << openPorts[i].toJson();
        if (i < openPorts.size() - 1) ss << ",";
    }
    ss << "],";

    ss << "\"vulnerabilities\": [";
    for (size_t i = 0; i < vulnerabilities.size(); ++i) {
        ss << vulnerabilities[i].toJson();
        if (i < vulnerabilities.size() - 1) ss << ",";
    }
    ss << "]";

    ss << "}";
    return ss.str();
}
*/