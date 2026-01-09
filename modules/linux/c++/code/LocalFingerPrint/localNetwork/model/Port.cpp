#include "h/Port.h"
#include <sstream> 

Port::Port(int number, std::string protocol, std::string service, std::string banner) 
    : number(number), protocol(protocol), service(service), banner(banner) {}



/*
std::string Ports::toJson() const {
    std::stringstream ss;
    ss << "{";
    
    ss << "\"number\": " << number << ",";
    
    ss << "\"protocol\": \"" << protocol << "\",";
    ss << "\"service\": \"" << service << "\",";
    ss << "\"banner\": \"" << banner << "\"";
    
    ss << "}";
    return ss.str();
}
*/