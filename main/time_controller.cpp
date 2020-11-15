#include <WiFi.h>
#include "sonos_app.h"

struct tm time_info;

const long  gmtOffset_sec = 3600; //,600 is +1h for berlin time zone
const int   daylightOffset_sec = 3600; //3600 for wintertime 
const char* ntpServer = "pool.ntp.org";

hw_timer_t *timer2 = NULL;


void getTimeNTP() 
{
  if (!getLocalTime(&time_info)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.print("Time: ");
  Serial.println(&time_info, "%A, %B %d %Y %H:%M:%S");
}
void initTimerSec2(int seconds);
void onTimer2() 
{
    getTimeNTP();
    updateSonosScreen();
    initTimerSec2(60);
 }

void initTimerSec2(int seconds) 
{
  Serial.printf("Starting timer 2 with %d seconds\n", seconds);
  timer2 = timerBegin(1, 80, true);                      // timer 0, div 80
  timerAttachInterrupt(timer2, &onTimer2, true);          // attach callback
  timerAlarmWrite(timer2, seconds * 1000 * 1000, false); // set time in us
  timerAlarmEnable(timer2);
}

void handleTime()
{
  static bool firstAfterBoot = true;
  if(firstAfterBoot)
  {   
      // get time once and start a timer till the end of that minute
      // afterwards the timer starts itself in the callback
      configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
      getTimeNTP();
      initTimerSec2(60 - time_info.tm_sec);
      firstAfterBoot = false;
  }   
  
}