#include <odroid_go.h>
#include "button_wrapper.h"
#include "wifi_controller.h"
#include "sonos_app.h"
#include "settings_app.h"

enum class APP { SONOS, WIFI_SETTINGS };
APP current_app = APP::SONOS;

void setup() 
{ 
  Serial.begin(115200);

  GO.begin();
  GO.Speaker.begin();
  GO.Speaker.mute();
  GO.Speaker.end();


  wifi_parameters.SSID = "Pfannekuchen";
  wifi_parameters.PASSWORD = "kabelbeisser";
  connectWifi();

  startSonosApp();
}
 
void loop() {
  GO.update();

  if(BURGER_BUTTON)
  {
      switch(current_app)
      {
          case APP::SONOS:
            current_app = APP::WIFI_SETTINGS;
            startSettingsApp();
            break;
          case APP::WIFI_SETTINGS:
            current_app = APP::SONOS;
            startSonosApp();
            break;
          default:
            current_app = APP::SONOS;
            startSonosApp();
            break;
      }
  }

  switch (current_app) 
  {
    case APP::SONOS:
        handleSonosApp();
        break;
    case APP::WIFI_SETTINGS:
        handleSettingsApp();
    default:
        break;
  }
  delay(200);
}