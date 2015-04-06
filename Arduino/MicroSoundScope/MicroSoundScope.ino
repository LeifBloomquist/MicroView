/*
    Sound Viewer with the Sparkfun SEN-12642 Sound Detector
*/
#include <MicroView.h>

#define PIN_ENVELOPE_IN A1
#define PIN_AUDIO_IN A2

#define ENVELOPE_MAX    350
#define AUDIO_MAX       1023


// Global variables
int max_x = uView.getLCDWidth();
int max_y = uView.getLCDHeight();
int mid_y = max_y/2;

void setup() 
{
  uView.begin();	// begin of MicroView
  uView.clear(ALL);	// erase hardware memory inside the OLED controller
  uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
  uView.setFontType(0);
  uView.setCursor(0,0);	
  uView.display();	// display the content in the buffer memory, by default it is the MicroView logo
  
  Serial.begin(9600);
}

void loop()
{
  int last_y = mid_y;
 
  uView.clear(PAGE);
  
  for (int pos_x=1; pos_x < max_x; pos_x++)
  {
    int value = analogRead(PIN_AUDIO_IN); 
    float audio = (float)value/(float)AUDIO_MAX;   // 0 to 1
    audio-=0.5;

    int pos_y = mid_y+(audio*max_y);
    uView.line(pos_x-1, last_y, pos_x, pos_y);
  
    last_y = pos_y;
  }
  
  uView.display(); 
  delay(10);
}
