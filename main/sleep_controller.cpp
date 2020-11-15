#include "button_wrapper.h"
#include "sonos.h"

hw_timer_t *timer = NULL;

void IRAM_ATTR onTimer() 
{
  Serial.println("timer shut down");
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_32, 0);
  delay(500);
  esp_deep_sleep_start();
}

void initTimerSec(int seconds)
{
  timer = timerBegin(0, 80, true);                      // timer 0, div 80
  timerAttachInterrupt(timer, &onTimer, true);          // attach callback
  timerAlarmWrite(timer, seconds * 1000 * 1000, false); // set time in us
  timerAlarmEnable(timer);
}


void handleSleep() 
{
  static std::string playstateLastloop = sonos_parameters.PlayState;
  std::string playStateActual = sonos_parameters.PlayState;
  initTimerSec(15*60);
  
  //check if playstate has changed
  if(playstateLastloop != playStateActual)
  {
      if(playStateActual == "Play")
      {
        initTimerSec(15*60);
      }
      else
      {
        initTimerSec(3*60);
      }
      playstateLastloop = playStateActual;
    
  }
}