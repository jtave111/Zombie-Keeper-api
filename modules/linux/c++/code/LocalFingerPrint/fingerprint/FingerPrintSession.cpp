#include "h/FingerprintSession.h"

std::string FingerprintSession::comand_exec(std::string comand ){

    char buffer [255];
    std::string result = "";

    FILE* pipe = popen(comand.c_str(), "r");

    try
    {
            
        while (fgets(buffer, sizeof(buffer), pipe) != NULL)
        {
            result += buffer;
        }


        pclose(pipe);
        
    }
    catch(...)
    {
        pclose(pipe);
        throw;
        
    }
    

    return result;
}



//Binary calc 
std::string FingerprintSession::ipIntToStr (u_int32_t ip){

    return std::to_string( (ip >> 24) & 0xFF) + "." +
    std::to_string( (ip >> 16) & 0xFF ) + "." + 
    std::to_string( (ip >> 8 ) & 0xFF ) + "." + 
    std::to_string (ip & 0xFF);

    
}

u_int32_t FingerprintSession::iptStrToInt(std::string ip){


    std::stringstream ss(ip);

    u_int32_t a, b, c, d;

    char p;

    ss >> a >> p >> b >> p >> c >> p >> d;


    return (a << 24) | (b << 16) | (c << 8) | d;

}



//Module 1 calls
//-----------------------------------


//getGateway modules 

std::string FingerprintSession::gatewayIp_module1(){
    
    std::string comand = "ip route show default | awk '{print $3}'";

    std::string result = FingerprintSession::comand_exec(comand);

    return result ;

}

// getCidr & submask modules

std::string FingerprintSession::getCidr_module1(){

    std::string comand = "ip route show dev $(ip route show default | awk '{print $5}') | grep 'scope link' | awk '{print $1}'";

    std::string result = FingerprintSession::comand_exec(comand);

    std::stringstream ss (result);
    std::string base_ip;


    std::string CIDR = "";

    while (std::getline(ss, base_ip, '/'))
    {
        ss >> CIDR;
    }
    

    return CIDR;

}

std::string FingerprintSession::getNetworkIp_module1(){
    
    std::string comand = "ip route show dev $(ip route show default | awk '{print $5}') | grep 'scope link' | awk '{print $1}'";    
    std::string result = FingerprintSession::comand_exec(comand);

    std::stringstream ss(result);

    std::string base_ip;

    std::getline(ss, base_ip, '/');


    return base_ip;


}


std::string FingerprintSession::getSubmask_module1(){


   int cidr = std::stoi(FingerprintSession::getCidr_module1());

    u_int32_t submask = 0xFFFFFFFF  << (32 - cidr);

    std::string result = ipIntToStr(submask);

    return result;

}



//NetWorkIdentifier 

std::string FingerprintSession::getSSID_module1(){

    std::string comand = "iwgetid -r";

    std::string result = FingerprintSession::comand_exec(comand);

    return result;
}

std::string FingerprintSession::getBSSID_module1(){

    std::string comand = "iwconfig 2>/dev/null | grep -i \"Access Point\" | awk '{print $6}'";

    std::string result = FingerprintSession::comand_exec(comand);

    return result;

    
}

std::string FingerprintSession::makeIdentifierCombination_module1(){

    std::string SSID = getSSID_module1();
    std::string BSSID = getBSSID_module1();

    return SSID + "-" + BSSID; 
}
