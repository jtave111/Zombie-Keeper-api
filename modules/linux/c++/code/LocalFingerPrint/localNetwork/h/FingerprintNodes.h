#pragma once
#include <string>
#include <sstream>
#include <cstdio>
#include <vector>
#include "ping/h/Ping.h"
#include "FingerprintSession.h"
#include <mutex>
#include <thread>

class FingerprintNodes
{
private:
     
    Ping ping;
    FingerprintSession fingerSession;


public:

    //Binary calc 
    std::string ipIntToStr(u_int32_t ip);
    u_int32_t iptStrToInt(std::string ip);

    std::vector<std::string> makeIpList(std::string ipNet, int cidr);

    

};


