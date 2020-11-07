#ifndef WIFI_CONTROLLER_H
#define WIFI_CONTROLLER_H

#include <odroid_go.h>
#include "string.h"

struct wifi_parameter_t
{
    std::string SSID;
    std::string PASSWORD; 
    std::string IP; 
};

extern wifi_parameter_t wifi_parameters;

boolean connectWifi();



#endif