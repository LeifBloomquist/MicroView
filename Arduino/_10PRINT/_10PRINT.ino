/*
     Teminal Demo
*/
#include <MicroView.h>

void setup()
{
  uView.begin();	// begin of MicroView  
  Serial.begin(38400);
  clearscreen(); 
}

void clearscreen()
{
  uView.clear(ALL);	// erase hardware memory inside the OLED controller
  uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
  uView.setFontType(0);
  uView.setCursor(0,0);
  uView.display();
  randomSeed(64);
}
  
  
char m[] = {47, 92};   // Characters /,\

void loop() 
{    
   uView.print(m[random(2)]);
   uView.display();
}
