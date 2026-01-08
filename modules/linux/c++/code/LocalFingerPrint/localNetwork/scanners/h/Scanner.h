#pragma once
#include <thread>
#include "ping/h/Ping.h"



class Scanner
{

private:

    Ping ping;

public:


    bool openPort(std::string ip, int port);


};

