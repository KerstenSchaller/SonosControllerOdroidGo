#include <WiFi.h>
#include <odroid_go.h>

#include "config.h"
#include "wifi_controller.h"

wifi_parameter_t wifi_parameters;

boolean connectWifi() 
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_parameters.SSID.c_str(), wifi_parameters.PASSWORD.c_str());
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
    wifi_parameters.IP = WiFi.localIP().toString().c_str();
    return true;
}