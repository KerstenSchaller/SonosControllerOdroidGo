#include <odroid_go.h>
#include "button_wrapper.h"
#include "wifi_controller.h"
#include "sonos_app.h"

void setup() 
{    
  GO.Speaker.end();
  Serial.begin(115200);
  GO.begin();
  GO.lcd.setTextSize(2);
  GO.lcd.println("Starting");
  wifi_parameter_t wifi_parameters;
  wifi_parameters.SSID = "Pfannekuchen";
  wifi_parameters.PASSWORD = "kabelbeisser";
  connectWifi(wifi_parameters);
  
}
 
void loop() {
  GO.update();
  handleSonos();
  delay(200);
}