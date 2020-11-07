#include "sonos_app.h"
#include "sonos.h"
#include "button_wrapper.h"
#include "odroid_go.h"

void updateSonosScreen();
void handleButtonsSonos();
void handleSonos()
{
    sonos_parameters.UID = "RINCON_347E5C37566601400";
    handleButtonsSonos();
}

void handleButtonsSonos()
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


void updateSonosScreen()
{
    GO.lcd.clear();
    GO.lcd.setCursor(0,0);
    GO.lcd.printf("Playstate: %s\n",sonos_parameters.PlayState.c_str());
    GO.lcd.printf("Voume: ");
    GO.lcd.print(sonos_parameters.Volume, DEC);
    GO.lcd.printf("\n");
}