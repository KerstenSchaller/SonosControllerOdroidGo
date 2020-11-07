#include <odroid_go.h>
#include "wifi_controller.h"
#include "sonos.h"

void updateScreen()
{
    GO.lcd.clear();
    GO.lcd.setCursor(0,0);
    GO.lcd.setTextSize(1);
    GO.lcd.println(" Odroid Wifi Settins: ");
    GO.lcd.printf( "   SSID: %s\n", wifi_parameters.SSID.c_str());
    GO.lcd.printf( "   IP: %s\n", wifi_parameters.IP.c_str());
    GO.lcd.println(" Sonos Wifi Settings: ");
    GO.lcd.printf( "   UID: %s\n", sonos_parameters.UID.c_str());
    GO.lcd.printf( "   IP: %s\n", sonos_parameters.IP.c_str());
    GO.lcd.printf( "   WWW: %s:1400/status/zp", sonos_parameters.IP.c_str());
}

void startSettingsApp()
{
    updateScreen();
}

void handleSettingsApp()
{
    
}

