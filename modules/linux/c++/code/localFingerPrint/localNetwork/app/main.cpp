#include "h/App.h"
#include <iostream>
#include "Scanner.h"
#include <iomanip>
#include <algorithm>

int main(int argc, char* argv[]){
   
    Session session; 
    App app;

    Scanner sc;

    std::cout << "[*] Iniciando construção da sessão..." << std::endl;
    
  
    app.createSession(session); 
    sc.setSession(&session); 

    std::cout << "[*] Iniciando Scan de Portas..." << std::endl;
    sc.scan_all_TcpNodePorts(session);
    std::cout << "[*] Iniciando Scan de Portas..." << std::endl;
    sc.scan_any_TcpNodePorts(session);

    
    std::string target = "192.168.5.157"; 
    bool found = false;

    auto& nodes = session.getMutableNodes(); 

    std::cout << "\n\n"; 

    for (auto& node : nodes) {
        if (node.getIpAddress() == target) {
            found = true;

            std::cout << "################################################" << std::endl;
            std::cout << "# Info of host: " << target << std::endl;
            std::cout << "################################################" << std::endl;
    
            std::cout << std::left 
                      << std::setw(10) << "PORT" 
                      << std::setw(10) << "PROTO" 
                      << "STATUS" << std::endl;
            
            std::cout << "--------------------------------" << std::endl;
            std::vector<Port> openPorts = node.getOpenPorts();
            std::sort(openPorts.begin(), openPorts.end(), 
                [](const Port& a, const Port& b) {
                    return a.getNumber() < b.getNumber();
                });

            if (openPorts.empty()) {
                std::cout << "Nothing" << std::endl;
            } else {
                for (auto& p : openPorts) {
                    std::cout << std::left 
                              << std::setw(10) << p.getNumber() 
                              << std::setw(10) << "tcp" 
                              << "\033[1;32mOPEN\033[0m" << std::endl;
                }
            }
            std::cout << "################################################" << std::endl;
            
            break; 
        }
    }

    if (!found) {
        std::cout << "[-] Error: node " << target << " not found." << std::endl;
    }
    
    return 0;
}

