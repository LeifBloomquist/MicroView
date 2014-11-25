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
  uView.println("READY.");  
  uView.display();
}
  

void loop() 
{    
    if (Serial.available() > 0)
    {
       char c=Serial.read();
       
       if (c == 1)  // CTRL-A, clear
       {
         clearscreen();
         return;
       }
       
       if (c == 13)  // Return
       {
          c = 10;
       }
 
       uView.print(c);
       uView.display();
       Serial.print(c);  // Echo
    }      
}
