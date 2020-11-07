#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <AsyncUDP.h>
#include <string.h>
#include <Preferences.h>
#include <esp_sleep.h>
#include <esp_wifi.h>
#include <driver/touch_pad.h>
#include <driver/rtc_io.h>
//#include "ulp_main.h"
#include "sonos.h"


#include <odroid_go.h>

#include "config.h"
#include "button_wrapper.h"
#include "wifi_controller.h"




void setup() {  
  
  GO.Speaker.end();
  Serial.begin(115200);
  GO.begin();
  GO.lcd.setTextSize(2);
  GO.lcd.println("Starting");
  wifi_parameter_t wifi_parameters;
  wifi_parameters.SSID = "Pfannekuchen";
  wifi_parameters.PASSWORD = "kabelbeisser";
  connectWifi(wifi_parameters);
  sonos_parameters.UID = "RINCON_347E5C37566601400";
}
 
void updateSonosScreen()
{
    GO.lcd.clear();
    GO.lcd.setCursor(0,0);
    GO.lcd.printf("Playstate: %s\n",sonos_parameters.PlayState.c_str());
    GO.lcd.printf("Voume: ");
    GO.lcd.print(sonos_parameters.Volume, DEC);
    GO.lcd.printf("\n");
}

void handleButtons()
{
  if(VOLUME_UP_BUTTON)
  {
      doSonos(volumeUp);
      updateSonosScreen();
  }
  if(VOLUME_DOWN_BUTTON)
  {
      doSonos(volumeDown);
      updateSonosScreen();
  }
  if(NEXT_TRACK_BUTTON)
  {
      doSonos(sonosNext);
  }
  if(PLAY_PAUSE_BUTTON)
  {
      doSonos(sonosPlay);
      updateSonosScreen();
  }


}
 
void loop() {
  GO.update();
  handleButtons();
  delay(200);
}