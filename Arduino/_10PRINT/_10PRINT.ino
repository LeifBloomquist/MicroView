/*
     10 PRINT CHR$(205.5+RND(1));   For MicroView/Arduino
     Leif Bloomquist
*/

#include <MicroView.h>

;  // Keep this here to pacify the Arduino pre-processor

#define C64FONT

#ifdef C64FONT    // C64 font for MicroView
  #define FONT 8
  #define MAZECHARS {77, 78}   // Characters \ and /
#else
  #define FONT 0  // Built-in 5x7 font
  #define MAZECHARS {92, 47}   // Characters \ and /
#endif

char m[] = MAZECHARS;

void setup()
{
  uView.begin();	// begin of MicroView
  clearscreen(); 
  randomSeed(64);
}

void clearscreen()
{
  uView.clear(ALL);	// erase hardware memory inside the OLED controller
  uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
  uView.setFontType(FONT);
  uView.setCursor(0,0);
  uView.display();
}

void loop() 
{    
   uView.print(m[random(2)]);
   uView.display();
}
