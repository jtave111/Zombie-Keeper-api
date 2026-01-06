#include "h/FingerprintNodes.h"



std::string FingerprintNodes::ipIntToStr(uint32_t ip){

    return std::to_string( (ip >> 24) & 0xFF ) + "."  +  
    std::to_string( (ip >> 16 )  & 0xFF ) + "."  + 
    std::to_string( (ip >> 8 )  & 0xFF ) + "."  + 
    std::to_string( ip & 0xFF );

}

uint32_t FingerprintNodes::iptStrToInt(std::string ip){

    uint32_t a, b, c, d;
    char p;
    std::stringstream ss (ip);


    ss >> a >> p >> b >> p >> c >> p >> d;


    return (a << 24) | (b  << 16) | (c << 8) | d;

}



std::mutex list_mutex;

void addIps(std::string ip, std::vector<std::string>& listIps ){
      
    Ping ping;


    if(ping.ping(ip.c_str()) != false){

        std::lock_guard<std::mutex> lock(list_mutex);
        listIps.emplace_back(ip);
    
    }
    

}

//Call whith 
/* 
    int cidr = std::stoi(fingerSession.getCidr_module1());
    std::string netIp = fingerSession.getNetworkIp_module1();
*/

std::vector<std::string> FingerprintNodes::makeIpList(std::string ipNet, int cidr){

    std::vector<std::thread> th;

    std::vector<std::string> listIps;
    
    uint32_t mask =  0xFFFFFFFF << (32 - cidr);
    uint32_t network = FingerprintNodes::iptStrToInt(ipNet);

    uint32_t broadcast = network | ~mask;


    for(int i = network; i < broadcast; i++){


        th.emplace_back(addIps, FingerprintNodes::ipIntToStr(i), std::ref(listIps));
    }


    for(auto& t: th){

        if(t.joinable()) t.join();
    }

    return listIps;

}