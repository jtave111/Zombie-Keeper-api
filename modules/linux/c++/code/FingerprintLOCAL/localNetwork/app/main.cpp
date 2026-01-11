#include "h/App.h"
#include <iostream>


int main(int argc, char* argv[]){

    App app;
    Session session = app.creatSession();
    std::string gt = session.getGatewayIp();
    std::cout << gt  << std::endl;

}

