#include <WiFi.h>
#include <odroid_go.h>

#include "config.h"
#include "wifi_controller.h"

boolean connectWifi(wifi_parameter_t parameter) 
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(parameter.SSID.c_str(), parameter.PASSWORD.c_str());
    Serial.write("Waiting for WiFi to connect...\n");
        
    uint8_t wifiTries = 0;
    wl_status_t status = WiFi.status();
    while (status != WL_CONNECTED && status != WL_CONNECT_FAILED && wifiTries < 50) {
        delay(50);
        status = WiFi.status();
        wifiTries += 1;
    }

    if (!WiFi.isConnected() ) {
            GO.lcd.println("WiFi connect failed, restarting");
            delay(1000);
            ESP.restart();
    
    }
    GO.lcd.println("WiFi connect succeeded");
    return true;
}