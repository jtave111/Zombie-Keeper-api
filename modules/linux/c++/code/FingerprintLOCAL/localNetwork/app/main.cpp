#include "h/App.h"
#include <iostream>
#include "Scanner.h"

int main(int argc, char* argv[]){
   
    Session session; 
    App app;

    Scanner sc;

    std::cout << "[*] Iniciando construção da sessão..." << std::endl;
    
  
    app.createSession(session); 
    sc.setSession(&session); 

    std::cout << "[*] Iniciando Scan de Portas..." << std::endl;
    sc.scan_all_TcpNodePorts(session);

    
    return 0;
}

