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
  
  
char c=0;

void loop() 
{    
    if (Serial.available() > 0)
    {
       if ((c%5) == 0) clearscreen();
      
       uView.print((int)c);
       uView.print(" : ");
       uView.print(c);
       uView.println();
       uView.display();
       Serial.read();
       c++;      
    }      
}
