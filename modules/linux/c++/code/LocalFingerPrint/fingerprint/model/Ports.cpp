#include "h/Port.h"
#include <sstream> 

Port::Port(int number, std::string protocol, std::string service, std::string banner) 
    : number(number), protocol(protocol), service(service), banner(banner) {}



/*
std::string Ports::toJson() const {
    std::stringstream ss;
    ss << "{";
    
    // Inteiro não leva aspas
    ss << "\"number\": " << number << ",";
    
    // Strings levam aspas escapadas (\")
    ss << "\"protocol\": \"" << protocol << "\",";
    ss << "\"service\": \"" << service << "\",";
    ss << "\"banner\": \"" << banner << "\"";
    
    ss << "}";
    return ss.str();
}
*/