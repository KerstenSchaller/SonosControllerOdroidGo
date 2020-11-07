#ifndef BUTTON_WRAPPER_H
#define BUTTON_WRAPPER_H

#define VOLUME_UP_BUTTON (GO.JOY_Y.isAxisPressed() == 2) 
#define VOLUME_DOWN_BUTTON (GO.JOY_Y.isAxisPressed() == 1) 
#define NEXT_TRACK_BUTTON (GO.JOY_X.isAxisPressed() == 1) 
#define PLAY_PAUSE_BUTTON (GO.BtnA.isPressed() == 1)
//(GO.JOY_X.isAxisPressed() == 2)
#define BURGER_BUTTON (GO.BtnMenu.isPressed() == 1) 
//(GO.BtnVolume.isPressed() == 1) 
//(GO.BtnSelect.isPressed() == 1) 
//(GO.BtnStart.isPressed() == 1) 
//(GO.BtnB.isPressed() == 1)


#endif