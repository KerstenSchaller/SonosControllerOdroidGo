#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <odroid_go.h>
#include "string.h"

struct wifi_parameter_t
{
    std::string SSID;
    std::string PASSWORD;  
};

boolean connectWifi(wifi_parameter_t parameter);



#endif