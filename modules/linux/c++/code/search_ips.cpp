#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

#include <nlohmann/json.hpp>



//Binary calc 
unsigned short checksum(void *b, int len) {    
    unsigned short *buf = (unsigned short *)b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;

    if (len == 1)
        sum += *(unsigned char *)buf;

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    
    return result;
}

uint32_t ipToInt(const std::string& ip){

    std::stringstream ss(ip);

    uint32_t a,b,c,d;

    char p;

    ss >> a >> p >> b >> p >> c >> p >> d;

    return(a << 24) | (b << 16) | (c << 8) | d;

}

std::string intToStr(uint32_t ip){

  return   std::to_string((ip >> 24) & 0xFF) + "." +
           std::to_string((ip >> 16) & 0xFF) + "." +
           std::to_string((ip >> 8) & 0xFF) + "." +
           std::to_string(ip & 0xFF);
}


// Ip_respnse from SpiderNET 
bool ping(const char *ip) {
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    
    if (sock < 0) return false;

    // Timeout 
    struct timeval tv;
    tv.tv_sec = 0; 
    tv.tv_usec = 200000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    // Target
    struct sockaddr_in target;
    target.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &target.sin_addr);

    // Pacote ICMP  
    char package[64];
    memset(package, 0, sizeof(package));

    struct icmphdr *icmp = (struct icmphdr*)package;
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->un.echo.id = htons(1234);
    icmp->un.echo.sequence = htons(1);

    // Calcula checksum                         
    icmp->checksum = checksum(package, sizeof(package)); 

    // Envia o pacote
    sendto(sock, package, sizeof(package), 0, (struct sockaddr*)&target, sizeof(target));

    // Resposta do timeout
    char buffer_respost[1024];
    struct sockaddr_in sender;
    socklen_t len = sizeof(sender);

    while(true) {
        int bytes = recvfrom(sock, buffer_respost, sizeof(buffer_respost), 0, (struct sockaddr*)&sender, &len);
    
        if(bytes <= 0) {
            close(sock);
            return false;   
        }

        // Cálculo para ICMP
        struct iphdr *ip_header = (struct iphdr *)buffer_respost;
        int header_len = ip_header->ihl * 4;
        struct icmphdr *reply = (struct icmphdr *)(buffer_respost + header_len);

        // Filtro
        if(reply->type == ICMP_ECHOREPLY && reply->un.echo.id == htons(1234)) {
            char d[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &sender.sin_addr, d, INET_ADDRSTRLEN);

            if (std::string(ip) == std::string(d)) {
                close(sock);
                return true;
            } else {
                continue; 
            }
        }
    }
}


std::mutex list_mutex;

void addIps(std::string ip, std::vector<std::string>& listIps ){



    if(ping(ip.c_str()) != false){

        std::lock_guard<std::mutex> lock(list_mutex);
        listIps.emplace_back(ip);
    
    }
    

}


std::vector<std::string> scanALl(const std::string& ip_str, int cidr){

    std::vector<std::thread> th;

    std::vector<std::string> listIps;

    uint32_t ip_binary = ipToInt(ip_str);

    uint32_t mask =  0xFFFFFFFF << (32 - cidr);

    uint32_t network = ip_binary & mask;

    uint32_t boradcast = network | ~mask;


    for(uint32_t i = network; i < boradcast; i++){

        th.emplace_back(addIps, intToStr(i), std::ref(listIps));

    }


    for(auto& t: th){

        if(t.joinable()) t.join();
    }


    return listIps;

}


std::string comand_exec(std::string comand){

    char buffer [255];
    std::string result = "";
    FILE* pipe = popen(comand.c_str(), "r");


    try{
        
        while (fgets(buffer, sizeof(buffer), pipe) != NULL)
        {
            result+= buffer;
        }
        

    }
    catch(...)
    {
        pclose(pipe);
        throw;
    }

    pclose(pipe);

    return result;

}


using json = nlohmann::json;

json create_json(std::vector<std::string> dataVector, std::string jsonName){

    json j;
    j[jsonName] = dataVector;


    return j;

}

std::vector<std::string> makeIpList( std::string comand){
    
   std::string  ip_range_str = comand_exec(comand);

    std::stringstream ss (ip_range_str);

    std::string ip_base;
    int cidr = 0;


    if(std::getline(ss, ip_base, '/')){

        ss >>cidr;
    }

    std::vector<std::string> ipList = scanALl(ip_base, cidr);


    return ipList;
} 



int main( int argc, char* argv[]){


    std::string comand = R"(ip -o -f inet addr show | grep -v 127.0.0.1 | awk '
    {
    split($4, a, "/")
    ip = a[1]
    mask = a[2]

    split(ip, o, ".")
    ipnum = o[1]*256^3 + o[2]*256^2 + o[3]*256 + o[4]

    net = int(ipnum / 2^(32-mask)) * 2^(32-mask)

    printf "%d.%d.%d.%d/%d\n",
        int(net/256^3)%256,
        int(net/256^2)%256,
        int(net/256)%256,
        net%256,
        mask
    }')";


    std::vector<std::string> ipList = makeIpList(comand);

    json j = create_json(ipList, "hosts");

    //Print para captura 
    std::cout << j.dump() << std::endl;

    
}