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

static IPAddress targetSonos;

// Second layer of sonos operation wrapper to handle the rediscovery logic
void doSonos(int (*operation)(HTTPClient *http, IPAddress targetSonos)) {
    if (!targetSonos) {
        targetSonos = discoverSonos(std::string(SONOS_UID));
    }
    if (!targetSonos) {
        ESP_LOGE(TAG, "Couldn't find the right sonos, bailing");
        return;
    }

    int error = sonosOperation(operation, targetSonos);
    if (error) {
        // try rediscovering
        targetSonos = discoverSonos(std::string(SONOS_UID));
    }
}



boolean connectWifi() 
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    Serial.write("Waiting for WiFi to connect...\n");
        
;
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

void setup() {
  GO.Speaker.setVolume(0);
  Serial.begin(115200);
  GO.begin();
  GO.lcd.setTextSize(2);
  GO.lcd.println("Starting");
  connectWifi();
}
 
void handleButtons() {
  static int cnt = 0;
  int linesOnScreen = 14;//14 for text size 2
  if (cnt >= linesOnScreen) 
  {
    cnt = 0;
    GO.lcd.clear();
    GO.lcd.setCursor(0, 0);
  }

  if(VOLUME_UP_BUTTON)
  {
      GO.lcd.printf("Volume up\n");
      doSonos(volumeUp);
      cnt++;
  }
  if(VOLUME_DOWN_BUTTON)
  {
      GO.lcd.printf("Volume down\n");
      doSonos(volumeDown);
      cnt++;
  }
  if(NEXT_TRACK_BUTTON)
  {
      GO.lcd.printf("Next track\n");
      doSonos(sonosNext);
      cnt++;
  }
  if(PLAY_PAUSE_BUTTON)
  {
      GO.lcd.printf("Play/Pause\n");
      doSonos(sonosPlay);
      cnt++;
  }


}
 
void loop() {
  GO.update();
  handleButtons();
  delay(200);
}